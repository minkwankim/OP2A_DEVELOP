//
//  flowdatabase.cpp
//  OP2A
//
//  Created by Kim M.K. on 22/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "flowdatabase.hpp"




flowDataBase::flowDataBase()
: m_assigned(false)
{
    rhos.reserve(FLUID_DATA_MAX_SPECIES);
    u.reserve(3);
    rho_u.reserve(3);
    T.reserve(FLUID_DATA_MAX_ENERGY_MODE);
    E.reserve(FLUID_DATA_MAX_ENERGY_MODE);

    Q.reserve(FLUID_DATA_MAX_SPECIES + 3 + FLUID_DATA_MAX_ENERGY_MODE);
    U.reserve(FLUID_DATA_MAX_SPECIES + 3 + FLUID_DATA_MAX_ENERGY_MODE);
}


flowDataBase::flowDataBase(int NS, int ND, int NE)
: rhos(NS), u(ND), rho_u(ND), T(NE), E(NE), m_assigned(true)
{
    for (int s = 0; s < NS; s++)    Q[s]       = &rhos[s];
    for (int k = 0; k < ND; k++)    Q[NS+k]    = &rho_u[k];
    for (int d = 0; d < NE; d++)    Q[NS+ND+d] = &E[d];
    
    for (int s = 0; s < NS; s++)    U[s]       = &rhos[s];
    for (int k = 0; k < ND; k++)    U[NS+k]    = &u[k];
    for (int d = 0; d < NE; d++)    U[NS+ND+d] = &T[d];
}





flowDataBase::~flowDataBase()
{
    
}



void flowDataBase::reassign(int NS, int ND, int NE)
{
    rhos.resize(NS);
    u.resize(ND);
    rho_u.resize(ND);
    T.resize(NE);
    E.resize(NE);
    
    for (int s = 0; s < NS; s++)    Q[s]       = &rhos[s];
    for (int k = 0; k < ND; k++)    Q[NS+k]    = &rho_u[k];
    for (int d = 0; d < NE; d++)    Q[NS+ND+d] = &E[d];
    
    for (int s = 0; s < NS; s++)    U[s]       = &rhos[s];
    for (int k = 0; k < ND; k++)    U[NS+k]    = &u[k];
    for (int d = 0; d < NE; d++)    U[NS+ND+d] = &T[d];
    
    m_assigned = true;
}

void flowDataBase::assignSize(int NS, int ND, int NE)
{
    if (m_assigned != true) reassign(NS, ND, NE);
}


bool flowDataBase::check()
{
    return (m_assigned);
}