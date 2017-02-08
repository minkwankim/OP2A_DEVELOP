//
//  primitive_variables_fluid5.cpp
//  OP2A
//
//  Created by Kim M.K. on 08/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "primitive_variables_fluid5.hpp"
#include "temperatureFns.hpp"



void variableMapCFD_fluid_5::UtoQ(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q)
{
    UtoQ_Common(U, speciesdata, Q);
    
    int index;
    double e;
    double E    = 0.0;
    double E_ke = 0.0;
    double Eelc = 0.0;
    double Eele = 0.0;
    double T    = U[EinQ(TRA)];
    double Telc = U[EinQ(ELC)];
    double Tele = U[EinQ(ELE)];
    
    
    for (int s = 0; s < NS; s++)
    {
        index = Qid(s,0);
        
        if (speciesdata[s].basic.type != -1)
        {
            e  = speciesdata[s].basic.h0;
            e += (speciesdata[s].basic.Cv[0] +speciesdata[s].basic.Cv[1]) * T;
            e += speciesdata[s].e_vib(T);
            
            E    += U[index] * e;    // Translational-Rotational-electron energy
            Eelc += U[index] * speciesdata[s].e_elc(Telc);
        }
        else
        {
            e    = speciesdata[s].basic.Cv[0]*Tele;
    
            Eele += U[index] * e;
        }
    }
    
    for (int k = 0; k < ND; k++)
    {
        index = Qid(k, 1);
        E_ke += U[index] * U[index];
    }
    E_ke = 0.5 * m_rho * E_ke;
    
    
    // Total Energy
    E = E + E_ke + Eelc + Eele;

    Q[Qid(0,2)] = E;
    Q[Qid(1,2)] = Eelc;
    Q[Qid(2,2)] = Eele;
}


void variableMapCFD_fluid_5::UtoW(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W)
{
    UtoW_Common(U, speciesdata, W);
    
    int    index;
    double T   = U[EinQ(TRA)];
    double Te  = U[EinQ(ELE)];
    double p   = 0.0;
    double pe  = 0.0;
    
    for (int s = 0; s < NS; s++)
    {
        index = Qid(s,0);
        if (speciesdata[s].basic.type != -1) p  += U[index]*speciesdata[s].basic.R;
        else                                 pe += U[index]*speciesdata[s].basic.R;
    }
    
    pe = pe*Te;
    p  = p*T + pe;
    
    W[Qid(0,2)] = p;
    W[Qid(2,2)] = pe;
}



void variableMapCFD_fluid_5::QtoU(std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U)
{
    QtoU_Common(Q, speciesdata, U);
    
    
    // Speies
    int index;
    double rhoCv   = 0.0;
    double rhoeCve = 0.0;
    double E_h0  = 0.0;
    double E_ke  = 0.0;
    double E     = Q[Qid(0,2)];     // Total energy
    double Eelc  = Q[Qid(1,2)];     // Electronic energy
    double Eele  = Q[Qid(2,2)];     // Electron energy
    
    
    for (int s = 0; s < NS; s++)
    {
        index    = Qid(s,0);                           // Species index in U
        E_h0    += Q[index] * speciesdata[s].basic.h0; // Enthalpy of formation
        
        if (speciesdata[s].basic.type != -1) rhoCv   += Q[index] * (speciesdata[s].basic.Cv[0] + speciesdata[s].basic.Cv[1]);
        else                                 rhoeCve  = Q[index] * speciesdata[s].basic.Cv[0];
    }
    
    for (int k = 0; k < ND; k++)
    {
        index    = Qid(k, 1);  // Momentum index in U
        E_ke    += U[index] * U[index];
    }
    E_ke = 0.5 * m_rho * E_ke;
    
    
    double T     = 0.0;
    double Telc  = 0.0;
    double Tele  = 0.0;
    
    // Electronic Temperature
    NEQ_elc Temp_elc(10000, 1.0e-8);
    Telc  = Temp_elc.solveTemp(U, speciesdata, Eelc, NS);
    
    
    double E_temp = E - E_ke - E_h0 - Eelc - Eele;
    
    if (E_temp < 0 || E_temp != E_temp)
    {
        std::ostringstream error_message;
        error_message << "[Error in U to Q convert] Negative/Inf T, [E_tra] = " << E_temp;
        Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::Negative());
    }
    
    T = E_temp / rhoCv;
    
    
    // Considering Vibrational Energies
    int    n     = 0;
    double error = 1.0;
    double Tnew  = T;
    
    while (n < 1000 && error > 1.0e-8)
    {
        double Evib_guess = 0.0;
        
        for (int s = 0; s < NS; s++)
        {
            index = Qid(s,0);
            Evib_guess += U[index] * speciesdata[s].e_vib(T);
        }
        
        // Update T
        Tnew  = (E_temp - Evib_guess) / rhoCv;
        error = fabs(Tnew - T);
        T     = Tnew;
        n++;
    }
    
    if (rhoeCve != 0) Tele = Eele / rhoeCve;
    else              Tele = T;
    
    U[Qid(0,2)] = T;
    U[Qid(1,2)] = Telc;
    U[Qid(2,2)] = Tele;
}

