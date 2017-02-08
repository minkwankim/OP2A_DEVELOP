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

#include "../COMM/map1D.hpp"
#include "../CHEM/species.hpp"

#include "flowdatabase.hpp"
#include "wallMaterial.hpp"
#include "ProbPhysicalModel.hpp"

///////////////////////
// 1. Basic seccion
//////////////////////
class ProbBasicInfo {
public:
    std::string title;
    int axisymmetric;
    double gridfactor;
    int cartesian_grid;
    
public:
    ProbBasicInfo();
    ~ProbBasicInfo();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
};



////////////////////////////////
// 2. Numerical Method Session
////////////////////////////////
class ProbNumericalMethodCFD {
public:
    int order;                      // Flux calculation order
    int timeIntegration;            // Time integration methods       (0: Explicit,  1: Point implicit,  2: Line implicit)
    int spatialIntegration;         // Spartical integration methods  (0: SW-FVS,    1: Modified SW-FVS, 2: AUSM)
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

/*
//////////////////////////////////
// 3. Physical Modelling Session
//////////////////////////////////
class variableMappingCFD
{
public:
    std::vector<int>               rho_s;
    std::vector<std::vector<int> > Ts;

protected:
    int m_NS;
    int m_ND;
    int m_NE;
    std::vector<int> m_start_index;
    std::vector<int> m_T;
    bool m_mapped;
    
    
public:
    variableMappingCFD();
    variableMappingCFD(int NS, int ND, int NE);
    ~variableMappingCFD();
    
public:
    void completeMapping(int NS, int ND, int NE, int Tr, int Tv, int Tel, int Te);
    void completeMappingElectron(int ND);
    unsigned int Q(int s, int type);
    unsigned int T(int type);
    unsigned int NS();
    unsigned int ND();
    unsigned int NE();
    
};

class ProbPhysicalModel {
public:
    std::vector<int> NS;
    std::vector<int> NR;
    std::vector<int> NE;
    int NS_tot;
    
    int NER;        // Rotational Energy
    int NEV;        // Vibrational Energy
    int NEEL;       // Electronic Energy
    int NEE;        // Elecrron Energy
    
    int E_Trot;
    int E_Tvib;
    int E_Tele;
    int E_Te;
    
    int mixingRule;
    int viscosityModel;
    int diffusivityModel;
    int conductivityModel;
    double Le;
    
    std::vector<std::string> speciesList;
    int fluidModel;
    std::vector<variableMappingCFD> variable_map;

    std::vector<int> whereIsRho_fluidNum;   // [Global ID] ==> fluid number
    std::vector<int> whereIsRho_speciesNum; // [Global ID] ==> local s
    Common::Map1D<std::string, int> species_name_to_global;
    
    std::vector<int> atomic_species_global_ID;
    std::vector<int> molecular_species_global_ID;
    int              electron_global_ID;
    
    
public:
    ProbPhysicalModel();
    ~ProbPhysicalModel();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
    void speciesMapping(std::vector<species>& speciesdata, int ND);

};
*/


//////////////////
// 4. IC/Bs
/////////////////
class ProbICBC {
public:
    int iniMethod;
    std::vector<int>           inletCond;
    std::vector<int>           wallCond;
    std::vector<std::string>   wallMatName;
    std::vector<wallMaterial>  wallMat;
    std::vector<flowDataBase>  flowCond;
    
    std::vector< std::vector< std::vector<double> > > U_inlet;
    std::vector< std::vector< std::vector<double> > > Q_inlet;
    
    std::vector< std::vector< std::vector<double> > > U_wall;
    std::vector< std::vector< std::vector<double> > > Q_wall;
    
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
    ProbPhysicalModel_ver1  physicalmodel;
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
    void processing(std::vector<species>& speciesdata, int ND);
    void errorcheck_and_shows();
    
};


























#endif /* problemSetup_hpp */
