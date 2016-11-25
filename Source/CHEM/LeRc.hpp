//
//  LeRc.hpp
//  OP2A
//
//  Created by Kim M.K. on 24/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef LeRc_hpp
#define LeRc_hpp

#include <stdio.h>
#include <string>
#include <vector>



class LeRc {
public:
    int lvl;
    std::vector<double> hf;
    std::vector<double> T1;
    std::vector<double> Tu;
    std::vector<double> A0;
    std::vector<double> A1;
    std::vector<double> A2;
    std::vector<double> A3;
    std::vector<double> A4;
    std::vector<double> A5;
    std::vector<double> A6;
    std::vector<double> A7;
    std::vector<double> A8;
    std::vector<double> A9;
    
public:
    LeRc();
    ~LeRc();
    
    void read(const int num, const std::vector<std::string>& line);
    void read(const std::vector<std::string>& line);    
};


#endif /* LeRc_hpp */
