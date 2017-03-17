//
//  ProbMPI.hpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef ProbMPI_hpp
#define ProbMPI_hpp

#include <stdio.h>
#include <string>
#include "problemDef.hpp"


class ProbCOMP_ver1 {
public:
    int taskID;
    int numTasks;
    int thread;
    
    double t0;
    double t;
    
protected:
    bool m_MPI;
    bool m_OpenMP;
    
public:
    ProbCOMP_ver1();
    ~ProbCOMP_ver1();
    
    void setting();
    void setting(const int NP, const int Nthread);
    void initialize(int argc, char **argv);
    
    bool useMPI();
    bool useVector();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
};




class ProbCOMP : public  CURRENT_VERSION_PROBCOMP
{
public:
    
    
public:
    ProbCOMP()  {  };
    ~ProbCOMP() {  };
};



#endif /* ProbMPI_hpp */
