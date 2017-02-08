//
//  ProbPhysicalModel.hpp
//  OP2A
//
//  Created by Kim M.K. on 23/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef ProbPhysicalModel_hpp
#define ProbPhysicalModel_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/map1D.hpp"
#include "../CHEM/species.hpp"
#include "variableMap.hpp"



#define PROB_SETUP_NUM_FLUID            "Number of Fluids:"
#define PROB_SETUP_MIX_RULE             "Mixing Rule:"
#define PROB_SETUP_VISCOSITY            "Viscosity Model:"
#define PROB_SETUP_DIFFUSITY            "Diffusivity Model:"
#define PROB_SETUP_CONDUCTIVITY         "Conductivity Model:"
#define PROB_SETUP_LEWIS                "Lewis number:"
#define PROB_SETUP_SPECIES              "Species List:"


int temperatureMode(std::string& temp);
std::string temperatureModeStr(int m);



class ProbPhysicalModel_ver1 {
public:
    // Transport Properties
    int    mixingRule;
    int    viscosityModel;
    int    diffusivityModel;
    int    conductivityModel;
    double Le;
    
    // SIMULATION SETTING (SPECIES / ENERGY)
    int num_fluid;
    int NS_tot;
    std::vector<std::string>        speciesList;
    Common::Map1D<std::string, int> speciesMap;
    
    std::vector<variableMap>        variableSetting;

    std::vector<int> atomic_species;
    std::vector<int> molecular_species;
    int              electron;
    
    //      [Part B]: Constructor / Destructor
public:
    ProbPhysicalModel_ver1();
    ~ProbPhysicalModel_ver1();
    
    
    //      [Part C]: Functions
public:
    void read(const std::string& filename);
    void speciesMapping(std::vector<species>& speciesdata, int ND);
    void errorcheck_and_shows();
};








#endif /* ProbPhysicalModel_hpp */
