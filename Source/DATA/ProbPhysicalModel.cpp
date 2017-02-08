//
//  ProbPhysicalModel.cpp
//  OP2A
//
//  Created by Kim M.K. on 23/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include <sstream>

#include "../COMM/assert_mk.hpp"
#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"
#include "../COMM/MultiVector.hpp"
#include "../COMM/VectorCompare.hpp"

#include "ProbPhysicalModel.hpp"

//      [Part B]: Constructor / Destructor
ProbPhysicalModel_ver1::ProbPhysicalModel_ver1()
: mixingRule(0), viscosityModel(0), diffusivityModel(0), conductivityModel(0), Le(1.0),
num_fluid(0), NS_tot(0)

{
    
}


ProbPhysicalModel_ver1::~ProbPhysicalModel_ver1()
{
    
}







//      [Part C]: Functions
void ProbPhysicalModel_ver1::read(const std::string& filename)
{
    // 1. Open file to read
    std::ifstream problem_file;
    
    problem_file.open(filename.c_str());
    if (!problem_file.is_open()) Common::ExceptionError(FromHere(), "Cannot find Problem Setup file. Please check your Problem Setup file!", Common::ErrorCodes::FileSystem());
    
    
    int         tempInt;
    double      tempDouble;
    std::string tempString;
    std::string line;
    std::string tempSpeciesList;
    std::string tempText;
    std::string tempSpecies;
    
    
    // Over information read
    while (!problem_file.eof())
    {
        // Remove Comments
        getline(problem_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        

        // Number of fluid
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_NUM_FLUID);
        if (tempInt != -1) num_fluid = tempInt;
        
        // Mixing rule
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_MIX_RULE);
        if (tempInt != -1) mixingRule = tempInt;
        
        
        // VISCOSITY MODEL
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_VISCOSITY);
        if (tempInt != -1) viscosityModel = tempInt;
        
        // DIFFUSITY
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_DIFFUSITY);
        if (tempInt != -1) diffusivityModel = tempInt;
        
        // CONDUCTIVITY
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_CONDUCTIVITY);
        if (tempInt != -1) conductivityModel = tempInt;
        
        // LEWIS NUMBER
        tempDouble = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_LEWIS);
        if (tempDouble != -1) Le = tempDouble;
        
        
        if (line.compare(0, 13, PROB_SETUP_SPECIES) == 0)
        {
            line.erase(0, sizeof(PROB_SETUP_SPECIES)-1);
            Common::StringOps::trimFront(line);
            tempSpeciesList = line;
        }
    }
    speciesList = Common::StringOps::getWords(tempSpeciesList);
    NS_tot = speciesList.size();
    for (int s = 0; s < NS_tot; s++)    speciesMap.insert(speciesList[s], s);
   
    
    
    // READ FILE for Fluid setting
    int f = 0;
    int s;
    int ner, nev, nec, nee;
    variableSetting.resize(num_fluid);
    
    problem_file.clear();
    problem_file.seekg(0,std::ios::beg);
    
    while (!problem_file.eof())
    {
        getline(problem_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        // Read Inlet condition setting
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "#FLUID SETTING[START]:");
        if (tempInt != -1)
        {
            f = tempInt;
            s = 0;
            if (variableSetting.size() < tempInt +1)    variableSetting.resize(tempInt + 1);
            

            ner = 0;
            nev = 0;
            nec = 0;
            nee = 0;
            
            while (line != "#FLUID SETTING[END]")
            {
                getline(problem_file, line);
                Common::read_data_from_string::remove_comments(line, "%");
                
                // SPECIES
                tempText = "RHO[";
                tempInt  = -1;
                tempInt  = Common::read_data_from_string::read_numeric<int>(line, tempText);
                
                if (tempInt != -1)
                {
                    tempText    = tempText + Common::StringOps::to_str<int>(tempInt) + "]:";
                    tempSpecies = Common::read_data_from_string::read_string(line, tempText);
                    
                    if (speciesMap.exists(tempSpecies) == true)
                    {
                        int g = speciesMap.find(tempSpecies);
                        variableSetting[f].setRho(s, g);
                        s++;
                    }
                    else
                    {
                        Common::ExceptionError(FromHere(), "Cannot find species!", Common::ErrorCodes::MismatchData());
                    }
                }
 
                
                tempInt  = Common::read_data_from_string::read_numeric<int>(line, "NONEQ ROT:");
                if (tempInt != -1) ner = tempInt;
                
                tempInt  = Common::read_data_from_string::read_numeric<int>(line, "NONEQ VIB:");
                if (tempInt != -1) nev = tempInt;
                
                tempInt  = Common::read_data_from_string::read_numeric<int>(line, "NONEQ ELC:");
                if (tempInt != -1) nec = tempInt;
                
                
                tempInt  = Common::read_data_from_string::read_numeric<int>(line, "NONEQ ELE:");
                if (tempInt != -1) nee = tempInt;
            }
            
            variableSetting[f].NS = s;
            variableSetting[f].setTemperature(ner, nev, nec, nee, 0);
        }
    }

    
    problem_file.close();
}


