//
//  species.hpp
//  OP2A
//
//  Created by Kim M.K. on 24/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef species_hpp
#define species_hpp

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <string>

#include "../COMM/map1D.hpp"
#include "../COMM/assert_mk.hpp"
#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"
#include "../COMM/VectorCompare.hpp"

#include "electronicState.hpp"
#include "kev.hpp"





class speciesBasic {
public:
    double M;
    double h0;
    double D;
    double I;
    double q;
    int    type;
    
public:
    speciesBasic();
    ~speciesBasic();
    
    void read(const std::string& line);
};
class speciesNoneq
{
public:
    double Z_inf;
    double T_star;
    double T_ref;
    double omega;
    double d_ref;
    double q_rot_e;
    double theta_v;
    
    electronicState ele;
    relaxation_rate_e_v k_ev;
    
    
public:
    speciesNoneq();
    ~speciesNoneq();
    
    void read(const std::string& line);
    void read(const std::vector<std::string>& line, int mode);
    
};



class species {
public:
    std::string name;
    speciesBasic basic;
    speciesNoneq noneq;
    
    
public:
    species();
    ~species();
};


#endif /* species_hpp */
