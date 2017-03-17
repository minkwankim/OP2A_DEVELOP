//
//  ProbIO.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "problemDef.hpp"

#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"

#include "ProbIO.hpp"


ProbIO_ver1::ProbIO_ver1()
{
    
}

ProbIO_ver1::~ProbIO_ver1()
{
    
}

void ProbIO_ver1::read(const std::string& filename)
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

void ProbIO_ver1::errorcheck_and_shows()
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
