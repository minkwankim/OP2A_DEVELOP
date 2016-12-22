//
//  problemSetup.cpp
//  OP2A
//
//  Created by Kim M.K. on 21/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//
#include <omp.h>
#include <mpi.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "problemSetup.hpp"
#include "problemDef.hpp"

#include "../COMM/assert_mk.hpp"
#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"
#include "../COMM/VectorCompare.hpp"
#include "../COMM/timer.hpp"


ProbBasicInfo::ProbBasicInfo()
: axisymmetric(0), gridfactor(1.0)
{
    
};



ProbBasicInfo::~ProbBasicInfo()
{
    
};


void ProbBasicInfo::read(const std::string& filename)
{
    // 1. Open file to read
    std::ifstream problem_file;
    problem_file.open(filename.c_str());
    if (!problem_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Problem Setup file. Please check your Problem Setup file!", Common::ErrorCodes::FileSystem());
    }
    
    int         tempInt;
    double      tempDouble;
    std::string tempString;
    std::string line;
    
    // Over information read
    while (!problem_file.eof())
    {
        getline(problem_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        tempString = "";
        tempString = Common::read_data_from_string::read_string(line, PROB_SETUP_TITLE);
        if (tempString != "") title = tempString;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "Axisymmetric:");
        if (tempInt != -1) axisymmetric = tempInt;
        
        tempDouble = -1;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Grid Factor:");
        if (tempDouble != -1) gridfactor = tempDouble;
    }
    
    problem_file.close();
}

void ProbBasicInfo::errorcheck_and_shows()
{
    if (title == " ") Common::ExceptionError(FromHere(), "[BASIC INFO]: problem title is not assigned.", Common::ErrorCodes::NotAllocated());
    if (axisymmetric != 0 && axisymmetric != 1) Common::ExceptionError(FromHere(), "[BASIC INFO]: Wrong option is selected for axisymmeric", Common::ErrorCodes::NotAllocated());
    
    
    std::cout << "[PROBLEM SETTING BASIC INFORMATION]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Axisymmeric Simulation: " << Common::StringOps::convertYesNo(axisymmetric) << std::endl << std::endl;
}




// Class for Numerical Method Setting
// COMMON
ProbNumericalMethod::ProbNumericalMethod()
: mode(0), conv_criterion(1.0e-5), t0(0.0), tMax(1.0), dt(0.0), dtMax(1.0e-3),
  iterMax(1e5), n(0)
{
    
};

ProbNumericalMethod::~ProbNumericalMethod()
{
    
};

void ProbNumericalMethod::read(const std::string& filename)
{
    // 1. Open file to read
    std::ifstream problem_file;
    problem_file.open(filename.c_str());
    if (!problem_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Problem Setup file. Please check your Problem Setup file!", Common::ErrorCodes::FileSystem());
    }
    
    int         tempInt;
    double      tempDouble;
    std::string tempString;
    std::string line;
    
    // Over information read
    while (!problem_file.eof())
    {
        getline(problem_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_MODE);
        if (tempInt != -1) mode = tempInt;
       
        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_COV_CRI);
        if (tempDouble != -1.0) conv_criterion = tempDouble;

        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_DT_MAX);
        if (tempDouble != -1.0) dtMax = tempDouble;
        
        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_T_MAX);
        if (tempDouble != -1.0) tMax = tempDouble;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_N_MAX);
        if (tempInt != -1) iterMax = tempInt;
        
    }
    
    problem_file.close();
    
    switch (mode)
    {
        case 0:
            cfd.read(filename);
            break;
            
        default:
            Common::ExceptionError(FromHere(), "It is not supported MODE. Please check the mode in the problem setup", Common::ErrorCodes::NotSupportedType());
            break;
    }
}


// A. CFD
ProbNumericalMethodCFD::ProbNumericalMethodCFD()
: order(1), timeIntegration(0), spatialIntegration(0), limiter(0), gradient(0), cflMethod(0), cflSat(100),
  cfl(0.1), maxCFL(10.0), relaxation_invicid(1.0), relaxation_viscous(1.0), pressure_switch_factor(6.0),
  SlipAccomodation(1.0)
{
    
};

ProbNumericalMethodCFD::~ProbNumericalMethodCFD()
{
    
};


