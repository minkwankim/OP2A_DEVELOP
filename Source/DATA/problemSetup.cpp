//
//  problemSetup.cpp
//  OP2A
//
//  Created by Kim M.K. on 21/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//
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


ProbBasicInfo::ProbBasicInfo()
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
    }
    
    problem_file.close();
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






// 3. Physical Modelling Session
ProbPhysicalModel::ProbPhysicalModel()
: NS(0), NE(0), NR(0), tempModel(0), multiTemp(0),
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
    }
    
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
    
    problem_file.close();
}





// 4. IC/Bs
ProbICBC::ProbICBC()
:iniMethod(0), inletCond(10, 0), wallCond(10, 0)
{
    
}

ProbICBC::ProbICBC(int num)
: iniMethod(0), inletCond(10, 0), wallCond(10, 0), flowCond(num)
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
    std::string  textInlet = PROB_SETUP_INLET;
    std::string  textWall  = PROB_SETUP_WALL;
    textInlet += "[";
    textWall += "[";
    
    

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















