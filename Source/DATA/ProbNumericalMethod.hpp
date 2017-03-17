//
//  ProbNumericalMethod.hpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef ProbNumericalMethod_hpp
#define ProbNumericalMethod_hpp

#include <stdio.h>
#include <string>
#include "problemDef.hpp"




/*
 * Class for Basic Numerical method
 *                                   - ver 1.0
 */
class ProbNumericalMethodBase_ver1 {
public:
    int     mode;            // [0]CFD   [1]PIC-DSMC [2]Hybrid
    double  conv_criterion;  // convergence criterion
    double  t0;              // t0    (Starting time)
    double  tMax;            // Max t (or T end)
    double  dtMax;           // Maximum time step
    int     iterMax;         // Maximum number of iteration

    // Variables
    double  dt;              // time step
    int     n;               // Current iteration
    
public:
    ProbNumericalMethodBase_ver1();
    ~ProbNumericalMethodBase_ver1();
    
    void read_Base(const std::string& filename);
    void errorcheck_and_shows_Base();
};



/*
 * Class for CFD method
 *                                   - ver 1.0
 */
class ProbNumericalMethodCFD_ver1 {
public:
    int    order;                   // Flux calculation order
    int    timeIntegration;         // Time integration methods       (0: Explicit,  1: Point implicit,  2: Line implicit)
    int    spatialIntegration;      // Spartical integration methods  (0: SW-FVS,    1: Modified SW-FVS, 2: AUSM)
    int    limiter;                 // Flux limiter                   (0: NONE       1: van Leer        2: Superbee)
    int    gradient;                // Gradient calculation method
    int    cflMethod;               // CFL number increasement Method
    int    cflSat;                  // Number of iteration before CFL = 1
    double cfl;                     // CFL number
    double maxCFL;                  // Maximum CFL number
    
    double relaxation_invicid;      // Relaxation factor for inviscid flux
    double relaxation_viscous;      // Relaxation facror for viscous flux
    double pressure_switch_factor;  // Pressure Switch Factor
    double SlipAccomodation;        // Accomodation coefficient for slip BC
    
public:
    ProbNumericalMethodCFD_ver1();
    ~ProbNumericalMethodCFD_ver1();
    
    void read_CFD(const std::string& filename);
    void errorcheck_and_shows_CFD();
};



/*
 * Class for DSMC method
 *                                   - ver 1.0
 */
class ProbNumericalMethodDSMC_ver1 {
public:
    
public:
    ProbNumericalMethodDSMC_ver1();
    ~ProbNumericalMethodDSMC_ver1();
};



/*
 * Class for Hybrid method
 *                                   - ver 1.0
 */
class ProbNumericalMethodHybrid_ver1 {
public:
    
public:
    ProbNumericalMethodHybrid_ver1();
    ~ProbNumericalMethodHybrid_ver1();
};




/*
 * Class for Numerical Method
 */
class ProbNumericalMethod
: public CURRENT_VERSION_PROBNUMCOM,
  public CURRENT_VERSION_PROBNUMCFD,
  public CURRENT_VERSION_PROBNUMDSMC,
  public CURRENT_VERSION_PROBNUMHYBR
{
public:
    
public:
    ProbNumericalMethod();
    ~ProbNumericalMethod();
    
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
};




#endif /* ProbNumericalMethod_hpp */