void ProbNumericalMethodCFD::read(const std::string& filename)
{
    // 1. Open file to read
    std::ifstream problem_file;
    problem_file.open(filename.c_str());
    if (!problem_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Problem Setup file. Please check your Problem Setup file!", Common::ErrorCodes::FileSystem());
    }
    
    int         tempInt;
    double      tempDouble;
    std::string tempString;
    std::string line;
    
    // Over information read
    while (!problem_file.eof())
    {
        getline(problem_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_CFD_ORDER);
        if (tempInt != -1) order = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_INTEGRATION_TIME);
        if (tempInt != -1) timeIntegration = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_INTEGRATION_SPACE);
        if (tempInt != -1) spatialIntegration = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_FLUX_LIMITER);
        if (tempInt != -1) limiter = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_GRADIENT_CALCULATION);
        if (tempInt != -1) gradient = tempInt;
        
    
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_CFL_MET);
        if (tempInt != -1) cflMethod = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_CFL_SAT);
        if (tempInt != -1) cflSat = tempInt;
        
        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_CFL_INI);
        if (tempDouble != -1.0) cfl = tempDouble;
        
        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_CFL_MAX);
        if (tempDouble != -1.0) maxCFL = tempDouble;
        
        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_REX_INV);
        if (tempDouble != -1.0) relaxation_invicid = tempDouble;
        
        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_REX_VIC);
        if (tempDouble != -1.0) relaxation_viscous = tempDouble;
        
        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_PRESSURE_SWITCH);
        if (tempDouble != -1.0) pressure_switch_factor = tempDouble;
        
        
        tempDouble = -1.0;
        tempDouble = Common::read_data_from_string::read_numeric<double>(line, PROB_SETUP_SLIP_ACCOM);
        if (tempDouble != -1.0) SlipAccomodation = tempDouble;
    }
    
    problem_file.close();
}

void ProbNumericalMethodCFD::errorcheck_and_shows()
{
    std::string currentmodule = "[Numerical Method - CFD]";
    
    
    if (order < 0)          Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the order.", Common::ErrorCodes::Negative());
    if (timeIntegration < 0 || timeIntegration > 2)        Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for time integration.", Common::ErrorCodes::NotSupportedType());
    if (spatialIntegration < 0 || spatialIntegration > 2)  Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for spartial integration.", Common::ErrorCodes::NotSupportedType());
    if (limiter < 0 || limiter > 3)                        Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for flux limiter option.", Common::ErrorCodes::NotSupportedType());
    if (gradient < 0 || gradient > 2)                      Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for gradient calculation method.", Common::ErrorCodes::NotSupportedType());
    if (cflMethod < 0 || cflMethod > 2)                    Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for CFL increment method.", Common::ErrorCodes::NotSupportedType());
    if (maxCFL < 0 || maxCFL > 1.0e5)                      Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for MAX CFL number.", Common::ErrorCodes::Negative());
    
    if (relaxation_invicid < 0 || relaxation_invicid > 1.0e5)      Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for Relaxation number for invicid flux.", Common::ErrorCodes::Negative());
    if (relaxation_viscous < 0 || relaxation_viscous > 1.0e5)      Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for Relaxation number for viscous flux.", Common::ErrorCodes::Negative());
    if (spatialIntegration == 1 && pressure_switch_factor < 0.0)   Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for Pressure Switch Factor.", Common::ErrorCodes::Negative());
    if (SlipAccomodation < 0.0 && SlipAccomodation >  1.0e10)      Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for Slip Accomodation coefficient.", Common::ErrorCodes::Negative());


    
    
    std::cout << "ORDER: " << order << std::endl;
    std::cout << "TIME INTEGRATION: ";
    switch (timeIntegration)
    {
        case 0:
            std::cout << "EXPLICIT METHOD";
            break;
            
        case 1:
            std::cout << "POINT-IMPLICIT METHOD";
            break;
            
        case 2:
            std::cout << "LINE-IMPLICIT METHOD";
            break;
    }
    std::cout << std::endl;
    
    
    std::cout << "SPARTIAL INTEGRATION: ";
    switch (spatialIntegration)
    {
        case 0:
            std::cout << "SW Flux Vector Splitting Method (SW-FVS)";
            break;
            
        case 1:
            std::cout << "Modified SW Flux Vector Splitting Method (SW-FVS)";
            break;
            
        case 2:
            std::cout << "AUSM";
            break;
    }
    std::cout << std::endl;
    
    std::cout << "FLUX LIMITER: ";
    switch (spatialIntegration)
    {
        case 0:
            std::cout << "NONE)";
            break;
            
        case 1:
            std::cout << "van Leer";
            break;
            
        case 2:
            std::cout << "Harmonic";
            break;
        
        case 3:
            std::cout << "Superbee";
            break;
            
    }
    std::cout << std::endl;

    std::cout << "GRADIENT CALCULATION: ";
    switch (spatialIntegration)
    {
        case 0:
            std::cout << "NODE BASED METHOD)";
            break;
            
        case 1:
            std::cout << "FACE BASED METHOD";
            break;
            
        case 2:
            std::cout << "CELL BASED METHOD";
            break;
    }
    std::cout << std::endl;
    
    std::cout << "CFL NUMBER INCREMENT METHOD: "  << cflMethod  << std::endl;
    std::cout << "MAX CFL NUMBER: " << maxCFL << std::endl;
    std::cout << "FLUX RELEXATION (INVISCID): " << relaxation_invicid << std::endl;
    std::cout << "FLUX RELEXATION (VISCOUS): "  << relaxation_viscous << std::endl;
    
    if (spatialIntegration == 1) std::cout << "PRESSURE S/W FACTOR: "  << pressure_switch_factor << std::endl;
    std::cout << "SLIP ACCOMODATION COEFFICIENT: "  << SlipAccomodation << std::endl;

    

    

}


