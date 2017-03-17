//
//  ProbBasicInfo.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "ProbBasicInfo.hpp"

#include "../COMM/assert_mk.hpp"
#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"


//////////////////////////////////////
// Class for ProbBasicInfo ver 1.0  //
//////////////////////////////////////
// Constructor and Destructor
ProbBasicInfo_ver1::ProbBasicInfo_ver1()
: axisymmetric(0), gridfactor(1.0), cartesian_grid(0)
{
    
};



ProbBasicInfo_ver1::~ProbBasicInfo_ver1()
{
    
};


void ProbBasicInfo_ver1::read(const std::string& filename)
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
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "Use Cartesian Grid:");
        if (tempInt != -1) cartesian_grid = tempInt;
    }
    
    problem_file.close();
}

void ProbBasicInfo_ver1::errorcheck_and_shows()
{
    if (title == " ") Common::ExceptionError(FromHere(), "[BASIC INFO]: problem title is not assigned.", Common::ErrorCodes::NotAllocated());
    if (axisymmetric != 0 && axisymmetric != 1) Common::ExceptionError(FromHere(), "[BASIC INFO]: Wrong option is selected for axisymmeric", Common::ErrorCodes::NotAllocated());
    
    
    std::cout << "[PROBLEM SETTING BASIC INFORMATION]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Axisymmeric Simulation: " << Common::StringOps::convertYesNo(axisymmetric) << std::endl << std::endl;
    std::cout << "USE Catesian Grid: " << Common::StringOps::convertYesNo(cartesian_grid) << std::endl << std::endl;

}