void ProbPhysicalModel_ver1::errorcheck_and_shows()
{
    std::ostringstream error_message;
    std::string currentmodule = "[Physical Models]";
    
        
    
    if (num_fluid <= 0)                                   Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for number of fluids.", Common::ErrorCodes::Negative());
    if (mixingRule < 0 || mixingRule > 1)                 Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the mixing rule.", Common::ErrorCodes::ExceedLimit());
    if (viscosityModel < 0 || viscosityModel > 4)         Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for viscosity model.", Common::ErrorCodes::ExceedLimit());
    if (conductivityModel < 0 || conductivityModel > 4)   Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for thermal conductivity model.", Common::ErrorCodes::ExceedLimit());
    if (Le < 0 || Le > 1.0e10)                            Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for Lewis number.", Common::ErrorCodes::ExceedLimit());
    if ((NS_tot) != speciesList.size())                   Common::ExceptionError(FromHere(), currentmodule + ": Species list does not match.", Common::ErrorCodes::Mismatch());
    if (num_fluid != variableSetting.size())              Common::ExceptionError(FromHere(), currentmodule + ": Fluid setting does not match with number of fluids.", Common::ErrorCodes::Mismatch());
    
    for (int f =0; f < num_fluid; f++) variableSetting[f].adjust();
    
    
    std::cout << "[PHYSICAL MODELS]" << std::endl;
    std::cout << "===================================" << std::endl;
    
    std::cout << "Number of fluids: " << num_fluid << std::endl;
    for (int f = 0; f < num_fluid; f++)
    {
        std::cout << "*Fluid Number [" << f << "]" << std::endl;
        variableSetting[f].showInfo();
        std::cout<<std::endl;
    }
    std::cout << "MIXING RULE: ";
    switch (mixingRule)
    {
        case 0:
            std::cout << "WILKE' RULE";
            break;
            
        case 1:
            std::cout << "GUPTA'S RULE";
            break;
    }
    std::cout << std::endl;
    
    
    std::cout << "VISCOSITY MODEL: ";
    switch (viscosityModel)
    {
        case 0:
            std::cout << "BLOTTNER MODEL";
            break;
            
        case 1:
            std::cout << "SUTHERLANDS MODEL";
            break;
            
        case 2:
            std::cout << "COLLISION CROSS SECTION MODEL";
            break;
            
        case 3:
            std::cout << "KINETIC THEORY MODEL";
            break;
    }
    std::cout << std::endl;
    
    
    std::cout << "VISCOSITY MODEL: ";
    switch (conductivityModel)
    {
        case 0:
            std::cout << "EUCKEN MODEL";
            break;
            
        case 1:
            std::cout << "SUTHERLANDS MODEL";
            break;
            
        case 2:
            std::cout << "COLLISION CROSS SECTION MODEL";
            break;
            
        case 3:
            std::cout << "KINETIC THEORY MODEL";
            break;
    }
    std::cout << std::endl;
    
    std::cout << "LEWIS NUMBER, Le: " << Le << std::endl;
    std::cout << "NUMBER OF SPECIES:" << NS_tot << std::endl;
    std::cout << "SPECIES LIST:" << std::endl;
    for (int s = 0; s < NS_tot; s++) std::cout << "     - " << speciesList[s] << std::endl;
    std::cout << std::endl;
}





void ProbPhysicalModel_ver1::speciesMapping(std::vector<species>& speciesdata, int ND)
{
    
    // Species Type Mapping
    int num_atom  = 0;
    int num_mole  = 0;
    
    for (int s = 0; s < NS_tot; s++)
    {
        switch(speciesdata[s].basic.type)
        {
            case 0: // Atomic Species
                if (atomic_species.size() < (num_atom+1)) atomic_species.resize(num_atom+1);
                atomic_species[num_atom] = s;
                num_atom++;
                break;
                
            case 1: // Molecular Species
                if (molecular_species.size() < (num_mole+1)) molecular_species.resize(num_mole+1);
                molecular_species[num_mole] = s;
                num_mole++;
                break;
                
            case -1: // Electron
                electron = s;
                break;
        }
    }
    
    
    for (int f = 0; f < num_fluid; f++)
    {
        variableSetting[f].ND = ND;
        
        variableSetting[f].HasMolecule = 0;
        for (int s = 0; s < variableSetting[f].NS; s++)
        {
            if (speciesdata[variableSetting[f].RHO_globalID(s)].basic.type == 1)
            {
                variableSetting[f].HasMolecule = 1;
                break;
            }
        }
        
        variableSetting[f].HasElectron = 0;
        for (int s = 0; s < variableSetting[f].NS; s++)
        {
            if (speciesdata[variableSetting[f].RHO_globalID(s)].basic.type == -1)
            {
                variableSetting[f].HasElectron = 1;
                break;
            }
        }
        
        variableSetting[f].HasIons = 0;
        for (int s = 0; s < variableSetting[f].NS; s++)
        {
            if (speciesdata[variableSetting[f].RHO_globalID(s)].basic.q != 0)
            {
                variableSetting[f].HasIons = 1;
                break;
            }
        }
        
        variableSetting[f].adjust();
        
        if ( variableSetting[f].NS == 1 && variableSetting[f].HasElectron == YES)
            variableSetting[f].setTemperature(variableSetting[f].NONEQ[1], variableSetting[f].NONEQ[2], variableSetting[f].NONEQ[3], variableSetting[f].NONEQ[4], -1);
        else
            variableSetting[f].setTemperature(variableSetting[f].NONEQ[1], variableSetting[f].NONEQ[2], variableSetting[f].NONEQ[3], variableSetting[f].NONEQ[4], 0);

    }
    
    
}









int temperatureMode(std::string& temp)
{
    int m;
    
    if (temp == "NONE")      m = -1;
    else if (temp == "Ttra") m = 0;
    else if (temp == "Trot") m = 1;
    else if (temp == "Tvib") m = 2;
    else if (temp == "Telc") m = 3;
    else if (temp == "Tele") m = 4;
    else                     m = -1;
    return(m);
}

std::string temperatureModeStr(int m)
{
    std::string temp;
    
    switch (m)
    {
    case 0:
        temp = "tra";
        break;
        
    case 1:
        temp = "rot";
        break;
        
    case 2:
        temp = "vib";
        break;
        
    case 3:
        temp = "elc";
        break;
        
    case 4:
        temp = "ele";
        break;
    }
    
    return (temp);
}