void ProbNumericalMethod::errorcheck_and_shows()
{
    if (mode < 0 || mode > 2)           Common::ExceptionError(FromHere(), "[Numerical Medhod]: Wrong option is selected for mode.", Common::ErrorCodes::NotAllocated());
    if (conv_criterion > 1.0e10)        Common::ExceptionError(FromHere(), "[Numerical Medhod]: Value for convergence creterion is not appropreate.", Common::ErrorCodes::NoSuchValue());
    if (tMax > 1.0e10 || tMax< 0)       Common::ExceptionError(FromHere(), "[Numerical Medhod]: Value for max simulation time is not appropreate.", Common::ErrorCodes::NoSuchValue());
    if (tMax > 1.0e10 || dtMax< 0)      Common::ExceptionError(FromHere(), "[Numerical Medhod]: Value for max di is not appropreate.", Common::ErrorCodes::NoSuchValue());
    if (iterMax > 1e10 || iterMax< 0)   Common::ExceptionError(FromHere(), "[Numerical Medhod]: Value for max iteration is not appropreate.", Common::ErrorCodes::NoSuchValue());

    
    
    
    
    
    std::cout << "[NUMERICAL METHODS]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "SIMULATION MODE: ";
    switch (mode)
    {
        case 0:
            std::cout << "CFD";
            break;
            
        case 1:
            std::cout << "PIC-DSMC";
            break;
            
        case 2:
            std::cout << "Hybrid";
            break;
    }
    std::cout << std::endl;
    std::cout << "CONVERGENCE CRITERIA: " << conv_criterion << std::endl;
    std::cout << "MAX SIMULATION TIME, [sec]: " << tMax << std::endl;
    std::cout << "MAX dt, [sec]: " << dtMax << std::endl;
    std::cout << "MAX ITERATION: " << iterMax << std::endl;

    
    
    switch (mode)
    {
        case 0:
            cfd.errorcheck_and_shows();
            break;
    }
    
    std::cout << std::endl;
}





// 3. Physical Modelling Session
ProbPhysicalModel::ProbPhysicalModel()
: NS(0), NE(0), NR(0), tempModel(0),
  mixingRule(0), viscosityModel(0), diffusivityModel(0), conductivityModel(0), Le(1.0),
  fluidModel(1)
{
    
}

ProbPhysicalModel::~ProbPhysicalModel()
{
    
}

