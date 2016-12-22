//
//  species.cpp
//  OP2A
//
//  Created by Kim M.K. on 24/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "species.hpp"




// 1. Basic DATA
speciesBasic::speciesBasic()
: M(0), m(0), h0(0), D(0), I(0), q(0), type(0), R(0), m_completed(false)
{
    
}

speciesBasic::~speciesBasic()
{
    
}

void speciesBasic::read(const std::string &line)
{
    sscanf(line.c_str(), "%lf %lf %lf %lf %lf %d", &M, &h0, &D, &I, &q, &type);
    
    m = M *AMU_SI;
    R = Ru_SI / M;
    
    Cv[0] = 1.5*R;
    if (type == 1) Cv[1] = R;
    else           Cv[0] = 0.0;
    
    m_completed = true;
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


// 3. Transport DATA
speciesTrans::speciesTrans()
{
    
}

speciesTrans::~speciesTrans()
{
    
}

void speciesTrans::read(const std::string& line, int mode)
{
    switch (mode)
    {
        case 0: // Blottner
            sscanf(line.c_str(), "%lf %lf %lf", &blottner.A, &blottner.B, &blottner.C);
            break;
            
        case 1: // Sutherland
            sscanf(line.c_str(), "%lf %lf %lf %lf %lf %lf", &sutherland.S, &sutherland.T_ref, &sutherland.mu_0, &sutherland.S_kappa, &sutherland.T0_kappa, &sutherland.kappa_0);
            break;
            
        case 2: // Kinetic theory model for viscosity
            sscanf(line.c_str(), "%lf %lf", &kinetic.sigma, &kinetic.Teps);
            break;
    }
}


double speciesTrans::kappa_Eucken(const double mus, const double Cvs, int mode)
{
    double kappa;
    
    if (mode == 0)
    {
        kappa = 2.5 * mus * Cvs;
    }
    else
    {
        kappa = mus * Cvs;
    }
    
    return(kappa);
}





species::species()
{
    
}


species::~species()
{
    
}