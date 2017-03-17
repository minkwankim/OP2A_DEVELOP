//
//  ProbMPI.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include <omp.h>
#include <mpi.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "problemDef.hpp"

#include "../COMM/assert_mk.hpp"
#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"
#include "../COMM/MultiVector.hpp"
#include "../COMM/VectorCompare.hpp"
#include "../COMM/timer.hpp"

#include "ProbMPI.hpp"


ProbCOMP_ver1::ProbCOMP_ver1()
: taskID(0), numTasks(1), thread(1), m_MPI(false), m_OpenMP(false), t(0.0), t0(0.0)
{
    
}

ProbCOMP_ver1::~ProbCOMP_ver1()
{
    
}

void ProbCOMP_ver1::setting(const int NP, const int Nthread)
{
    thread = Nthread;
    numTasks = NP;
    
    if (NP > 1) m_MPI = true;
    else        m_MPI = false;
    
    if (Nthread > 1) m_OpenMP = true;
    else             m_OpenMP = false;
}


void ProbCOMP_ver1::setting()
{
    if (numTasks > 1) m_MPI = true;
    else        m_MPI = false;
    
    if (thread > 1) m_OpenMP = true;
    else             m_OpenMP = false;
}


bool ProbCOMP_ver1::useMPI()
{
    return (m_MPI);
}

bool ProbCOMP_ver1::useVector()
{
    return (m_OpenMP);
}


void ProbCOMP_ver1::initialize(int argc, char **argv)
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


void ProbCOMP_ver1::read(const std::string& filename)
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


void ProbCOMP_ver1::errorcheck_and_shows()
{
    std::string currentmodule = "[COMPUTATIOAL PARAMETERS]";
    if (numTasks < 0)    Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the number of CPUs.", Common::ErrorCodes::Negative());
    if (thread < 0)      Common::ExceptionError(FromHere(), currentmodule + ": Wrong value for the number of THREAD.", Common::ErrorCodes::Negative());
    
    std::cout << "[COMOUTATIONAL PARAMETERS]" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "USING MPI                 : " << Common::StringOps::convertYesNo(m_MPI) << std::endl;
    std::cout << "MAX NUMBER OF CPUs        : " << numTasks << std::endl;
    std::cout << "USING VECTOR CALCULATION  : " << Common::StringOps::convertYesNo(m_OpenMP) << std::endl;
    std::cout << "NUMBER OF THREAD PER NODE : " << thread << std::endl;
    std::cout << std::endl;
}

