//
//  variableMap.cpp
//  OP2A
//
//  Created by Kim M.K. on 23/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include <sstream>

#include "variableMap.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/noninstantiable.hpp"


int energyMode(int NER, int NEV, int NEC, int NEE, int fluid)
{
    int aux = 0;
    aux = 27*NER + 9*NEV + 3*NEC + NEE;
    
    if (fluid != -1)    return (aux);
    else                return (-1);
}









// [Part B]: Section for Constructor/Destructor
variableMap::variableMap()
: NS(0), ND(0), NE(0), temperatureMode(0),
HasMolecule(0), HasIons(0), HasElectron(0),
NONEQ(5, 0), SeparateModeElc(0), SeparateModeEle(0),
m_T(5, 0)
{
    
}


variableMap::~variableMap()
{
    
}



// [Part C]: Functions
// A. For species
void variableMap::setSpecies(int ns)
{
    NS = ns;
    m_rho_s_global_ID.resize(NS);
}

void variableMap::setRho(int s_local, int s_global)
{
    if (m_rho_s_global_ID.size() < s_local +1)  m_rho_s_global_ID.resize(s_local+1);
    m_rho_s_global_ID[s_local] = s_global;
}


int variableMap::rho_s_ID(unsigned int s)
{
    if (s < NS) return (m_rho_s_global_ID[s]);
    
    std::ostringstream error_message;
    error_message << "Exceed index of Species: NS = " << NS;
    Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::ExceedLimit());
    return (-1);
}


bool variableMap::hasGlobalSpecies(int s)
{
    for (int index_s = 0; index_s < NS; index_s++)
    {
        if (m_rho_s_global_ID[index_s] == s) return (true);
    }
    
    return (false);
}




void variableMap::setDimension(int nd)
{
    ND = nd;
}






void variableMap::setTemperature(int NER, int NEV, int NEC, int NEE, int fluid)
{
    
    NONEQ[ROT] = NER;
    NONEQ[VIB] = NEV;
    NONEQ[ELC] = NEC;
    NONEQ[ELE] = NEE;
    
    if (fluid == -1)
    {
        NONEQ[ROT] = 0;
        NONEQ[VIB] = 0;
        NONEQ[ELC] = 0;
        NONEQ[ELE] = 0;
    }
    
    temperatureMode = energyMode(NONEQ[ROT], NONEQ[VIB], NONEQ[ELC], NONEQ[ELE], fluid);
    
    
    switch (temperatureMode)
    {
        case -1:
            SeparateModeElc = NO;
            SeparateModeEle = NO;
            
            NE = 1;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 0;
            m_T[ELE] = 0;
            break;
            
        case 0:                     // Single Temperature Model
            SeparateModeElc = NO;
            SeparateModeEle = NO;
            
            NE = 1;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 0;
            m_T[ELE] = 0;
            break;
            
        case 1:                     // NEE
            SeparateModeElc = NO;
            SeparateModeEle = YES;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 0;
            m_T[ELE] = 1;
            break;
            
        case 2:                     // NEE
            SeparateModeElc = NO;
            SeparateModeEle = YES;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 0;
            m_T[ELE] = 1;
            break;
            
        case 3:                     // NEE
            SeparateModeElc = YES;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 1;
            m_T[ELE] = 0;
            break;
            
        case 4:                     // NEC-NEE
            SeparateModeElc = YES;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 1;
            m_T[ELE] = 1;
            break;
        
        case 5:                     // NEC, NEE
            SeparateModeElc = YES;
            SeparateModeEle = YES;
            
            NE = 3;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 1;
            m_T[ELE] = 2;
            break;
            
        case 6:                     // NEC
            SeparateModeElc = YES;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 1;
            m_T[ELE] = 0;
            
        case 7:                     // NEC-NEE
            SeparateModeElc = YES;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 1;
            m_T[ELE] = 1;
            break;
            
        case 8:                     // NEC, NEE
            SeparateModeElc = YES;
            SeparateModeEle = YES;
            
            NE = 3;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 0;
            m_T[ELC] = 1;
            m_T[ELE] = 2;
            break;
            
        case 9:                     // NEV
            SeparateModeElc = NO;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 0;
            m_T[ELE] = 0;
            break;
            
        case 10:                     // NEV-NEE
            SeparateModeElc = NO;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 0;
            m_T[ELE] = 1;
            break;
            
        case 11:                     // NEV, NEE
            SeparateModeElc = NO;
            SeparateModeEle = YES;
            
            NE = 3;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 0;
            m_T[ELE] = 2;
            break;
            
        case 12:                     // NEV-NEC
            SeparateModeElc = NO;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 1;
            m_T[ELE] = 0;
            break;
            
            
        case 13:                    // Parks Two-temperature model
            SeparateModeElc = NO;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 1;
            m_T[ELE] = 1;
            break;
            
        case 14:                    // MK NEE Model
            SeparateModeElc = NO;
            SeparateModeEle = YES;
            
            NE = 3;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 1;
            m_T[ELE] = 2;
            break;
            
        case 15:
            SeparateModeElc = YES;
            SeparateModeEle = NO;
            
            NE = 3;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 2;
            m_T[ELE] = 0;
            break;
            
        case 16:
            SeparateModeElc = YES;
            SeparateModeEle = NO;
            
            NE = 3;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 2;
            m_T[ELE] = 2;
            break;
            
        case 17:
            SeparateModeElc = YES;
            SeparateModeEle = YES;
            
            NE = 4;
            m_T[TRA] = 0;
            m_T[ROT] = 0;
            m_T[VIB] = 1;
            m_T[ELC] = 2;
            m_T[ELE] = 3;
            break;
            
        case 27:
            SeparateModeElc = NO;
            SeparateModeEle = NO;
            
            NE = 2;
            m_T[TRA] = 0;
            m_T[ROT] = 1;
            m_T[VIB] = 0;
            m_T[ELC] = 0;
            m_T[ELE] = 0;
            break;
            
        case 40:                    // Rotational Noneq
            SeparateModeElc = NO;
            SeparateModeEle = NO;
            
            NE = 3;
            m_T[TRA] = 0;
            m_T[ROT] = 1;
            m_T[VIB] = 2;
            m_T[ELC] = 2;
            m_T[ELE] = 2;
            break;

        case 41:                    // Four temperaure model
            SeparateModeElc = NO;
            SeparateModeEle = YES;
            
            NE = 4;
            m_T[TRA] = 0;
            m_T[ROT] = 1;
            m_T[VIB] = 2;
            m_T[ELC] = 2;
            m_T[ELE] = 3;
            break;
         
        case 44:
            SeparateModeElc = YES;
            SeparateModeEle = YES;
            
            NE = 5;
            m_T[TRA] = 0;
            m_T[ROT] = 1;
            m_T[VIB] = 2;
            m_T[ELC] = 3;
            m_T[ELE] = 4;
            break;
            
        default:
            std::ostringstream error_message;
            error_message << "Temperature Model number: " << temperatureMode << " is Not SUPPORTED!";
            Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::NotSupportedType());
            break;
    }
}

