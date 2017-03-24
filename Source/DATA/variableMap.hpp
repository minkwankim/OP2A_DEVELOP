//
//  variableMap.hpp
//  OP2A
//
//  Created by Kim M.K. on 23/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef variableMap_hpp
#define variableMap_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "dataDef.hpp"




int energyMode(int NER, int NEV, int NEC, int NEE, int fluid);


class variableMap {
public:
    unsigned int     NS;
    unsigned int     ND;
    unsigned int     NE;
    
    int temperatureMode;
    std::vector<int> NONEQ;
    int SeparateModeElc;
    int SeparateModeEle;

    int HasMolecule;
    int HasIons;
    int HasElectron;
    
    std::vector<std::string>    temperatureName;
    
protected:
    std::vector<int> m_T;     // local energy mode
    std::vector<int> m_rho_s_global_ID;   // global species ID of rho_s
    
    
    // [Part B]: Section for Constructor/Destructor
public:
    variableMap();
    ~variableMap();
    
    // [Part C]: Functions
public:
    void setSpecies(int ns);
    void setRho(int s_local, int s_global);
    int  rho_s_ID(unsigned int s);
    bool hasGlobalSpecies(int s);
    
    void setDimension(int nd);

    void setTemperature(int NER, int NEV, int NEC, int NEE, int fluid);
    int Tid(unsigned int mode);
    
    void showInfo();
    void adjust();
    
    // Legacy Functyions
    int RHO_globalID(unsigned int s);
    void setTemperatureModes(std::vector<int>& noneq, int flag_elec, int flag_ele);
    void setTemperatureModes();

};






#endif /* variableMap_hpp */
