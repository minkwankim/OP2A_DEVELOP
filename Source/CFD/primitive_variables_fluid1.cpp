//
//  primitive_variables_fluid1.cpp
//  OP2A
//
//  Created by Kim M.K. on 07/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "primitive_variables_fluid1.hpp"

void variableMapCFD_fluid_1::UtoQ(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q)
{
    UtoQ_Common(U, speciesdata, Q);
    
    
    int index;
    double e;
    double E    = 0.0;
    double E_ke = 0.0;
    double Ee   = 0.0;
    double T    = U[Qid(0,2)];
    double Te   = U[Qid(1,2)];
    
    
    
    for (int s = 0; s < NS; s++)
    {
        index = Qid(s,0);
        
        if (speciesdata[s].basic.type != -1)
        {
            e  = speciesdata[s].basic.h0;
            e += (speciesdata[s].basic.Cv[0] +speciesdata[s].basic.Cv[1]) * T;
            e += speciesdata[s].e_vib(T);
            e += speciesdata[s].e_elc(T);
            
            E += U[index] * e;    // Translational-Rotational-electron energy
        }
        else
        {
            e  = speciesdata[s].basic.Cv[0]*Te;
            Ee = U[index] * e;
            
            E += Ee;
        }
    }
    
    for (int k = 0; k < ND; k++)
    {
        index = Qid(k, 1);
        E_ke += U[index] * U[index];
    }
    E_ke = 0.5 * m_rho * E_ke;
    
    
    // Total Energy
    E = E + E_ke;
    
    index = Qid(0,2);
    Q[index] = E;
    
    index = Qid(1,2);
    Q[index] = Ee;
}




void variableMapCFD_fluid_1::UtoW(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W)
{
    UtoW_Common(U, speciesdata, W);
    
    int    index;
    double T  = U[EinQ(TRA)];
    double Te = U[EinQ(ELE)];
    double p  = 0.0;
    double pe = 0.0;
    
    for (int s = 0; s < NS; s++)
    {
        index = Qid(s,0);
        if (speciesdata[s].basic.type != -1)    p += U[index]*speciesdata[s].basic.R;
        else                                    pe = U[index]*speciesdata[s].basic.R;
    }
    pe = pe*Te;
    p  = p*T + pe;
    
    index = EinQ(TRA);
    W[index] = p;
    
    index = EinQ(ELE);
    W[index] = pe;
}



void variableMapCFD_fluid_1::QtoU(std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U)
{
    QtoU_Common(Q, speciesdata, U);
    
    
    // Speies
    int index;
    double rhoCv   = 0.0;
    double rhoeCve = 0.0;
    double E_h0    = 0.0;
    double E_ke    = 0.0;
    
    double E     = Q[Qid(0,2)];     // Total energy
    double Ee    = Q[Qid(1,2)];     // Electron energy
    
    
    for (int s = 0; s < NS; s++)
    {
        index    = Qid(s,0);                           // Species index in U
        E_h0    += Q[index] * speciesdata[s].basic.h0; // Enthalpy of formation
        
        if (speciesdata[s].basic.type != -1) rhoCv  += Q[index] * (speciesdata[s].basic.Cv[0] + speciesdata[s].basic.Cv[1]);
        else                                 rhoeCve = Q[index] * speciesdata[s].basic.Cv[0];
    }
    
    for (int k = 0; k < ND; k++)
    {
        index    = Qid(k, 1);  // Momentum index in U
        E_ke    += U[index] * U[index];
    }
    E_ke = 0.5 * m_rho * E_ke;
    
    double T, Te;
    double E_temp = E - E_ke - E_h0 - Ee;
    
    if (E_temp < 0 || E_temp != E_temp)
    {
        std::ostringstream error_message;
        error_message << "[Error in U to Q convert] Negative/Inf T, [E_tra] = " << E_temp;
        Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::Negative());
    }
    
    T  = E_temp / rhoCv;
    
    
    // Considering Vibrational and Electronic Energies
    int    n     = 0;
    double error = 1.0;
    double Tnew  = T;
    
    while (n < 100 && error > 1.0e-8)
    {
        double Eve_guess = 0.0;
        
        for (int s = 0; s < NS; s++)
        {
            index = Qid(s,0);
            Eve_guess += U[index] * (speciesdata[s].e_vib(T) + speciesdata[s].e_elc(T));
        }
        
        // Update T
        Tnew  = (E_temp - Eve_guess) / rhoCv;
        error = fabs(Tnew - T);
        T     = Tnew;
        n++;
    }
    
    
    if (rhoeCve != 0) Te = Ee / rhoeCve;
    else              Te = T;

    
    U[Qid(0,2)] = T;
    U[Qid(1,2)] = Te;
}





