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
#include "flowdatabase.hpp"

// 1. Basic seccion
class ProbBasicInfo {
public:
    std::string title;
    
    
public:
    ProbBasicInfo();
    ~ProbBasicInfo();
    
    void read(const std::string& filename);
};



// 2. Numerical Method Session
class ProbNumericalMethodCFD {
public:
    int order;                      // Flux calculation order
    int timeIntegration;            // Time integraion methods       (0: Explicit,  1: Point implcit,  2: Line implicit)
    int spatialIntegration;         // Spatical integration methods (0: FVS,       1: SW-FVS,         2: AUSM)
    int limiter;                    // Flux limiter                  (0: NONE       1: van Leer        2: Superbee)
    int gradient;                   // Gradient calculation method
    
    int    cflMethod;               // CFL number increasement Method
    int    cflSat;                  // Number of iteration before CFL = 1
    double cfl;                     // CFL number
    double maxCFL;                  // Maximum CFL number
    
    double relaxation_invicid;      // Relaxation factor for inviscid flux
    double relaxation_viscous;      // Relaxation facror for viscous flux
    double pressure_switch_factor;  // Pressure Switch Factor
    
    double SlipAccomodation;        // Accomodation coefficient for slip BC
    
public:
    ProbNumericalMethodCFD();
    ~ProbNumericalMethodCFD();
    
    void read(const std::string& filename);
};


class ProbNumericalMethod {
public:
    int mode;               // [0]CFD   [1]PIC-DSMC [2]Hybrid
    double conv_criterion;  // convergence criterion
    double t0;              // t0
    double tMax;            // Max t (or T end)
    double dt;              // time step
    double dtMax;           // Maximum time step
    
    int iterMax;            // Maximum number of iteration
    int n;                  // Current iteration
    
    ProbNumericalMethodCFD cfd;
    
public:
    ProbNumericalMethod();
    ~ProbNumericalMethod();
    
    void read(const std::string& filename);
};



// 3. Physical Modelling Session
class ProbPhysicalModel {
public:
    int NS;
    int NR;
    int NE;
    int tempModel;
    int multiTemp;
    
    int mixingRule;
    int viscosityModel;
    int diffusivityModel;
    int conductivityModel;
    double Le;
    
    int fluidModel;
    
    
    
public:
    ProbPhysicalModel();
    ~ProbPhysicalModel();
    
    void read(const std::string& filename);
};



// 4. IC/Bs
class ProbICBC {
public:
    int iniMethod;
    std::vector<int> inletCond;
    std::vector<int> wallCond;
    
    std::vector<flowDataBase>   flowCond;
    
    
public:
    ProbICBC();
    ProbICBC(int num);
    
    void allocateData(int NS, int ND, int NE);
    void read(const std::string& filename);
    
    ~ProbICBC();
    
    
};

































#endif /* problemSetup_hpp */
