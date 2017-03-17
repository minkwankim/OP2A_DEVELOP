//
//  initializeFlowCondition.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include <stdio.h>
#include "../CHEM/speciesDataBase.hpp"
#include "../DATA/problemSetup.hpp"
#include "../DATA/wallMaterial.hpp"

#include "gridCFD.hpp"
#include "primitive_variables.hpp"

#include "../DATA/dataCFD.hpp"


void initizliseFlowCondition(ProbleSetup* problem,
                             CFD::Grid* grid,
                             std::vector<variableMapCFD*>& CFD_variables,
                             std::vector< std::vector< std::vector<double> > >& U_flow,
                             std::vector< std::vector< std::vector<double> > >& Q_flow)
{
    int N_tot       = -1;
    int init_method = -1;
    
    init_method     = problem->boundaryconditions.iniMethod;
    
    for (int s = 0; s < problem->physicalmodel.num_fluid; s++)
    {
        N_tot = CFD_variables[s]->NS + CFD_variables[s]->ND +CFD_variables[s]->NE;

        for (int n = 0; n < grid->info->NNM; n++)   grid->data->nodes[n][s].basic->U = U_flow[init_method][s];
        for (int f = 0; f < grid->info->NFM; f++)   grid->data->faces[f][s].basic->U = U_flow[init_method][s];
        for (int c = 0; c < grid->info->NCM; c++)   grid->data->cells[c][s].basic->U = U_flow[init_method][s];
        
        for (int n = 0; n < grid->info->NNM; n++)   grid->data->nodes[n][s].basic->Q = Q_flow[init_method][s];
        for (int f = 0; f < grid->info->NFM; f++)   grid->data->faces[f][s].basic->Q = Q_flow[init_method][s];
        for (int c = 0; c < grid->info->NCM; c++)   grid->data->cells[c][s].basic->Q = Q_flow[init_method][s];
    }
}
