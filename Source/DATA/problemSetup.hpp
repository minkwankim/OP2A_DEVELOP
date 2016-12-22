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
#include "wallMaterial.hpp"

// 1. Basic seccion
class ProbBasicInfo {
public:
    std::string title;
    int axisymmetric;
    double gridfactor;
    
    
    
public:
    ProbBasicInfo();
    ~ProbBasicInfo();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
};



// 2. Numerical Method Session
class ProbNumericalMethodCFD {
public:
    int order;                      // Flux calculation order
    int timeIntegration;            // Time integraion methods       (0: Explicit,  1: Point implcit,  2: Line implicit)
    int spatialIntegration;         // Spatical integration methods (0: SW-FVS,       1: Modified SW-FVS,         2: AUSM)
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
    void errorcheck_and_shows();
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
    void errorcheck_and_shows();
};



// 3. Physical Modelling Session
class ProbPhysicalModel {
public:
    int NS;
    int NR;
    int NE;
    int tempModel;
    //int multiTemp;
    
    int mixingRule;
    int viscosityModel;
    int diffusivityModel;
    int conductivityModel;
    double Le;
    
    std::vector<std::string> speciesList;
    
    
    int fluidModel;
    
    
    
public:
    ProbPhysicalModel();
    ~ProbPhysicalModel();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();

};



// 4. IC/Bs
class ProbICBC {
public:
    int iniMethod;
    std::vector<int>            inletCond;
    std::vector<int>            wallCond;
    std::vector<std::string>    wallMatName;
    std::vector<wallMaterial>   wallMat;
    
    std::vector<flowDataBase>   flowCond;
    
    
public:
    ProbICBC();
    ProbICBC(int num);
    ~ProbICBC();

    
    void allocateData(int NS, int ND, int NE);
    void read(const std::string& filename);
    
    void errorcheck_and_shows();
};


// 5. MPI Info
class ProbCOMP {
public:
    int taskID;
    int numTasks;
    int thread;
    
    double t0;
    double t;
    
protected:
    bool m_MPI;
    bool m_OpenMP;
    
public:
    ProbCOMP();
    ~ProbCOMP();
    
    void setting();
    void setting(const int NP, const int Nthread);
    void initialize(int argc, char **argv);
    
    bool useMPI();
    bool useVector();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
};



// 6. Input/Output Info
class ProbIO {
public:
    std::string filename_ProblemSetup;
    std::string filename_grid;
    std::string filename_speciesdatabase;
    std::string filename_wallmaterial;
    std::string filename_Output;
    
    
public:
    ProbIO();
    ~ProbIO();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
};




class ProbleSetup {
public:
    ProbBasicInfo           basicinfo;
    ProbNumericalMethod     numericalmethod;
    ProbPhysicalModel       physicalmodel;
    ProbICBC                boundaryconditions;
    ProbCOMP                computation;
    ProbIO                  inputoutput;
    
public:
    ProbleSetup()
    {
        
    };
    
    ~ProbleSetup()
    {
        
    };
    
    void read();
    void errorcheck_and_shows();
    
};


























#endif /* problemSetup_hpp */
