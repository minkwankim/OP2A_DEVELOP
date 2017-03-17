//
//  ProbNumericalMethod.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "ProbNumericalMethod.hpp"

#include "../COMM/assert_mk.hpp"
#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"




/*
 * Class for Basic Numerical method
 *                                   - ver 1.0
 */
ProbNumericalMethodBase_ver1::ProbNumericalMethodBase_ver1()
: mode(0), conv_criterion(1.0e-5), t0(0.0), tMax(1.0), dt(0.0), dtMax(1.0e-3), iterMax(1e5), n(0)
{
    
};

ProbNumericalMethodBase_ver1::~ProbNumericalMethodBase_ver1()
{
    
};

void ProbNumericalMethodBase_ver1::read_Base(const std::string& filename)
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
    
    // Overall information read
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
}



void ProbNumericalMethodBase_ver1::errorcheck_and_shows_Base()
{
    // Basic Error Checking
    if (mode < 0 || mode > 2)           Common::ExceptionError(FromHere(), "[Numerical Medhod]: Wrong option is selected for mode.", Common::ErrorCodes::NotAllocated());
    if (conv_criterion > 1.0e10)        Common::ExceptionError(FromHere(), "[Numerical Medhod]: Value for convergence creterion is not appropreate.", Common::ErrorCodes::NoSuchValue());
    if (tMax > 1.0e10 || tMax< 0)       Common::ExceptionError(FromHere(), "[Numerical Medhod]: Value for max simulation time is not appropreate.", Common::ErrorCodes::NoSuchValue());
    if (tMax > 1.0e10 || dtMax< 0)      Common::ExceptionError(FromHere(), "[Numerical Medhod]: Value for max di is not appropreate.", Common::ErrorCodes::NoSuchValue());
    if (iterMax > 1e10 || iterMax< 0)   Common::ExceptionError(FromHere(), "[Numerical Medhod]: Value for max iteration is not appropreate.", Common::ErrorCodes::NoSuchValue());
    
    
    std::cout << "[NUMERICAL METHODS]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "SIMULATION MODE           : ";
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
    std::cout << "CONVERGENCE CRITERIA      : " << conv_criterion << std::endl;
    std::cout << "MAX SIMULATION TIME, [sec]: " << tMax << std::endl;
    std::cout << "MAX dt, [sec]             : " << dtMax << std::endl;
    std::cout << "MAX ITERATION             : " << iterMax << std::endl;
}



/*
 * Class for CFD method
 *                                   - ver 1.0
 */
ProbNumericalMethodCFD_ver1::ProbNumericalMethodCFD_ver1()
: order(1), timeIntegration(0), spatialIntegration(0), limiter(0), gradient(0), cflMethod(0), cflSat(100),
cfl(0.1), maxCFL(10.0), relaxation_invicid(1.0), relaxation_viscous(1.0), pressure_switch_factor(6.0),
SlipAccomodation(1.0)
{
    
};

ProbNumericalMethodCFD_ver1::~ProbNumericalMethodCFD_ver1()
{
    
};


void ProbNumericalMethodCFD_ver1::read_CFD(const std::string& filename)
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

void ProbNumericalMethodCFD_ver1::errorcheck_and_shows_CFD()
{
    std::string currentmodule = "[Numerical Method - CFD]";
    
    // Basic Error Check
    if (order < 0)                                         Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the order.", Common::ErrorCodes::Negative());
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
    
    
    
    
    std::cout << "ORDER                         : " << order << std::endl;
    std::cout << "TIME INTEGRATION              : ";
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
    
    
    std::cout << "SPARTIAL INTEGRATION          : ";
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
    
    std::cout << "FLUX LIMITER                  : ";
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
    
    std::cout << "GRADIENT CALCULATION          : ";
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
    
    std::cout << "CFL NUMBER INCREMENT METHOD   : " << cflMethod  << std::endl;
    std::cout << "MAX CFL NUMBER                : " << maxCFL << std::endl;
    std::cout << "FLUX RELEXATION (INVISCID)    : " << relaxation_invicid << std::endl;
    std::cout << "FLUX RELEXATION (VISCOUS)     : " << relaxation_viscous << std::endl;
    
    if (spatialIntegration == 1) std::cout << "PRESSURE S/W FACTOR           : "  << pressure_switch_factor << std::endl;
    std::cout << "SLIP ACCOMODATION COEFFICIENT : "  << SlipAccomodation << std::endl;
}





/*
 * Class for DSMC method
 *                                   - ver 1.0
 */
ProbNumericalMethodDSMC_ver1::ProbNumericalMethodDSMC_ver1()
{
    
}


ProbNumericalMethodDSMC_ver1::~ProbNumericalMethodDSMC_ver1()
{
    
}



/*
 * Class for Hybrid method
 *                                   - ver 1.0
 */
ProbNumericalMethodHybrid_ver1::ProbNumericalMethodHybrid_ver1()
{
    
}


ProbNumericalMethodHybrid_ver1::~ProbNumericalMethodHybrid_ver1()
{
    
}






/*
 * Class for Numerical Method
 */
ProbNumericalMethod::ProbNumericalMethod()
{
    
}

ProbNumericalMethod::~ProbNumericalMethod()
{
    
}



void ProbNumericalMethod::read(const std::string& filename)
{
    read_Base(filename);
    
    switch(mode)
    {
        case 0:
            read_CFD(filename);
            break;
            
        default:
            std::ostringstream error_message;
            error_message << "[Error in Numerical Method Setting]: " << mode << " is NOT supported mode.";
            Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::NotSupportedType());
            break;
    }
}



void ProbNumericalMethod::errorcheck_and_shows()
{
    errorcheck_and_shows_Base();
    std::cout << std::endl;
    switch(mode)
    {
        case 0:
            std::cout << " --> Detail CFD method settings <--" << std::endl;
            errorcheck_and_shows_CFD();
            break;
            
        default:
            std::ostringstream error_message;
            error_message << "[Error in Numerical Method Setting]: " << mode << " is NOT supported mode.";
            Common::ExceptionError(FromHere(), error_message.str(), Common::ErrorCodes::NotSupportedType());
            break;
    }
    std::cout << std::endl;
}


