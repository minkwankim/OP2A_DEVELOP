//
//  temperatureFns.hpp
//  OP2A
//
//  Created by Kim M.K. on 06/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef temperatureFns_hpp
#define temperatureFns_hpp

#include <stdio.h>
#include <vector>

#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/noninstantiable.hpp"
#include "../CHEM/species.hpp"




// Basic Class for Temperature Solver
class temperatureSolverBasic {
public:
    double T0;
    double E;

protected:
    double error_limit;
    int    iter_limit;
    
public:
    temperatureSolverBasic();
    temperatureSolverBasic(int iter, double error);
    ~temperatureSolverBasic();
    
public:
    double fn(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
    double fn_p(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
    
    
    double solveTemp(std::vector<double>& rho_s, std::vector<species>& speciesdata, double Ein, int NS);
    
    virtual double e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS) = 0;
    virtual double rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS) = 0;
};



// 1. Vibrational NONEQ
class NEQ_vib : public temperatureSolverBasic
{
public:
    NEQ_vib()  {};
    NEQ_vib(int iter, double error) : temperatureSolverBasic(iter, error) {  };
    ~NEQ_vib()  {};
    
public:
    double e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
    double rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
};


// 2. Electrical NONEQ
class NEQ_elc : public temperatureSolverBasic
{
public:
    NEQ_elc()  {};
    NEQ_elc(int iter, double error) : temperatureSolverBasic(iter, error) {  };
    ~NEQ_elc()  {};
    
public:
    double e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
    double rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
};


// 3. Vibrational-Electrical NONEQ
class NEQ_ve : public temperatureSolverBasic
{
public:
    NEQ_ve()  {};
    NEQ_ve(int iter, double error) : temperatureSolverBasic(iter, error) {  };
    ~NEQ_ve()  {};
    
public:
    double e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
    double rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
};


// 4. Vibrational-Electrical-Electron NONEQ
class NEQ_vee : public temperatureSolverBasic
{
public:
    NEQ_vee()  {};
    NEQ_vee(int iter, double error) : temperatureSolverBasic(iter, error) {  };
    ~NEQ_vee()  {};
    
public:
    double e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
    double rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
};


// 5. Electrical-Electron NONEQ
class NEQ_ee : public temperatureSolverBasic
{
public:
    NEQ_ee()  {};
    NEQ_ee(int iter, double error) : temperatureSolverBasic(iter, error) {  };
    ~NEQ_ee()  {};
    
public:
    double e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
    double rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
};


// 6. Vibrational-Electron NONEQ
class NEQ_vibe : public temperatureSolverBasic
{
public:
    NEQ_vibe()  {};
    NEQ_vibe(int iter, double error) : temperatureSolverBasic(iter, error) {  };
    ~NEQ_vibe()  {};
    
public:
    double e(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
    double rho_Cv(std::vector<double>& rho_s, std::vector<species>& speciesdata, double T, int NS);
};

#endif /* temperatureFns_hpp */
