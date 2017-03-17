//
//  problemSetup.hpp
//  OP2A
//
//  Created by Kim M.K. on 21/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef problemSetup_hpp
#define problemSetup_hpp

#include <stdio.h>
#include <string>


#include "ProbBasicInfo.hpp"
#include "ProbNumericalMethod.hpp"
#include "ProbPhysicalModel.hpp"
#include "ProbICBC.hpp"
#include "ProbMPI.hpp"
#include "ProbIO.hpp"

#include "../CHEM/species.hpp"

class ProbleSetup {
public:
    ProbBasicInfo           basicinfo;
    ProbNumericalMethod     numericalmethod;
    ProbPhysicalModel       physicalmodel;
    ProbICBC                boundaryconditions;
    ProbCOMP                computation;
    ProbIO                  inputoutput;
    
public:
    ProbleSetup()
    {
        
    };
    
    ~ProbleSetup()
    {
        
    };
    
    void read();
    void processing(std::vector<species>& speciesdata, int ND);
    void errorcheck_and_shows();
    
};


























#endif /* problemSetup_hpp */
