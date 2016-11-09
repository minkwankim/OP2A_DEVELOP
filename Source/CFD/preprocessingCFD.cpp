//
//  preprocessingCFD.cpp
//  OP2A
//
//  Created by Kim M.K. on 16/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//
#include <time.h>
#include <stdio.h>
#include "OP2ACFDversioninfo.hpp"
#include "../COMM/version.hpp"



/*
 * ==========================================
 * Pre-Processing Part I ver 1.0
 * ==========================================
 * It is initially developed by Min Kwan Kim
 *
 *                Last Updated
 *                             on 21/June/2016
 *                             by Min Kwan Kim
 */

// PART 1. Setting Version information
// [Please DO NOT CHANGE]

#include <mpi.h>
#include <omp.h>


void preProcessingPart1Version(int argc, char *argv[], double& t0)
{
    time_t m_t = time(0);
    struct	tm* m_now;
    
    m_now = localtime(& m_t);
    Common::version ver(CURRENT_MAIN_VERSION, CURRENT_SUB_VERSION,  m_now->tm_year + 1900, m_now->tm_mon + 1, m_now->tm_mday, CURRENT_VERSION_TYPE);
    ver.info();
    
    
    int num_threads;
    int max_threads;
    int micid;
    
    
    // Initiate MPI
    char *name;
    int *resultlen;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &micid);
    //MPI_Comm_size(MPI_COMM_WORLD, &proc_info.num_CPU);
    
    //int max_threads = omp_get_max_threads();
    //if (proc_info.num_CPU == 1) proc_info.num_threads = max_threads;
    //else						proc_info.num_threads = THREAD_PER_CPU;
}

