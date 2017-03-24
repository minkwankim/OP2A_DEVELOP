//
//  output.cpp
//  OP2A
//
//  Created by Kim M.K. on 23/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include "OP2ACFD.hpp"
#include "../COMM/StringOPs.hpp"

void outputNodeTecplot(ProbleSetup* problem,
                       CFD::Grid* grid,
                       std::vector<variableMapCFD*>& CFD_variables,
                       std::vector< std::vector<species> >& species,
                       vector3D&  data,
                       std::vector<std::vector <std::string> >& variableName)
{
    int NNM = grid->info->NNM;
    int index;
    
    data.resize(problem->physicalmodel.num_fluid);
    variableName.resize(problem->physicalmodel.num_fluid);
    
    for (int f = 0; f < problem->physicalmodel.num_fluid; f++)
    {
        int N = CFD_variables[f]->NS + CFD_variables[f]->ND + CFD_variables[f]->NE;
        
        data[f].resize(NNM);
        variableName[f].resize(N);
        
        
        for (int s = 0; s < CFD_variables[f]->NS; s++)  variableName[f][s] = "rho_" + species[f][s].name;
        variableName[f][CFD_variables[f]->NS]   = "u";
        variableName[f][CFD_variables[f]->NS+1] = "v";
        if (CFD_variables[f]->ND == 3) variableName[f][CFD_variables[f]->NS+2] = "w";
        
        for (int m = 0; m < CFD_variables[f]->NE; m++)
            variableName[f][CFD_variables[f]->NS+CFD_variables[f]->ND+m] = CFD_variables[f]->temperatureName[m];
        
        for (int n = 0; n < NNM; n++)
        {
            data[f][n].resize(N);
            
            for (int s = 0; s < CFD_variables[f]->NS; s++)
            {
                index = CFD_variables[f]->Qid(s,0);
                data[f][n][s] = grid->data->nodes[n][f].basic->U[index];
            }
            
            for (int k = 0; k < CFD_variables[f]->ND; k++)
            {
                index = CFD_variables[f]->Qid(k,1);
                data[f][n][CFD_variables[f]->NS+k] = grid->data->nodes[n][f].basic->U[index];
            }
            
            
            for (int m = 0; m < CFD_variables[f]->NE; m++)
            {
                index = CFD_variables[f]->Qid(m,2);
                data[f][n][CFD_variables[f]->NS+CFD_variables[f]->ND+m] = grid->data->nodes[n][f].basic->U[index];
            }
        }
    }
}