void ProbPhysicalModel::read(const std::string& filename)
{
    // 1. Open file to read
    std::ifstream problem_file;
    problem_file.open(filename.c_str());
    if (!problem_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Problem Setup file. Please check your Problem Setup file!", Common::ErrorCodes::FileSystem());
    }
    
    int         tempInt;
    double      tempDouble;
    std::string tempString;
    std::string line;
    std::string tempSpeciesList;
    
    // Over information read
    while (!problem_file.eof())
    {
        getline(problem_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_TEMP);
        if (tempInt != -1) tempModel = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_FLU);
        if (tempInt != -1) fluidModel = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_MIX_RULE);
        if (tempInt != -1) mixingRule = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_VIS);
        if (tempInt != -1) viscosityModel = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_DIF);
        if (tempInt != -1) diffusivityModel = tempInt;

        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_CON);
        if (tempInt != -1) conductivityModel = tempInt;

        tempDouble = -1;
        tempDouble = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_LEWIS);
        if (tempDouble != -1) Le = tempDouble;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "Species Number:");
        if (tempInt != -1) NS = tempInt;
        
        if (line == "Species List:")
        {
            getline(problem_file, line);
            Common::read_data_from_string::remove_comments(line, "%");
            tempSpeciesList = line;
        }
        
    }
    problem_file.close();

    
    switch (fluidModel)
    {
        case 1:
            NE = tempModel;
            break;
            
        case 2:
            if (tempModel >= 3) NE = tempModel -1;
            else                NE = tempModel;
            break;
            
        case 3:
            if (tempModel >= 3) NE = tempModel -1;
            else                NE = tempModel;
            break;
    }
    
    
    speciesList = Common::StringOps::getWords(tempSpeciesList);
}


void ProbPhysicalModel::errorcheck_and_shows()
{
    std::string currentmodule = "[Physical Models]";
    
    
    if (tempModel <= 0 || tempModel > 4)                  Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the temperature model.", Common::ErrorCodes::Negative());
    if (fluidModel <= 0 || fluidModel > 3)                Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the fluid model.", Common::ErrorCodes::Negative());
    if (mixingRule < 0 || mixingRule > 1)                 Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the mixing rule.", Common::ErrorCodes::Negative());
    if (viscosityModel < 0 || viscosityModel > 4)         Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for viscosity model.", Common::ErrorCodes::Negative());
    if (conductivityModel < 0 || conductivityModel > 4)   Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for thermal conductivity model.", Common::ErrorCodes::Negative());
    if (Le < 0 || Le > 1.0e10)                            Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for Lewis number.", Common::ErrorCodes::Negative());

    if (NS != speciesList.size())                         Common::ExceptionError(FromHere(), currentmodule + ": Species list does not match.", Common::ErrorCodes::Negative());
    
    
    
    std::cout << "[PHYSICAL MODELS]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "TEMPERATURE MODEL: ";
    switch (tempModel)
    {
        case 1:
            std::cout << "ONE-TEMPERATURE MODEL";
            break;
            
        case 2:
            std::cout << "PARK'S TWO-TEMPERATURE MODEL";
            break;
            
        case 3:
            std::cout << "THREE TEMPERATURE MODEL: T_TR, T_VE, T_E";
            break;
            
        case 4:
            std::cout << "FULL TEMPERATURE MODEL: T_TRA, T_ROT, T_VEE, T_E";
            break;
    }
    std::cout << std::endl;

    
    std::cout << "FLUID MODEL: ";
    switch (fluidModel)
    {
        case 1:
            std::cout << "SINGLE FLUID";
            break;
            
        case 2:
            std::cout << "TWO FLUID (HEAVY SPECIES /  ELECTRONS)";
            break;
            
        case 3:
            std::cout << "THREE FLUID (NEUTRALS / IONS / ELECGRONS)";
            break;
    }
    
    std::cout << "MIXING RULE: ";
    switch (fluidModel)
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
    std::cout << "NUMBER OF SPECIES:" << NS << std::endl;
    std::cout << "SPECIES LIST:" << std::endl;
    for (int s = 0; s < NS; s++) std::cout << "     - " << speciesList[s] << std::endl;
    std::cout << std::endl;
}




// 4. IC/Bs
ProbICBC::ProbICBC()
:iniMethod(0)
{
    
}

ProbICBC::ProbICBC(int num)
: iniMethod(0), flowCond(num)
{
    
}


ProbICBC::~ProbICBC()
{
    
}


void ProbICBC::allocateData(int NS, int ND, int NE)
{
    for (int i = 0; i < flowCond.size(); i++)    flowCond[i].assignSize(NS, ND, NE);
}


