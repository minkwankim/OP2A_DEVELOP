//
//  problemSetup.cpp
//  OP2A
//
//  Created by Kim M.K. on 21/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//
#include "problemSetup.hpp"


// ProblemSetup Class
void ProbleSetup::read()
{
    basicinfo.read(inputoutput.filename_ProblemSetup);
    numericalmethod.read(inputoutput.filename_ProblemSetup);
    physicalmodel.read(inputoutput.filename_ProblemSetup);
    boundaryconditions.read(inputoutput.filename_ProblemSetup);
    computation.read(inputoutput.filename_ProblemSetup);
    inputoutput.read(inputoutput.filename_ProblemSetup);
}


void ProbleSetup::errorcheck_and_shows()
{
    std::cout << " -> ERROR CHECKING ON INPUT DATA AND SHOW THE SETTING" << std::endl;
    basicinfo.errorcheck_and_shows();
    numericalmethod.errorcheck_and_shows();
    physicalmodel.errorcheck_and_shows();
    boundaryconditions.errorcheck_and_shows();
    computation.errorcheck_and_shows();
    inputoutput.errorcheck_and_shows();
    std::cout << "[DONE]" << std::endl << std::endl;
}


void ProbleSetup::processing(std::vector<species>& speciesdata, int ND)
{
    int cond;   // Condition ID
    physicalmodel.speciesMapping(speciesdata, ND);
    
    // For Inlet Conditions
    for (int n = 0; n < boundaryconditions.U_inlet.size(); n++)
    {
        cond = boundaryconditions.inletCond[n]; // Get Condition ID of inlet

        // Resize Q and U for inlet condition for all fluids
        boundaryconditions.U_inlet[n].resize(physicalmodel.num_fluid);
        boundaryconditions.Q_inlet[n].resize(physicalmodel.num_fluid);
        for (int f = 0; f < physicalmodel.num_fluid; f++)
        {
            int NS = physicalmodel.variableSetting[f].NS;
            int ND = physicalmodel.variableSetting[f].ND;
            int NE = physicalmodel.variableSetting[f].NE;
            
            boundaryconditions.U_inlet[n][f].resize(NS+ND+ND);
            boundaryconditions.Q_inlet[n][f].resize(NS+ND+ND);
        }
    }
    
    
    // For Wall Conditions
    for (int n = 0; n < boundaryconditions.U_wall.size(); n++)
    {
        cond = boundaryconditions.wallCond[n];
        boundaryconditions.U_wall[n].resize(physicalmodel.num_fluid);
        boundaryconditions.Q_wall[n].resize(physicalmodel.num_fluid);
        
        for (int f = 0; f < physicalmodel.num_fluid; f++)
        {
            int NS = physicalmodel.variableSetting[f].NS;
            int ND = physicalmodel.variableSetting[f].ND;
            int NE = physicalmodel.variableSetting[f].NE;
            
            boundaryconditions.U_wall[n][f].resize(NS+ND+ND);
            boundaryconditions.Q_wall[n][f].resize(NS+ND+ND);
        }
    }
}

