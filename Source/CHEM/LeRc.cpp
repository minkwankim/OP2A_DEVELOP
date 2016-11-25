//
//  LeRc.cpp
//  OP2A
//
//  Created by Kim M.K. on 24/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "LeRc.hpp"



LeRc::LeRc()
:lvl(0)
{
    
}


LeRc::~LeRc()
{
    
}


void LeRc::read(const int num, const std::vector<std::string>& line)
{
    int s = 0;
    double temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9;
    double tempT1, tempTu, temphf;
    
    lvl = num;
    hf.resize(lvl);
    T1.resize(lvl);
    Tu.resize(lvl);
    A0.resize(lvl);
    A1.resize(lvl);
    A2.resize(lvl);
    A3.resize(lvl);
    A4.resize(lvl);
    A5.resize(lvl);
    A6.resize(lvl);
    A7.resize(lvl);
    A8.resize(lvl);
    A9.resize(lvl);
    
    
    for (int i = 0; i < lvl; i++)
    {
        sscanf(line[i].c_str(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
               &hf[i], &T1[i], &Tu[i], &A0[i], &A1[i], &A2[i], &A3[i], &A4[i], &A5[i], &A6[i], &A7[i], &A8[i], &A9[i]);
    }
}


void LeRc::read(const std::vector<std::string>& line)
{
    int s = 0;
    double temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9;
    double tempT1, tempTu, temphf;
    
    hf.resize(lvl);
    T1.resize(lvl);
    Tu.resize(lvl);
    A0.resize(lvl);
    A1.resize(lvl);
    A2.resize(lvl);
    A3.resize(lvl);
    A4.resize(lvl);
    A5.resize(lvl);
    A6.resize(lvl);
    A7.resize(lvl);
    A8.resize(lvl);
    A9.resize(lvl);
    
    
    for (int i = 0; i < lvl; i++)
    {
        sscanf(line[i].c_str(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
               &hf[i], &T1[i], &Tu[i], &A0[i], &A1[i], &A2[i], &A3[i], &A4[i], &A5[i], &A6[i], &A7[i], &A8[i], &A9[i]);
    }

}