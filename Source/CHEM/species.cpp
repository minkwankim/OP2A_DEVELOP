//
//  species.cpp
//  OP2A
//
//  Created by Kim M.K. on 24/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "species.hpp"


speciesBasic::speciesBasic()
: M(0), h0(0), D(0), I(0), q(0), type(0)
{
    
}

speciesBasic::~speciesBasic()
{
    
}

void speciesBasic::read(const std::string &line)
{
    sscanf(line.c_str(), "%lf %lf %lf %lf %lf %d", &M, &h0, &D, &I, &q, &type);
}


speciesNoneq::speciesNoneq()
: Z_inf(1.0), T_star(1.0), T_ref(273.0), omega(0.74), d_ref(3.1e-10), q_rot_e(1.0), theta_v(1.0)
{
    
}

speciesNoneq::~speciesNoneq()
{
    
}


void speciesNoneq::read(const std::string& line)
{
    sscanf(line.c_str(), "%lf %lf %lf %lf %lf %lf %lf", &Z_inf, &T_star, &T_ref, &omega, &d_ref, &q_rot_e, &theta_v);
}


void speciesNoneq::read(const std::vector<std::string>& line, int mode)
{
    switch (mode)
    {
        case 0:
            sscanf(line[0].c_str(), "%lf %lf %lf %lf %lf %lf %lf", &Z_inf, &T_star, &T_ref, &omega, &d_ref, &q_rot_e, &theta_v);
            break;
            
        case 1:
            ele.read(line);
            break;
            
        case 2:
            k_ev.read(line);
            break;

    }
}











species::species()
{
    
}


species::~species()
{
    
}