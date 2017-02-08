//
//  variableMapCFD.cpp
//  OP2A
//
//  Created by Kim M.K. on 26/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "variableMapCFD.hpp"


variableMapCFD::variableMapCFD()
:startIndex(3,0), m_rho(0.0)
{
    
}

variableMapCFD::variableMapCFD(variableMap input)
:startIndex(3,0), m_rho(0.0)
{
    NS = input.NS;
    ND = input.ND;
    NE = input.NE;
    
    temperatureMode = input.temperatureMode;
    NONEQ = input.NONEQ;
    SeparateModeElc = input.SeparateModeElc;
    SeparateModeEle = input.SeparateModeEle;
    
    HasMolecule = input.HasMolecule;
    HasIons     = input.HasIons;
    HasElectron = input.HasElectron;
    
    m_rho_s_global_ID.resize(NS);
    for (int s = 0; s< NS; s++) m_rho_s_global_ID[s] = input.RHO_globalID(s);
    
    m_T.resize(5);
    for (int m = 0; m < 5; m++) m_T[m] = input.T(m);
}

variableMapCFD::~variableMapCFD()
{
    
}

// [Part C]: Functions
variableMapCFD&	variableMapCFD::operator= (variableMap input)
{
    NS = input.NS;
    ND = input.ND;
    NE = input.NE;
    
    temperatureMode = input.temperatureMode;
    NONEQ = input.NONEQ;
    SeparateModeElc = input.SeparateModeElc;
    SeparateModeEle = input.SeparateModeEle;
    
    HasMolecule = input.HasMolecule;
    HasIons     = input.HasIons;
    HasElectron = input.HasElectron;
    
    m_rho_s_global_ID.resize(NS);
    for (int s = 0; s< NS; s++) m_rho_s_global_ID[s] = input.RHO_globalID(s);
    
    m_T.resize(5);
    for (int m = 0; m < 5; m++) m_T[m] = input.T(m);
    
    startIndex.resize(3);
    return *this;
}


void variableMapCFD::setting(int density, int velocity, int energy)
{
    startIndex[0] = density;
    startIndex[1] = velocity;
    startIndex[2] = energy;
}

void variableMapCFD::setting()
{
    startIndex[0] = 0;
    startIndex[1] = NS;
    startIndex[2] = NS+ND;
}

int variableMapCFD::Qid(int s, int mode)
{
    return (s + startIndex[mode]);
}

int variableMapCFD::EinQ(int mode)
{
    return (startIndex[2] + T(mode));
}

int variableMapCFD::Pressure()
{
    return (startIndex[2]);
}




void variableMapCFD::constructU(std::vector<double>&rho_s, std::vector<double>& u, std::vector<double>& T, std::vector<double>& U)
{
    U.resize(NS + ND + NE);
    
    for (int s = 0; s < NS; s++) U[Qid(s,0)] = rho_s[s];
    for (int s = 0; s < ND; s++) U[Qid(s,1)] = u[s];
    for (int s = 0; s < NE; s++) U[Qid(s,2)] = T[s];
};



void variableMapCFD::UtoQ_Common(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q)
{
    int index;
    m_rho  = 0.0;
    
    Q.resize(NS + ND + NE);
    for (int s = 0; s < NS + ND + NE; s ++) Q[s] = 0.0;
    
    for (int s = 0; s < NS; s++)
    {
        index    = Qid(s,0);
        Q[index] = U[index];
        m_rho   += U[index];
    }
    
    for (int k = 0; k < ND; k++)
    {
        index    = Qid(k, 1);
        Q[index] = m_rho * U[index];
    }
}



void variableMapCFD::UtoW_Common(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W)
{
    W.resize(NS + ND + NE);
    W = U;
}


void variableMapCFD::QtoU_Common(std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U)
{
    int    index;
    m_rho = 0.0;
    
    U.resize(NS + ND + NE);
    for (int s = 0; s < NS+ND+NE; s ++) U[s] = 0.0;
    
    for (int s = 0; s < NS; s++)
    {
        index    = Qid(s,0); // Species index in U
        U[index] = Q[index];
        
        m_rho   += Q[index];      // mixture density
    }
    
    for (int k = 0; k < ND; k++)
    {
        index    = Qid(k, 1);  // Momentum index in U
        U[index] = Q[index] / m_rho;
    }
}



