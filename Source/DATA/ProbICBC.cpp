//
//  ProbICBC.cpp
//  OP2A
//
//  Created by Kim M.K. on 08/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include "../COMM/assert_mk.hpp"
#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"
#include "../COMM/MultiVector.hpp"
#include "../COMM/VectorCompare.hpp"

#include "ProbICBC.hpp"
#include "problemDef.hpp"


ProbICBC_ver1::ProbICBC_ver1()
:iniMethod(0)
{
    
}

ProbICBC_ver1::ProbICBC_ver1(int num)
: iniMethod(0), flowCond(num)
{
    
}


ProbICBC_ver1::~ProbICBC_ver1()
{
    
}


void ProbICBC_ver1::allocateData(int NS, int ND, int NE)
{
    for (int i = 0; i < flowCond.size(); i++)    flowCond[i].assignSize(NS, ND, NE);
}


void ProbICBC_ver1::read(const std::string& filename)
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
            ne = 5;
            
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
                if (tempDouble != -1.0)	flowCond[tempIndex].T[TRA] = tempDouble;
                
                tempDouble = -1.0;
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Tr: ");
                if (tempDouble != -1.0)	flowCond[tempIndex].T[ROT] = tempDouble;
                
                tempDouble = -1.0;
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Tv: ");
                if (tempDouble != -1.0)	flowCond[tempIndex].T[VIB] = tempDouble;
                
                tempDouble = -1.0;
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Tele: ");
                if (tempDouble != -1.0)	flowCond[tempIndex].T[ELC] = tempDouble;
                
                tempDouble = -1.0;
                tempDouble = Common::read_data_from_string::read_numeric<double>(line, "Te: ");
                if (tempDouble != -1.0)	flowCond[tempIndex].T[ELE] = tempDouble;
            }
        }
    }
    
    prob_file.close();
    
    U_inlet.resize(inletCond.size());
    Q_inlet.resize(inletCond.size());
    
    U_wall.resize(wallCond.size());
    Q_wall.resize(wallCond.size());
}



void ProbICBC_ver1::errorcheck_and_shows()
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
    
    
    std::cout << "[INITIAL AND BOUNDARY CONDITIONS]" << std::endl;
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
