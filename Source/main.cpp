//
//  main.cpp
//  OP2A
//
//  Created by Kim M.K. on 15/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//
#include <omp.h>
#include <iostream>
#include <mkl.h>


#include "./COMM/version.hpp"
#include "./COMM/error_codes.hpp"

#include "./DATA/problemSetup.hpp"
#include "./DATA/wallMaterial.hpp"
#include "./DATA/dataCFD.hpp"
#include "./CHEM/speciesDataBase.hpp"

#include "./MATH_MK/matrix.hpp"
#include "./GRID/grid.hpp"


#include "./CFD/OP2ACFD.hpp"

#include "./CFD/primitive_variables.hpp"
#include "./CFD/temperatureFns.hpp"


#include "./DATA/ProbPhysicalModel.hpp"




// Global variables
#define CURRENT_MAIN_VERSION 1
#define CURRENT_SUB_VERSION  1
#define CURRENT_VERSION_TYPE "TEST"



// Temperary definition for test (Need to adjust in the final version)
#define PROBSETUPFILE   "/Users/mkk1u16/Desktop/Code_Development/OP2A/problem.pro"
#define SPECIESDATABASE "/Users/mkk1u16/Desktop/Code_Development/OP2A/dat/species.dat"
#define WALLMATERIAL    "/Users/mkk1u16/Desktop/Code_Development/OP2A/dat/wall_material.dat"





