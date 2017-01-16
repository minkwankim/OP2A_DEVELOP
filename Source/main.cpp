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


//#include "./CFD/OP2ACFD.hpp"




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
    std::vector<species>    speciesdata(problem.physicalmodel.NS);
    for (int s = 0; s < problem.physicalmodel.NS; s++)  speciesdata[s] = species_database.find(problem.physicalmodel.speciesList[s]);

    
    // 4. Error check and show the simulation setting [Please DO NOT CHANGE THIS SECTION]
    problem.errorcheck_and_shows();
    
    
    // 5. Read / Generate mesh
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
    

    
    // TEST SECTION
    NodeBase test_node1;
    NodeBase test_node2;
    
    test_node1.geometry.id = 1;
    test_node2.geometry.id = 1;
    
    double   test_node1_data = 0.0;
    double   test_node2_data = 10.0;
    
   
    //Node_ver1<NodeBase, double>  test_node1_fullset;
    //Node_ver1<NodeBase, double>  test_node2_fullset;
    //test_node1_fullset.assign(test_node1, test_node1_data);
    //test_node2_fullset.assign(test_node1, test_node1_data);
    //test_node2_fullset.geom->geometry.id = 2;
    
    
    
    
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
