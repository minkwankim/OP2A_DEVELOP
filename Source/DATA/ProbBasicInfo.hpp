//
//  ProbBasicInfo.hpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef ProbBasicInfo_hpp
#define ProbBasicInfo_hpp

#include <stdio.h>
#include <string>
#include "problemDef.hpp"



// Class for ProbBasicInfo ver 1.0
class ProbBasicInfo_ver1 {
public:
    std::string title;          // Title of Simulation
    int axisymmetric;           // Grid Info (Axis or not)
    double gridfactor;          // Grid Factor
    int cartesian_grid;         // Flag for Cartesian Grid
    
public:
    explicit ProbBasicInfo_ver1();
    ~ProbBasicInfo_ver1();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
};











// Class for ProbBasicInfo
class ProbBasicInfo : public CURRENT_VERSION_PROBBASIC
{
public:
    explicit ProbBasicInfo() : CURRENT_VERSION_PROBBASIC() { };
    ~ProbBasicInfo(){ };
};





#endif /* ProbBasicInfo_hpp */
