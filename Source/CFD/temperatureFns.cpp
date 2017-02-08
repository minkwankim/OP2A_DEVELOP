//
//  temperatureFns.cpp
//  OP2A
//
//  Created by Kim M.K. on 06/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "temperatureFns.hpp"

temperatureSolverBasic::temperatureSolverBasic()
: error_limit(1.0e-3), iter_limit(1000), T0(100.0), E(0.0)
{
    
}

temperatureSolverBasic::temperatureSolverBasic(int iter, double error)
: error_limit(error), iter_limit(iter), T0(100.0), E(0.0)
{
    
}


temperatureSolverBasic::~temperatureSolverBasic()
{

}


double temperatureSolverBasic::solveTemp(std::vector<double>& rho_s, std::vector<species>& speciesdata, double Ein, int NS)
{
    int n = 0;
    double half_PI = 0.5 * 3.141592;
    double T_old, T_new;
    double f_old, f_new;
    
    

    // 1. Finding lower and upper limits
    E    = Ein;
    T_old = T0;
    f_old = fn(rho_s, speciesdata, T_old, NS);
    
    double Tmin, Tmax;
    double dT = 100.0;
    
    
    
    if (f_old == 0.0)
    {
        return (T_old);
    }
    else if (f_old < 0.0)
    {
        Tmin = T0;
        n    = 0;
        
        while (f_old < 0.0 && n < iter_limit)
        {
            T_old += dT;
            f_old = fn(rho_s, speciesdata, T_old, NS);
            
            if (f_old == 0.0) return (T_old);
            n++;
        }
        
        if (f_old > 0) Tmax = T_old;
        else           Common::ExceptionError(FromHere(), "Problem in finding Tmax. Increase n_limit", Common::ErrorCodes::NoSuchValue());
    }
    else
    {
        Tmax = T0;
        n    = 0;
        
        while (f_old > 0.0 && n < iter_limit)
        {
            double aux = T_old - dT;
            if (aux <= 0.0)
            {
                T_old = 0.9*T_old;
                dT    = 0.5*dT;
            }
            else
            {
                T_old = aux;
            }
            
            f_old = fn(rho_s, speciesdata, T_old, NS);
            
            if (f_old == 0.0) return (T_old);
            n++;
        }
        
        if (f_old < 0) Tmin = T_old;
        else           Common::ExceptionError(FromHere(), "Problem in finding Tmax. Increase n_limit", Common::ErrorCodes::NoSuchValue());

    }
    

    // Method 1 (Newton-Raphson)
    double error = 1.0;
    double fp_old;
    
    T_old = Tmax;
    while (n < iter_limit && error > error_limit)
    {
        f_old  = fn(rho_s, speciesdata, T_old, NS);
        fp_old = fn_p(rho_s, speciesdata, T_old, NS);
        dT     = f_old/fp_old;
        
        error = fabs(dT);
        T_new = T_old - dT;
        
        if (error <= error_limit) return (T_new);
        else                      T_old = T_new;
        
        
        if(T_old < Tmin) T_old = Tmin - 5.0*atan(dT)/half_PI;
        if(T_old > Tmax) T_old = Tmax + 5.0*atan(dT)/half_PI;
        n++;
    }
    
    
    // Method 2 (Search Temprature)
    n     = 0;
    error = 1.0;
    dT    = 100.0;
    T_old = Tmax;
    
    while (n < iter_limit && error > error_limit)
    {
        f_old  = fn(rho_s, speciesdata, T_old, NS);

        if (fabs(f_old) > error_limit)
        {
            if (f_old > 0.0)
            {
                dT    = 1.5*dT;
                T_old = T_old - dT;
            }
            else
            {
                dT    = 0.5*dT;
                T_old = T_old + dT;
            }
        }
        else
        {
            return (T_old);
        }
        
        n++;
    }
    
    Common::ExceptionError(FromHere(), "CANNOT Find Solution", Common::ErrorCodes::NoSuchValue());
    return (T0);
}


double temperatureSolverBasic::fn(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    return (e(rho_s, speciesdata, T, NS) - E);
}

double temperatureSolverBasic::fn_p(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    return (rho_Cv(rho_s, speciesdata, T, NS));
}





// 1. Vibrational NONEQ
double NEQ_vib::e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double Evib = 0.0;
    for (int s = 0; s < NS; s++) Evib += speciesdata[s].e_vib(T) * rho_s[s];
    
    return (Evib);
}


double NEQ_vib::rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double aux = 0.0;
    for (int s = 0; s < NS; s++) aux += speciesdata[s].Cv_vib(T) * rho_s[s];
    
    return (aux);
}


// 2. Electrical NONEW
double NEQ_elc::e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double Eelc = 0.0;
    for (int s = 0; s < NS; s++) Eelc += speciesdata[s].e_elc(T) * rho_s[s];
    
    return (Eelc);
}


double NEQ_elc::rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double aux = 0.0;
    for (int s = 0; s < NS; s++) aux += speciesdata[s].Cv_elc(T) * rho_s[s];
    
    return (aux);
}


// 3. Vibrational-Electrical NONEQ
double NEQ_ve::e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double Eve = 0.0;
    for (int s = 0; s < NS; s++) Eve += (speciesdata[s].e_vib(T) + speciesdata[s].e_elc(T)) * rho_s[s];
    
    return (Eve);
}


double NEQ_ve::rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double aux = 0.0;
    for (int s = 0; s < NS; s++) aux += (speciesdata[s].Cv_vib(T) + speciesdata[s].Cv_elc(T)) * rho_s[s];
    
    return (aux);
}


// 4. Vibrational-Electrical-Electron NONEQ
double NEQ_vee::e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double Evee = 0.0;
    for (int s = 0; s < NS; s++) Evee += (speciesdata[s].e_vib(T) + speciesdata[s].e_elc(T) + speciesdata[s].e_ele(T)) * rho_s[s];
    
    return (Evee);
}


double NEQ_vee::rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double aux = 0.0;
    for (int s = 0; s < NS; s++) aux += (speciesdata[s].Cv_vib(T) + speciesdata[s].Cv_elc(T) +speciesdata[s].Cv_ele(T)) * rho_s[s];
    
    return (aux);
}


// 5. Electrical-Electron NONEQ
double NEQ_ee::e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double Eee = 0.0;
    for (int s = 0; s < NS; s++) Eee += (speciesdata[s].e_elc(T) + speciesdata[s].e_ele(T)) * rho_s[s];
    
    return (Eee);
}


double NEQ_ee::rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double aux = 0.0;
    for (int s = 0; s < NS; s++) aux += (speciesdata[s].Cv_elc(T) +speciesdata[s].Cv_ele(T)) * rho_s[s];
    
    return (aux);
}


// 6. Vibrational-Electron NONEQ
double NEQ_vibe::e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double Evibe = 0.0;
    for (int s = 0; s < NS; s++) Evibe += (speciesdata[s].e_vib(T) + speciesdata[s].e_ele(T)) * rho_s[s];
    
    return (Evibe);
}


double NEQ_vibe::rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS)
{
    double aux = 0.0;
    for (int s = 0; s < NS; s++) aux += (speciesdata[s].Cv_vib(T) +speciesdata[s].Cv_ele(T)) * rho_s[s];
    
    return (aux);
}