void ProbICBC::read(const std::string& filename)
{

    int     tempInt;
    int     tempInt2;
    int     tempIndex;
    double 	tempDouble;
    int     ns, nd, ne;
    
    std::string  tempText;
    std::string  tempText2;
    std::string  tempText3;
    std::string  textInlet    = PROB_SETUP_INLET;
    std::string  textWall     = PROB_SETUP_WALL;
    std::string  textWallMAT  = PROB_SETUP_WALL_MAT;
    textInlet   += "[";
    textWall    += "[";
    textWallMAT += "[";
    
    

    std::string	line;
    
    std::ifstream	prob_file;
    prob_file.open(filename.c_str());
    if (!prob_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Problem Setup file. Please check your Problem Setup file!", Common::ErrorCodes::FileSystem());
    }

    // READ PROBLEM SETUP DATA FILE
    int numIC= 0;

    while (! prob_file.eof())
    {
        getline(prob_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        // Read initialization method
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_INI_METHOD);
        if (tempInt != -1) iniMethod = tempInt;
        
        
        // Read Inlet condition setting
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, textInlet);
        if (tempInt != -1)
        {
            if (inletCond.size() < tempInt + 1) inletCond.resize(tempInt+1);
            
            tempText = textInlet;
            tempText += Common::StringOps::to_str<int>(tempInt);
            tempText += "]:";
            
            tempInt2 = -1;
            tempInt2 = Common::read_data_from_string::read_numeric<int>(line, tempText);
            if (tempInt2 != -1) inletCond[tempInt] = tempInt2;
        }
        
        // Read Wall condition setting
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, textWall);
        if (tempInt != -1)
        {
            if (wallCond.size() < tempInt + 1) wallCond.resize(tempInt+1);
            
            tempText = textWall;
            tempText += Common::StringOps::to_str<int>(tempInt);
            tempText += "]:";
            
            tempInt2 = -1;
            tempInt2 = Common::read_data_from_string::read_numeric<int>(line, tempText);
            if (tempInt2 != -1) wallCond[tempInt] = tempInt2;
        }
        
        
        
        // Read Wall Material
        // Read Wall condition setting
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, textWallMAT);
        if (tempInt != -1)
        {
            if (wallMatName.size() < tempInt + 1) wallMatName.resize(tempInt+1);
            
            tempText = textWallMAT;
            tempText += Common::StringOps::to_str<int>(tempInt);
            tempText += "]:";
            
            tempText2 = "";
            tempText2 = Common::read_data_from_string::read_string(line, tempText);
            if (tempText2 != "") wallMatName[tempInt] = tempText2;
        }
        
        
        
        // Read flow conditions
        tempIndex = -1;
        tempIndex = Common::read_data_from_string::read_numeric<int>(line, PROB_SETUP_INI_START);
        
        if (tempIndex >= 0)
        {
            // Resize Flow condition data
            if (flowCond.size() < tempIndex+1)  flowCond.resize(tempIndex+1);
            
            ns = 0;
            nd = 3;
            ne = 4;
            
            flowCond[tempIndex].u.resize(nd);
            flowCond[tempIndex].T.resize(ne);
            
            while (line != PROB_SETUP_INI_END)
            {
                getline(prob_file, line);
                Common::read_data_from_string::remove_comments(line, "%");
                
                tempText = "RHO[";
                tempInt  = -1;
                tempInt  = Common::read_data_from_string::read_numeric<int>(line, tempText);
                
                // SPECIES Density
                if (tempInt != -1)
                {
                    tempText3 = Common::StringOps::to_str<int>(tempInt);
                    tempText2 = tempText + tempText3 + "]:";
                    
                    tempDouble = -1.0;
                    tempDouble = Common::read_data_from_string::read_numeric<double>(line, tempText2);
                    
                    if (tempDouble != -1.0)
                    {
                        ns++;
                        if (flowCond[tempIndex].rhos.size() < tempInt +1)  flowCond[tempIndex].rhos.resize(tempInt + 1);
                        
                        flowCond[tempIndex].rhos[tempInt] = tempDouble;
                    }
                }
                
                // Velocity
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Vx:");
                if (tempDouble != -1) flowCond[tempIndex].u[0] = tempDouble;
                
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Vy:");
                if (tempDouble != -1) flowCond[tempIndex].u[1] = tempDouble;
                
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Vz:");
                if (tempDouble != -1) flowCond[tempIndex].u[2] = tempDouble;
                
                // Temperature
                tempDouble = -1.0;
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "T: ");
                if (tempDouble != -1.0)	flowCond[tempIndex].T[0] = tempDouble;
                    
                tempDouble = -1.0;
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Tr: ");
                if (tempDouble != -1.0)	flowCond[tempIndex].T[1] = tempDouble;
                
                tempDouble = -1.0;
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Tv: ");
                if (tempDouble != -1.0)	flowCond[tempIndex].T[2] = tempDouble;
                
                tempDouble = -1.0;
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Te: ");
                if (tempDouble != -1.0)	flowCond[tempIndex].T[3] = tempDouble;
            }
        }
    }
    
    prob_file.close();
}



