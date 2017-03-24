//
//  OP2ACFDmain.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "OP2ACFD.hpp"


void OP2A_CFD_ver1(ProbleSetup& problem,
                   GridBasicInfo& gridinfo,
                   GridMPI& gridmpi,
                   GridGeo& gridgeo,
                   std::vector<species>& speciesdata,
                   wallMaterialDataBase& wall_material_database)
{
    // Create Grid for CFD
    CFD::Grid grid;
    grid.info  = &gridinfo;
    grid.mpi   = &gridmpi;
    grid.geo   = &gridgeo;
    
    
    // I. Preprocessing (Continue from commom module)
    //    1. Set NE/NS for each fluid
    if (problem.basicinfo.cartesian_grid != 0) grid.allocateIndex();
    std::vector<int> NS(problem.physicalmodel.num_fluid, 0);
    for (int f = 0; f < problem.physicalmodel.num_fluid; f++) NS[f] = problem.physicalmodel.variableSetting[f].NS;
    
    std::vector<int> NE(problem.physicalmodel.num_fluid, 0);
    for (int f = 0; f < problem.physicalmodel.num_fluid; f++) NE[f] = problem.physicalmodel.variableSetting[f].NE;
    
    
    //    2. Set and Allocate CFD data
    if (problem.numericalmethod.timeIntegration == 0) grid.allocateData(NS, gridinfo.DIM, NE, 0, 1, 2, false, problem.physicalmodel.num_fluid);
    else                                              grid.allocateData(NS, gridinfo.DIM, NE, 0, 1, 2, true,  problem.physicalmodel.num_fluid);
    grid.allocateInternalData();
    grid.errorCheck();
    
    
    //    3. Variable for CFD
    std::vector< std::vector<species> > species(problem.physicalmodel.num_fluid);        // Species data for each fluids
    std::vector<variableMapCFD*>        CFD_variables(problem.physicalmodel.num_fluid);  // CFD variable module
    
    for (int f = 0; f < problem.physicalmodel.num_fluid; f++)
    {
        CFD_variables[f] = nonequilibriumModel(problem.physicalmodel.variableSetting[f]);

        species[f].resize(problem.physicalmodel.variableSetting[f].NS);
        for (int s = 0; s < problem.physicalmodel.variableSetting[f].NS; s++)
        {
            species[f][s] = speciesdata[problem.physicalmodel.variableSetting[f].rho_s_ID(s)];
        }
    }
    
    
    

    // 4. Set U and Q from flow conditions
    int numFlowCond = problem.boundaryconditions.flowCond.size();
    std::vector< std::vector< std::vector<double> > > U_flow(numFlowCond);
    std::vector< std::vector< std::vector<double> > > Q_flow(numFlowCond);
    
    for (int i = 0; i < numFlowCond; i++)
    {
        U_flow[i].resize(problem.physicalmodel.num_fluid);
        Q_flow[i].resize(problem.physicalmodel.num_fluid);
        
        for (int f = 0; f < problem.physicalmodel.num_fluid; f++)
        {
            int flag = 0;
            if (CFD_variables[f]->NS == 1 && species[f][0].basic.type == -1) flag = -1;
            
            CFD_variables[f]->constructUfromGlobal(problem.boundaryconditions.flowCond[i].rhos,
                                                   problem.boundaryconditions.flowCond[i].u,
                                                   problem.boundaryconditions.flowCond[i].T,
                                                   U_flow[i][f], flag);
            CFD_variables[f]->UtoQ(U_flow[i][f], species[f], Q_flow[i][f]);
        }
    }
    
    
    // 5. Initializing
    initizliseFlowCondition(&problem, &grid, CFD_variables, U_flow, Q_flow);
    
    
    // 6 Set BC and Wall conditions
    int numInlet = problem.boundaryconditions.inletCond.size();
    
    problem.boundaryconditions.U_inlet.resize(numInlet);
    problem.boundaryconditions.Q_inlet.resize(numInlet);
    
    for (int i = 0; i < numInlet; i++)
    {
        int cond = problem.boundaryconditions.inletCond[i];
        
        problem.boundaryconditions.U_inlet[i].resize(numFlowCond);
        problem.boundaryconditions.Q_inlet[i].resize(numFlowCond);
        
        for (int f = 0; f < numFlowCond; f++)
        {
            int N_tot = CFD_variables[f]->NS + CFD_variables[f]->ND + CFD_variables[f]->NE;
            problem.boundaryconditions.U_inlet[i][f].resize(N_tot);
            problem.boundaryconditions.Q_inlet[i][f].resize(N_tot);
        }
        
        problem.boundaryconditions.U_inlet[i] = U_flow[cond];
        problem.boundaryconditions.Q_inlet[i] = U_flow[cond];
    }
    
    int numWall  = problem.boundaryconditions.wallCond.size();

    problem.boundaryconditions.U_wall.resize(numWall);
    problem.boundaryconditions.Q_wall.resize(numWall);
    
    for (int i = 0; i < numInlet; i++)
    {
        int cond = problem.boundaryconditions.inletCond[i];
        
        problem.boundaryconditions.U_wall[i].resize(numFlowCond);
        problem.boundaryconditions.Q_wall[i].resize(numFlowCond);
        
        for (int f = 0; f < numFlowCond; f++)
        {
            int N_tot = CFD_variables[f]->NS + CFD_variables[f]->ND + CFD_variables[f]->NE;
            
            problem.boundaryconditions.U_wall[i][f].resize(N_tot);
            problem.boundaryconditions.Q_wall[i][f].resize(N_tot);
        }
        
        problem.boundaryconditions.U_wall[i] = U_flow[cond];
        problem.boundaryconditions.Q_wall[i] = U_flow[cond];
    }
    
    
    // Test
    std::string outfilename  = "/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2_solution";
    
    vector3D  data;
    std::vector<std::vector <std::string> > variableName;
    
    outputNodeTecplot(&problem, &grid, CFD_variables, species, data, variableName);
    writeSolutionCellTecplot(outfilename, gridinfo, gridgeo, data[0], variableName[0], variableName[0].size());
    
    int aaa = 0;
    aaa = 10;
    
    
    
    
    
}