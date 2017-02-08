//
//  primitive_variables.cpp
//  OP2A
//
//  Created by Kim M.K. on 20/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include <vector>
#include <sstream>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/noninstantiable.hpp"

#include "primitive_variables.hpp"


variableMapCFD* nonequilibriumModel(variableMap& model)
{
    variableMapCFD* aux;
    variableMapCFD_fluid_0 fluid0(model);
    variableMapCFD_fluid_1 fluid1(model);
    variableMapCFD_fluid_3 fluid3(model);
    variableMapCFD_fluid_4 fluid4(model);
    //variableMapCFD_fluid_5* fluid5 = new variableMapCFD_fluid_5(model);

    
   
    switch (model.temperatureMode)
    {
        case -1:
            aux = new variableMapCFD_fluid_0(model);
            break;
                
        case 0:
            aux = new variableMapCFD_fluid_0(model);
            break;
                
        case 1:
            aux = new variableMapCFD_fluid_1(model);
            break;
                
        case 2:
            aux = new variableMapCFD_fluid_1(model);
            break;
            
        case 3:
            aux = new variableMapCFD_fluid_3(model);
            break;
            
        case 4:
            aux = new variableMapCFD_fluid_4(model);
            break;
            
        case 5:
            aux = new variableMapCFD_fluid_5(model);
            break;
            
        case 6:
            aux = new variableMapCFD_fluid_3(model);
            break;
            
        case 7:
            aux = new variableMapCFD_fluid_4(model);
            break;
            
        case 8:
            aux = new variableMapCFD_fluid_5(model);
            break;
            
        case 9:
            aux = new variableMapCFD_fluid_9(model);
            break;
            
        case 10:
            aux = new variableMapCFD_fluid_10(model);
            break;
            
        case 11:
            aux = new variableMapCFD_fluid_11(model);
            break;
            
        case 12:
            aux = new variableMapCFD_fluid_12(model);
            break;
            
        case 13:
            aux = new variableMapCFD_fluid_13(model);
            break;
            
        case 14:
            aux = new variableMapCFD_fluid_14(model);
            break;
            
        case 15:
            aux = new variableMapCFD_fluid_15(model);
            break;
            
        case 16:
            aux = new variableMapCFD_fluid_16(model);
            break;
            
        case 17:
            aux = new variableMapCFD_fluid_17(model);
            break;
            
        case 27:
            aux = new variableMapCFD_fluid_27(model);
            break;
            
        default:
            std::ostringstream error_message;
            error_message << "Temperature Model number: " << model.temperatureMode << " is Not SUPPORTED!";
            Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::NotSupportedType());
            break;
    }
    
    aux->setting();
    return (aux);
}



void UtoQ(variableMapCFD& info, std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q)
{
    // Speies
    int index;
    double E_ke = 0.0;
    double E_h0 = 0.0;
    double rho  = 0.0;
    
    double E_tra = 0.0;
    double E_rot = 0.0;
    double E_vib = 0.0;
    double E_elc = 0.0;
    double E_ele = 0.0;
    
    double T_tra = U[info.EinQ(TRA)];
    double T_rot = U[info.EinQ(ROT)];
    double T_vib = U[info.EinQ(VIB)];
    double T_elc = U[info.EinQ(ELC)];
    double T_ele = U[info.EinQ(ELE)];
    
    
    Q.resize(info.NS + info.ND + info.NE);
    for (int s = 0; s < info.NS + info.ND + info.NE; s ++) Q[s] = 0.0;
    
    for (int s = 0; s < info.NS; s++)
    {
        index = info.Qid(s,0);
        Q[index] = U[index];
        rho += U[index];
        
        E_h0  += U[index] * speciesdata[s].basic.h0;         // Enthalpy of formation
        E_tra += U[index] * speciesdata[s].e(T_tra, 0);    // Translational energy
        E_rot += U[index] * speciesdata[s].e(T_rot, 1);    // Rotational energy
        E_vib += U[index] * speciesdata[s].e(T_vib, 2);    // Vibrational energy
        E_elc += U[index] * speciesdata[s].e(T_elc, 3);    // Electronic energy
        E_ele += U[index] * speciesdata[s].e(T_ele, 4);    // Electron energy
    }
    
    for (int k = 0; k < info.ND; k++)
    {
        index = info.Qid(k, 1);
        Q[index] = rho * U[index];
        
        E_ke    += U[index] * U[index];
    }
    E_ke = 0.5 * rho * E_ke;
    
    
    // Total Energy
    index = info.Qid(0,2);
    Q[index] = E_tra + E_rot + E_vib + E_elc + E_ele + E_ke + E_h0;
    
    if (info.NONEQ[ROT] != 0)
    {
        index = info.EinQ(ROT);
        Q[index] += E_rot;
    }
    
    if (info.NONEQ[VIB] != 0)
    {
        index = info.EinQ(VIB);
        Q[index] += E_vib;
    }
    
    if (info.NONEQ[ELC] != 0)
    {
        index = info.EinQ(ELC);
        Q[index] += E_elc;
    }
    
    if (info.NONEQ[ELE] != 0)
    {
        index = info.EinQ(ELE);
        Q[index] += E_ele;
    }

}


