//
//  ProbICBC.hpp
//  OP2A
//
//  Created by Kim M.K. on 08/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef ProbICBC_hpp
#define ProbICBC_hpp

#include <stdio.h>
#include "flowdatabase.hpp"
#include "wallMaterial.hpp"

class ProbICBC_ver1 {
public:
    int iniMethod;
    std::vector<int>           inletCond;
    std::vector<int>           wallCond;
    std::vector<std::string>   wallMatName;
    std::vector<wallMaterial>  wallMat;
    std::vector<flowDataBase>  flowCond;
    
    std::vector< std::vector< std::vector<double> > > U_inlet;
    std::vector< std::vector< std::vector<double> > > Q_inlet;
    
    std::vector< std::vector< std::vector<double> > > U_wall;
    std::vector< std::vector< std::vector<double> > > Q_wall;
    
public:
    ProbICBC_ver1();
    ProbICBC_ver1(int num);
    ~ProbICBC_ver1();
    
    
    void allocateData(int NS, int ND, int NE);
    void read(const std::string& filename);
    void errorcheck_and_shows();
};



#endif /* ProbICBC_hpp */