void ProbICBC::errorcheck_and_shows()
{
    std::string currentmodule = "[ICs/BCs]";
    
    for (int i = 0; i < inletCond.size(); i++)
    {
        if (inletCond[i] < 0 || inletCond[i] > flowCond.size())   Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for inlet flow condition.", Common::ErrorCodes::ExceedLimit());
    }

    for (int i = 0; i < wallCond.size(); i++)
    {
        if (wallCond[i] < 0 || wallCond[i] > flowCond.size())   Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for wall condition.", Common::ErrorCodes::ExceedLimit());
    }
    
    if (wallCond.size() != wallMatName.size())   Common::ExceptionError(FromHere(), currentmodule + ": Wall material is not appropreately listed.", Common::ErrorCodes::ExceedLimit());

    
    std::cout << "[PHYSICAL MODELS]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "INITIALIZATION FLOW CONDITION: " << iniMethod << std::endl;
    for (int i = 0; i < inletCond.size(); i++)
    {
        std::cout << "INLET[" << i << "] FLOW CONDITION: " << inletCond[i] << std::endl;
    }
    
    
    for (int i = 0; i < wallCond.size(); i++)
    {
        std::cout << "WALL[" << i << "] FLOW CONDITION / MATERIAL: " << wallCond[i] << " / " << wallMatName[i] << std::endl;
    }
    
    std::cout << std::endl;
    
    
}



// 5. MPI Info
ProbCOMP::ProbCOMP()
: taskID(0), numTasks(1), thread(1), m_MPI(false), m_OpenMP(false), t(0.0), t0(0.0)
{
    
}

ProbCOMP::~ProbCOMP()
{
    
}

void ProbCOMP::setting(const int NP, const int Nthread)
{
    thread = Nthread;
    numTasks = NP;
    
    if (NP > 1) m_MPI = true;
    else        m_MPI = false;
    
    if (Nthread > 1) m_OpenMP = true;
    else             m_OpenMP = false;
}


void ProbCOMP::setting()
{
    if (numTasks > 1) m_MPI = true;
    else        m_MPI = false;
    
    if (thread > 1) m_OpenMP = true;
    else             m_OpenMP = false;
}


bool ProbCOMP::useMPI()
{
    return (m_MPI);
}

bool ProbCOMP::useVector()
{
    return (m_OpenMP);
}


void ProbCOMP::initialize(int argc, char **argv)
{
    if (m_MPI == true)
    {
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &taskID);
        MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
    }
    
    if (m_OpenMP == true)
    {
        omp_set_dynamic(0);     // Explicitly disable dynamic teams
        omp_set_num_threads(thread);
    }
    
    
    t0 = Common::dtime();
}


void ProbCOMP::read(const std::string& filename)
{
    std::string	line;
    int         tempInt;
    int         i;
    
    std::ifstream	prob_file;
    prob_file.open(filename.c_str());
    if (!prob_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Problem Setup file. Please check your Problem Setup file!", Common::ErrorCodes::FileSystem());
    }
    
    // READ PROBLEM SETUP DATA FILE
    
    while (! prob_file.eof())
    {
        getline(prob_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        sscanf(line.c_str(), "USE MPI: %i", &i);
        
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "THREAD PER NODE:");
        if (tempInt != -1) thread = tempInt;

    }
   
    prob_file.close();
 
    
    if (i == 1) m_MPI = true;
    else        m_MPI = false;
    
    if (thread > 1) m_OpenMP = true;
    else            m_OpenMP = false;
}


