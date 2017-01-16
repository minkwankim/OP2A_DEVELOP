//
//  dataCFD.hpp
//  OP2A
//
//  Created by Kim M.K. on 01/12/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef dataCFD_hpp
#define dataCFD_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/MultiVector.hpp"
#include "../MATH_MK/matrix.hpp"



// 1. Basic Data class for CFD
class dataCFDbasic {
protected:
    std::vector<double> m_densities;      // Densities of species
    std::vector<double> m_velocities;     // velocities
    std::vector<double> m_temperatures;   // temperatures
    std::vector<double> m_energies;       // energies
    std::vector<double> m_pressures;      // pressures
    std::vector<double> m_momentums;      // momentums

    int m_mapping_rho;
    int m_mapping_v;
    int m_mapping_T;
    int m_mapping_p;
    int m_mapping_pe;
    bool m_mapped;
    
public:
    dataCFDbasic();
    dataCFDbasic(unsigned int ns, unsigned int nd, unsigned int ne);
    ~dataCFDbasic();
    
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
    bool isMapped();
    
    double& Q(unsigned int s);  // Premitive variables
    double& U(unsigned int s);  // Conservative variables
    double& W(unsigned int s);  // Conservatibe variables II
    
    double& Q(unsigned int s, int mode);  // Premitive variables
    double& U(unsigned int s, int mode);  // Conservative variables
    double& W(unsigned int s, int mode);  // Conservative variables II
    
    double& RHO(unsigned int s);
    double& V(unsigned int k);
    double& T(unsigned int i);
    double& E(unsigned int i);
    double& P();
    double& Pe();
    double& RHO_MIX();
};


// 2. Class for Source terms for CFD
class dataCFDsource {
public:
    std::vector<double> Source;
    std::vector<double> Reaction;
    std::vector<double> Source2;
    
public:
    dataCFDsource();
    dataCFDsource(unsigned int NS, unsigned int ND, unsigned int NE);
    
    ~dataCFDsource();
    
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};


// 3. Class for thermodynamics and transport parameters
class dataCFDtransport {
public:
    std::vector<double> Xs;         // species molar fracion
    std::vector<double> Ys;         // species mass fraction
    std::vector<double> mu_s;       // species coefficient of viscosity
    std::vector<double> kappa_s;    // species thermal conductivity
    std::vector<double> D_s;        // species diffusion coefficient

    std::vector<double> kappa_tra;  // species thermal conductivity (translational)
    std::vector<double> kappa_rot;  // species thermal conductivity (rotational)
    std::vector<double> kappa_ve;   // species thermal conductivity (vibrational-electronic)
    
    double mu;
    double kappa;
    
    double Cv_tra;                  // Mixture translational specific heat
    double Cv_rot;                  // Mixture rotational specific heat;

public:
    dataCFDtransport();
    dataCFDtransport(unsigned int NS);

    ~dataCFDtransport();
    
    void assignSize(unsigned int NS);
};


// 4. Class for Implicit time integration
class dataCFDimplicit {
public:
    vector2D dSource;
    vector2D dT;
    
    std::vector<double> dP;
    std::vector<double> dPe;
    
    matrix A;

public:
    dataCFDimplicit();
    dataCFDimplicit(unsigned int NS, unsigned int ND, unsigned int NE);

    ~dataCFDimplicit();
    
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};


// 5. Class for Updating
class dataCFDupdate {
public:
    std::vector<double> dS;
    std::vector<double> RHS;

public:
    dataCFDupdate();
    dataCFDupdate(unsigned int NS, unsigned int ND, unsigned int NE);
    
    ~dataCFDupdate();
    
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};



// 6. Data class for CFD
class dataCFD
{
    // [Part A]: Section for Data
public:
    dataCFDbasic      basic;
    dataCFDsource     source;
    dataCFDtransport  transport;
    dataCFDupdate     update;
    
    // [Part B]: Section for Constructor/Destructor
public:
    dataCFD();
    dataCFD(unsigned int NS, unsigned int ND, unsigned int NE);

    ~dataCFD();
    
    // [Part C]: Section for functions
public:
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};


// 7. Data class for CFD1 (Imlicit)
class dataCFD2: public dataCFD
{
    // [Part A]: Section for Data
public:
    dataCFDimplicit implicit;
    
    // [Part B]: Section for Constructor/Destructor
public:
    dataCFD2();
    dataCFD2(unsigned int NS, unsigned int ND, unsigned int NE);
    
    ~dataCFD2();
    
    // [Part C]: Section for functions
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};



#endif /* dataCFD_hpp */