int main(int argc, char **argv) {
    
    
    /*
     * ==========================================
     * Pre-Processing ver 1.0
     * ==========================================
     * It is initially developed by Min Kwan Kim
     *
     *                Last Updated
     *                             on 21/June/2016
     *                             by Min Kwan Kim
     */
    
    // 1. Setting Version information [Please DO NOT CHANGE THIS SECTION]
    time_t	m_t = time(0);
    struct	tm* m_now;
    m_now = localtime(& m_t);
    Common::version ver(CURRENT_MAIN_VERSION, CURRENT_SUB_VERSION,  m_now->tm_year + 1900, m_now->tm_mon + 1, m_now->tm_mday, CURRENT_VERSION_TYPE);
    ver.info();
    
    
    
    // 2. Initialize and Setup variables [Please DO NOT CHANGE THIS SECTION]
    ProbleSetup problem;
    if (std::string(argv[0]) == " ") problem.inputoutput.filename_ProblemSetup = PROBSETUPFILE;
    problem.inputoutput.filename_ProblemSetup = PROBSETUPFILE;
    problem.read();
    problem.computation.initialize(argc, argv);
    
    
    
    // 3. Read and Assign Wall material and Species Database
    //    A. Read Database[Please DO NOT CHANGE THIS SECTION]
    wallMaterialDataBase    wall_material_database;
    speciesDataBase         species_database;
    
    wall_material_database.read(problem.inputoutput.filename_wallmaterial);
    species_database.read(problem.inputoutput.filename_speciesdatabase);
    
    //    B. Assign wall material and species data for the problem
    //       a. Wall material properties
    problem.boundaryconditions.wallMat.resize(problem.boundaryconditions.wallMatName.size());
    for (int s = 0; s < problem.boundaryconditions.wallMatName.size(); s++) problem.boundaryconditions.wallMat[s] = wall_material_database.find(problem.boundaryconditions.wallMatName[s]);
    
    //       b. Species properties
    std::vector<species> speciesdata(problem.physicalmodel.NS_tot); // Global species data
    std::vector< std::vector<species> > species;                    // Species data for each fluids
    for (int s = 0; s < problem.physicalmodel.NS_tot; s++) speciesdata[s] = species_database.find(problem.physicalmodel.speciesList[s]);
    
    
    
    // 4. Read / Generate mesh
    //  - NOTE: Cartesian mesh generation module need to b completed
    // A. Read from the prepared mesh file
    std::string        gridfilename = "/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2.op2";
    std::string        outfilename  = "/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2";
    
    GridBasicInfo gridinfo;
    GridMPI       gridmpi;
    GridGeo       gridgeo;
    readGridFromFile(gridfilename, gridinfo, gridgeo);
    processingGrid(gridinfo, gridgeo);
    writeGridGeoTecplot(outfilename, gridinfo, gridgeo);
    
    // Grid for CFD
    CFD::Grid gridCFD;
    gridCFD.info  = &gridinfo;
    gridCFD.mpi   = &gridmpi;
    gridCFD.geo   = &gridgeo;
    
    // Grid for DSMC
    
    
    
    // 5. Error check and show the simulation setting/Processing input data[Please DO NOT CHANGE THIS SECTION]
    std::vector<variableMapCFD*> CFD_variables(problem.physicalmodel.num_fluid);
    problem.processing(speciesdata, gridinfo.DIM);
    problem.errorcheck_and_shows();

    switch (problem.numericalmethod.mode)
    {
        case 0: // CFD-simulation
            species.resize(problem.physicalmodel.num_fluid);
            for (int f = 0; f < problem.physicalmodel.num_fluid; f++)
            {
                species[f].resize(problem.physicalmodel.variableSetting[f].NS);
                for (int s = 0; s < problem.physicalmodel.variableSetting[f].NS; s++) species[f][s] = speciesdata[problem.physicalmodel.variableSetting[f].rho_s_ID(s)];
                    
                CFD_variables[f] = nonequilibriumModel(problem.physicalmodel.variableSetting[f]);
            }
            
            if (problem.basicinfo.cartesian_grid != 0)  gridCFD.allocateIndex();
            std::vector<int> NS(problem.physicalmodel.num_fluid, 0);
            std::vector<int> NE(problem.physicalmodel.num_fluid, 0);
            
            for (int f = 0; f < problem.physicalmodel.num_fluid; f++)
            {
                NS[f] = problem.physicalmodel.variableSetting[f].NS;
                NE[f] = problem.physicalmodel.variableSetting[f].NE;
            }
            
            if (problem.numericalmethod.cfd.timeIntegration == 0)   gridCFD.allocateData(NS, gridinfo.DIM, NE, 0, 1, 2, false, problem.physicalmodel.num_fluid);
            else                                                    gridCFD.allocateData(NS, gridinfo.DIM, NE, 0, 1, 2, true,  problem.physicalmodel.num_fluid);
            
            gridCFD.allocateInternalData();
            gridCFD.errorCheck();
            break;
            
            /*
        case 1: // DSMC-simulation
            
            break;
            
        case 2: // Hybrid-simulation
            
            break;
             */
    }
    

    
    // TEST SECTION
    std::vector<double> test_rho(8);
    std::vector<double> test_u(3, 0.0);
    std::vector<double> test_T(4, 0.0);
    std::vector<double> test_U;
    std::vector<double> test_W;
    std::vector<double> test_Q;
    
    test_rho[0] = 2.0e-4;
    test_rho[1] = 1.0e-4;
    test_rho[2] = 1.0e-4;
    test_rho[3] = 1.0e-4;
    test_rho[4] = 1.0e-4;
    test_rho[5] = 1.0e-14;
    test_rho[6] = 1.0e-14;
    test_rho[7] = 1.0e-14;

    
    test_u[0]  = 5000;
    
    test_T[0] = 300;
    test_T[1] = 3000;
    test_T[2] = 5000;
    test_T[3] = 7000;
    
    
    
    
    CFD_variables[1]->constructU(test_rho, test_u, test_T, test_U);
    for (int n = 0; n < 10000; n++)
    {
        CFD_variables[1]->UtoQ(test_U, speciesdata, test_Q);
        CFD_variables[1]->UtoW(test_U, speciesdata, test_W);
        CFD_variables[1]->QtoU(test_Q, speciesdata, test_U);
    }

    
    
    /*
    std::vector<double> test_U;
    std::vector<double> test_U1;
    std::vector<double> test_Q;
    
    variableMapCFD      test_info(problem.physicalmodel.variableSetting[0]);
    test_info.setting();
    
    constructU(test_info, test_rho, test_u, test_T, test_U);
    UtoQ(test_info, test_U, speciesdata, test_Q);
    QtoU(test_info, test_Q, speciesdata, test_U1);
    */
    
    
    
    
    //GridBasicInfo gridinfo;
    //GridData<NodeNormal<double>, FaceNormal<double>, CellNormal<double> > gridtemp;
    //readGridFromFile("/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2.op2", gridinfo, gridtemp);
    //processingGrid(gridinfo, gridtemp);
    //writeGridTecplot("/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2", gridinfo, gridtemp);
    
    // insert code here...
    double res;
    res = 1.0;
    std::cout << "Hello, World!  " << res << "\n";
    return 0;
   
    
}