void UtoW(variableMapCFD& info, std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W)
{
    // Speies
    int index;
    double rho  = 0.0;
    
    double T  = U[info.EinQ(TRA)];
    double Te = U[info.EinQ(ELE)];
    double p  = 0.0;
    double pe = 0.0;
    
    W.resize(info.NS + info.ND + info.NE);
    W = U;
    
    for (int s = 0; s < info.NS; s++)
    {
        index = info.Qid(s,0);
        W[index] = U[index];
        rho += U[index];
        
        if (speciesdata[s].basic.type != -1)    p += U[index]*speciesdata[s].basic.R*T;
        else                                    pe = U[index]*speciesdata[s].basic.R*Te;
    }
    
    p += pe;
    
    index = info.EinQ(TRA);
    W[index] = p;
    
    if (info.NONEQ[ELE] != 0 && info.SeparateModeEle == YES)
    {
        index = info.EinQ(ELE);
        W[index] = pe;
    }
}




void QtoU(variableMapCFD& info, std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U)
{
    // Speies
    int    index;
    int    flag_vib  = 0;
    int    flag_elc  = 0;
    double rho       = 0.0;
    double rhoCv_tra = 0.0;
    double rhoCv_rot = 0.0;
    double rhoCv_ele = 0.0;
    
    double E_ke      = 0.0;
    double E_h0      = 0.0;
    double E         = 0.0;
    double Erot      = 0.0;
    double Evib      = 0.0;
    double Eelc      = 0.0;
    double Eele      = 0.0;
    
    
    U.resize(info.NS + info.ND + info.NE);
    for (int s = 0; s < info.NS + info.ND + info.NE; s ++) U[s] = 0.0;
    
    for (int s = 0; s < info.NS; s++)
    {
        index    = info.Qid(s,0); // Species index in U
        
        U[index] = Q[index];
        
        rho     += Q[index];                           // mixture density
        E_h0    += Q[index] * speciesdata[s].basic.h0; // Enthalpy of formation
        
        if(speciesdata[s].basic.type != -1)
        {
            rhoCv_tra += Q[index] * speciesdata[s].basic.Cv[0];
            rhoCv_rot += Q[index] * speciesdata[s].basic.Cv[1];
        }
        else
        {
            rhoCv_ele += Q[index] * speciesdata[s].basic.Cv[0];
        }
    }
    
    for (int k = 0; k < info.ND; k++)
    {
        index    = info.Qid(k, 1);  // Momentum index in U
        U[index] = Q[index] / rho;
        
        E_ke    += U[index] * U[index];
    }
    E_ke = 0.5 * rho * E_ke;
    
    E  = Q[info.Qid(0,2)];     // Total energy
    
    // Rotational energy
    if (info.NONEQ[ROT] != 0)
    {
        index = info.EinQ(ROT);
        Erot  = Q[index];
        U[index] = Erot / rhoCv_rot;
        rhoCv_rot = 0.0;
    }
    
    

    if (info.NONEQ[VIB] != 0)
    {
        index = info.EinQ(ELE);
        Evib  = Q[index];
    }
    else
    {
        flag_vib = 1;
        Evib     = 0.0;
    }
    
    if (info.NONEQ[ELC] != 0)
    {
        if (info.SeparateModeElc == YES)
        {
            index = info.EinQ(ELC);
            Eelc  = Q[index];
        }
    }
    else
    {
        flag_elc = 1;
        Eelc     = 0.0;
    }
    
    if (info.NONEQ[ELE] != 0)
    {
        if (info.SeparateModeEle == YES)
        {
            index    = info.EinQ(ELE);
            Eele     = Q[index];
            U[index] = Eele / rhoCv_ele;
            rhoCv_ele = 0.0;
        }
    }
    
    
    double T;
    double E_tra = E - E_ke - E_h0 - Erot - Evib - Eelc - Eele;
    double rhoCv = rhoCv_tra + rhoCv_rot + rhoCv_ele;
    
    
    if (E_tra < 0 || E_tra != E_tra)
    {
        std::ostringstream error_message;
        error_message << "[Error in U to Q convert] Negative/Inf T, [E_tra] = " << E_tra;
        Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::Negative());
    }
    
    T = E_tra / rhoCv;
    
    
    // Considering Vibrational and Electronic Energies
    if (flag_vib == 1 || flag_elc == 1)
    {
    
        int    n     = 0;
        double error = 1.0;
        double Tnew  = T;
        
        while (n < 100 && error > 1.0e-5)
        {
            double Evib_guess = 0.0;
            double Eelc_guess = 0.0;
            
            
            if (flag_vib == 1)
            {
                for (int s = 0; s < info.NS; s++)
                {
                    index       = info.Qid(s,0);
                    Evib_guess += U[index] * speciesdata[s].e(T, 2);    // Vibrational energy
                }
            }
            
            if (flag_elc == 1)
            {
                for (int s = 0; s < info.NS; s++)
                {
                    index       = info.Qid(s,0);
                    Eelc_guess += U[index] * speciesdata[s].e(T, 3);    // Vibrational energy
                }
            }
            
            // Update T
            Tnew  = (E_tra - Evib_guess - Eelc_guess) / rhoCv;
            error = fabs(Tnew - T);
            T = Tnew;
            n++;
        }
    }
    
    
    U[info.Qid(0,2)] = T;
}