void ProbCOMP::errorcheck_and_shows()
{
    std::string currentmodule = "[COMPUTATIOAL PARAMETERS]";
    if (numTasks < 0)    Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the number of CPUs.", Common::ErrorCodes::Negative());
    if (thread < 0)      Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the number of THREAD.", Common::ErrorCodes::Negative());
    
    std::cout << "[COMOUTATIONAL PARAMETERS]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "USING MPI: " << Common::StringOps::convertYesNo(m_MPI) << std::endl;
    std::cout << "MAX NUMBER OF CPUs: " << numTasks << std::endl;
    std::cout << "USING VECTOR CALCULATION: " << Common::StringOps::convertYesNo(m_OpenMP) << std::endl;
    std::cout << "NUMBER OF THREAD PER NODE: " << thread << std::endl;
    std::cout << std::endl;
}







// 6. Input/Output Info
ProbIO::ProbIO()
{
    
}

ProbIO::~ProbIO()
{
    
}

void ProbIO::read(const std::string& filename)
{
    std::string	line;
    std::string	temp;

    
    std::ifstream	prob_file;
    prob_file.open(filename.c_str());
    if (!prob_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Problem Setup file. Please check your Problem Setup file!", Common::ErrorCodes::FileSystem());
    }
    
    // READ PROBLEM SETUP DATA FILE
    while (! prob_file.eof())
    {
        getline(prob_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        temp = Common::read_data_from_string::read_string(line, "SPECIES DATABASE:");
        if (temp != "") filename_speciesdatabase = temp;
        
        temp = Common::read_data_from_string::read_string(line, "WALL MATERIAL DATABASE:");
        if (temp != "") filename_wallmaterial = temp;
        
        temp = Common::read_data_from_string::read_string(line, "GRID FILE:");
        if (temp != "") filename_grid = temp;
        
        temp = Common::read_data_from_string::read_string(line, "OUTPUT FILE:");
        if (temp != "") filename_Output = temp;
    }
    
    prob_file.close();    
}

void ProbIO::errorcheck_and_shows()
{
    std::string currentmodule = "[I/O]";
    if (filename_ProblemSetup == "")    Common::ExceptionError(FromHere(), currentmodule + ": Problem setup file name is not provided.", Common::ErrorCodes::Negative());
    if (filename_grid == "")            Common::ExceptionError(FromHere(), currentmodule + ": Gridp file name is not provided.", Common::ErrorCodes::Negative());
    if (filename_speciesdatabase == "") Common::ExceptionError(FromHere(), currentmodule + ": Species database file name is not provided.", Common::ErrorCodes::Negative());
    if (filename_wallmaterial == "")    Common::ExceptionError(FromHere(), currentmodule + ": Wall material database file name is not provided.", Common::ErrorCodes::Negative());
    if (filename_Output == "")          Common::ExceptionError(FromHere(), currentmodule + ": Output file name is not provided.", Common::ErrorCodes::Negative());

    std::cout << "[I/O]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << " PROBLEM SETUP FILENAME          : " << filename_ProblemSetup << std::endl;
    std::cout << " GRID FILENAME                   : " << filename_grid << std::endl;
    std::cout << " SPECIES DATABASE SETUP FILENAME : " << filename_speciesdatabase << std::endl;
    std::cout << " WALL MATERIAL DATABASE FILENAME : " << filename_wallmaterial << std::endl;
    std::cout << " OUTOUT FILENAME                 : " << filename_Output << std::endl;
    std::cout << std::endl;
}





// ProblemSetup Class
void ProbleSetup::read()
{
    basicinfo.read(inputoutput.filename_ProblemSetup);
    numericalmethod.read(inputoutput.filename_ProblemSetup);
    physicalmodel.read(inputoutput.filename_ProblemSetup);
    boundaryconditions.read(inputoutput.filename_ProblemSetup);
    computation.read(inputoutput.filename_ProblemSetup);
    inputoutput.read(inputoutput.filename_ProblemSetup);
    
}


void ProbleSetup::errorcheck_and_shows()
{
    std::cout << " -> ERROR CHECKING ON INPUT DATA AND SHOW THE SETTING" << std::endl;
    basicinfo.errorcheck_and_shows();
    numericalmethod.errorcheck_and_shows();
    physicalmodel.errorcheck_and_shows();
    boundaryconditions.errorcheck_and_shows();
    computation.errorcheck_and_shows();
    inputoutput.errorcheck_and_shows();
    std::cout << "[DONE]" << std::endl << std::endl;

}