int variableMap::Tid(unsigned int mode)
{
    if (mode < TRA || mode > ELE) Common::ExceptionError(FromHere(), "Provide mode is not supported temperature mode", Common::ErrorCodes::ExceedLimit());

    return (m_T[mode]);
}



void variableMap::showInfo()
{
    std::cout << "<<VARIABLE SETTING>>" << std::endl;
    std::cout << "    Number of Species:      " << NS << std::endl;
    std::cout << "    Number of Energy modes: " << NE << std::endl;
    std::cout << "     -> Ttra: " << m_T[TRA] << std:: endl;
    
    std::cout << "     -> Trot: " << m_T[ROT];
    if (NONEQ[ROT] == YES) std::cout << " --> Rotational Energy Nonequilibrium";
    std::cout << std:: endl;
    
    std::cout << "     -> Tvib: " << m_T[VIB];
    if (NONEQ[VIB] == YES) std::cout << " --> Vibrational Energy Nonequilibrium";
    std::cout << std:: endl;
    
    std::cout << "     -> Telc: " << m_T[ELC];
    if (NONEQ[ELC] == YES)
    {
        std::cout << " --> Electronic Energy Nonequilibrium";
        if (SeparateModeElc == YES) std::cout << "(Seperate mode)";
        else                        std::cout << "(Same mode to Vibrational Energy)";
    }
    std::cout << std:: endl;
    
    std::cout << "     -> Tele: " << m_T[ELE];
    if (NONEQ[ELE] == YES)
    {
        std::cout << " --> Electron Energy Nonequilibrium";
        if (SeparateModeEle == YES) std::cout << "(Seperate mode)";
        else                        std::cout << "(Same mode to Vibrational Energy)";
    }
    std::cout << std:: endl;
}


void variableMap::adjust()
{
    if (HasMolecule == NO)
    {
        NONEQ[ROT] = NO;
        NONEQ[VIB] = NO;
    }
    
    if (HasElectron == NO) NONEQ[ELE] = NO;
    
    if (NONEQ[VIB] == NO && NONEQ[ELC] == YES)                      SeparateModeElc = YES;
    if (NONEQ[VIB] == NO && NONEQ[ELC] == NO && NONEQ[ELE] == YES)  SeparateModeElc = YES;
}





int variableMap::RHO_globalID(unsigned int s)
{
    return (m_rho_s_global_ID[s]);
}


void variableMap::setTemperatureModes(std::vector<int>& noneq, int flag_elc, int flag_ele)
{
    NONEQ = noneq;
    SeparateModeElc = flag_elc;
    SeparateModeEle = flag_ele;
    
    setTemperatureModes();
}


void variableMap::setTemperatureModes()
{
    NE = 0;
    
    m_T[TRA] = 0; NE++;
    
    if (NONEQ[ROT] == YES)
    {
        m_T[ROT] = NE;
        NE++;
    }
    else
    {
        m_T[ROT] = m_T[TRA];
    }
    
    
    if (NONEQ[VIB] == YES)
    {
        m_T[VIB] = NE;
        NE++;
    }
    else
    {
        m_T[VIB] = m_T[TRA];
    }
    
    
    if (NONEQ[ELC] == YES)
    {
        if (SeparateModeElc == YES)
        {
            m_T[ELC] = NE;
            NE++;
        }
        else
        {
            m_T[ELC] = m_T[VIB];
        }
    }
    else
    {
        m_T[ELC] = m_T[TRA];
    }
    
    if (NONEQ[ELE] == YES)
    {
        if (SeparateModeEle == YES)
        {
            m_T[ELE] = NE;
            NE++;
        }
        else
        {
            m_T[ELE] = m_T[VIB];
        }
    }
    else
    {
        m_T[ELE] = m_T[TRA];
    }
}



