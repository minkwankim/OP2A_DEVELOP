//
//  primitive_variables_fluid9.cpp
//  OP2A
//
//  Created by Kim M.K. on 08/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "primitive_variables_fluid9.hpp"
#include "temperatureFns.hpp"



void variableMapCFD_fluid_9::UtoQ(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q)
{
    UtoQ_Common(U, speciesdata, Q);
    
    
    int index;
    double E    = 0.0;
    double E_ke = 0.0;
    double Evib = 0.0;
    double e    = 0.0;
    double T    = U[Qid(0,2)];
    double Tvib = U[Qid(1,2)];
    
    
    for (int s = 0; s < NS; s++)
    {
        index = Qid(s,0);
        
        e  = speciesdata[s].basic.h0;
        e += (speciesdata[s].basic.Cv[0] + speciesdata[s].basic.Cv[1]) * T;
        e += speciesdata[s].e_elc(T);
        
        Evib += U[index] * speciesdata[s].e_vib(Tvib);
        E    += U[index] * e;    // Tran-Rot-Elc-Ele energy
    }
    
    for (int k = 0; k < ND; k++)
    {
        index = Qid(k, 1);
        E_ke += U[index] * U[index];
    }
    E_ke = 0.5 * m_rho * E_ke;
    
    
    // Total Energy
    E = E + E_ke + Evib;
    Q[Qid(0,2)] = E;
    Q[Qid(1,2)] = Evib;
}


void variableMapCFD_fluid_9::UtoW(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W)
{
    UtoW_Common(U, speciesdata, W);
    
    int    index;
    double T  = U[Qid(0,2)];
    double p  = 0.0;
    
    for (int s = 0; s < NS; s++)
    {
        index = Qid(s,0);
        p += U[index]*speciesdata[s].basic.R;
    }
    p = p * T;
    
    W[Qid(0,2)] = p;
}



void variableMapCFD_fluid_9::QtoU(std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U)
{
    QtoU_Common(Q, speciesdata, U);
    
    
    // Speies
    int index;
    double rhoCv = 0.0;
    double E_h0  = 0.0;
    double E_ke  = 0.0;
    double E     = Q[Qid(0,2)];     // Total energy
    double Evib  = Q[Qid(1,2)];     // Vibrational energy
    
    
    
    
    for (int s = 0; s < NS; s++)
    {
        index    = Qid(s,0);                           // Species index in U
        E_h0    += Q[index] * speciesdata[s].basic.h0; // Enthalpy of formation
        
        rhoCv    += Q[index] * (speciesdata[s].basic.Cv[0] + speciesdata[s].basic.Cv[1]);
    }
    
    for (int k = 0; k < ND; k++)
    {
        index    = Qid(k, 1);  // Momentum index in U
        E_ke    += U[index] * U[index];
    }
    E_ke = 0.5 * m_rho * E_ke;
    
    double T    = 0.0;
    double Tvib = 0.0;
    
    
    // Vibrational Temperature
    NEQ_vib Temp_vib(10000, 1.0e-8);
    Tvib  = Temp_vib.solveTemp(U, speciesdata, Evib, NS);
    
    
    // Translatonal temperature
    double E_temp = E - E_ke - E_h0- Evib;
    
    if (E_temp < 0 || E_temp != E_temp)
    {
        std::ostringstream error_message;
        error_message << "[Error in U to Q convert] Negative/Inf T, [E_tra] = " << E_temp;
        Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::Negative());
    }
    T    = E_temp / rhoCv;
    
    // Considering Electronic Energies
    int    n     = 0;
    double error = 1.0;
    double Tnew  = T;
    
    while (n < 100 && error > 1.0e-8)
    {
        double Eelc_guess = 0.0;
        
        for (int s = 0; s < NS; s++)
        {
            index = Qid(s,0);
            Eelc_guess += U[index] * speciesdata[s].e_elc(T);
        }
        
        // Update T
        Tnew  = (E_temp - Eelc_guess) / rhoCv;
        error = fabs(Tnew - T);
        T     = Tnew;
        n++;
    }
    
    
    U[Qid(0,2)] = T;
    U[Qid(1,2)] = Tvib;

}