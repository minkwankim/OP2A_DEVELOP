//
//  flowdatabase.cpp
//  OP2A
//
//  Created by Kim M.K. on 22/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "flowdatabase.hpp"
#include <cmath>



flowDataBase::flowDataBase()
: u(3, 0), T(5, 0), m_assigned(false)
{
    rhos.reserve(FLUID_DATA_MAX_SPECIES);
}


flowDataBase::flowDataBase(int NS)
: rhos(NS), u(3), T(5), m_assigned(true)
{
   
}





flowDataBase::~flowDataBase()
{
    
}



void flowDataBase::reassign(int NS, int ND, int NE)
{
    rhos.resize(NS);
    u.resize(ND);
    T.resize(NE);
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


void flowDataBase::allocateU(int NS, int ND, int E_Tr, int E_Tv, int E_Tele, int E_Te, std::vector<double>& U)
{
    int NE;
    NE = std::max(E_Tr, E_Tv);
    NE = std::max(NE, E_Tele);
    NE = std::max(NE, E_Te);
    NE = NE + 1;
    U.resize(NS+ND+NE);
    
    for (int s = 0; s < NS; s++)    U[s]    = rhos[s];
    for (int k = 0; k < ND; k++)    U[NS+k] = u[k];
    
    NE = NS + ND;
    
    U[NE+E_Te]   = T[ELE];
    U[NE+E_Tele] = T[ELC];
    U[NE+E_Tv]   = T[VIB];
    U[NE+E_Tr]   = T[ROT];
    U[NE]        = T[0];
}




