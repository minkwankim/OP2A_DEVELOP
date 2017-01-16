//
//  dataCFD.cpp
//  OP2A
//
//  Created by Kim M.K. on 01/12/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "dataCFD.hpp"

// 1. Basic Data class for CFD
dataCFDbasic::dataCFDbasic()
: m_mapping_rho(-1), m_mapping_v(-1), m_mapping_T(-1), m_mapping_p(-1), m_mapping_pe(-1), m_mapped(false)
{
    
}

dataCFDbasic::dataCFDbasic(unsigned int ns, unsigned int nd, unsigned int ne)
: m_mapping_rho(0), m_mapping_v(ns), m_mapping_T(ns+nd), m_mapping_p(ns+nd), m_mapping_pe(ns+nd+ne-1), m_densities(ns+1), m_velocities(nd), m_momentums(nd), m_energies(ne), m_temperatures(ne), m_pressures(2),m_mapped(true)
{
    
}

dataCFDbasic::~dataCFDbasic()
{
    
}


void dataCFDbasic::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    m_densities.resize(NS);
    m_velocities.resize(ND);
    m_temperatures.resize(NE);
    m_energies.resize(NE);
    m_pressures.resize(2);
    m_momentums.resize(ND);
    
    m_mapped = true;
}

bool dataCFDbasic::isMapped()
{
    return (m_mapped);
}


double& dataCFDbasic::Q(unsigned int s)
{
    if (s < m_mapping_v)    return(m_densities[s]);
    if (s < m_mapping_T)    return(m_momentums[s - m_mapping_v]);
    if (s > m_mapping_pe)   Common::ExceptionError(FromHere(), "Exceed possible index number for Q", Common::ErrorCodes::ExceedLimit());
    
    return(m_energies[s - m_mapping_T]);
}

double& dataCFDbasic::U(unsigned int s)
{
    if (s < m_mapping_v)    return(m_densities[s]);
    if (s < m_mapping_T)    return(m_velocities[s - m_mapping_v]);
    if (s > m_mapping_pe)   Common::ExceptionError(FromHere(), "Exceed possible index number for U", Common::ErrorCodes::ExceedLimit());
    
    return(m_temperatures[s - m_mapping_T]);
}

double& dataCFDbasic::W(unsigned int s)
{
    if (s < m_mapping_v)    return(m_densities[s]);
    if (s < m_mapping_T)    return(m_velocities[s - m_mapping_v]);
    if (s == m_mapping_p)   return(m_pressures[0]);
    if (s == m_mapping_pe)  return(m_pressures[1]);
    if (s > m_mapping_pe)   Common::ExceptionError(FromHere(), "Exceed possible index number for W", Common::ErrorCodes::ExceedLimit());
    
    return(m_temperatures[s - m_mapping_T]);
}

double& dataCFDbasic::Q(unsigned int s, int mode)
{
    if (mode == 0)    return(m_densities[s]);
    if (mode == 1)    return(m_momentums[s]);
    if (mode == 2)    return(m_energies[s]);
    
    Common::ExceptionError(FromHere(), "Not supported mode for Q", Common::ErrorCodes::NotSupportedType());
}

double& dataCFDbasic::U(unsigned int s, int mode)
{
    if (mode == 0)    return(m_densities[s]);
    if (mode == 1)    return(m_velocities[s]);
    if (mode == 2)    return(m_temperatures[s]);
    
    Common::ExceptionError(FromHere(), "Not supported mode for U", Common::ErrorCodes::NotSupportedType());
}

double& dataCFDbasic::W(unsigned int s, int mode)
{
    if (mode == 0)    return(m_densities[s]);
    if (mode == 1)    return(m_velocities[s]);
    if (mode == 2)
    {
        if (s == 0)                                 return(m_pressures[0]);
        else if (s == m_mapping_pe - m_mapping_p)   return(m_pressures[1]);
        else                                        return(m_temperatures[s]);
    }
    
    Common::ExceptionError(FromHere(), "Not supported mode for W", Common::ErrorCodes::NotSupportedType());
}

double& dataCFDbasic::RHO(unsigned int s)
{
    return (m_densities[s]);
}


double& dataCFDbasic::V(unsigned int k)
{
    return (m_velocities[k]);
}

double& dataCFDbasic::T(unsigned int i)
{
    return (m_temperatures[i]);
}

double& dataCFDbasic::E(unsigned int i)
{
    return (m_energies[i]);
}

double& dataCFDbasic::P()
{
    return (m_pressures[0]);
}


double& dataCFDbasic::Pe()
{
    return (m_pressures[1]);
}


double& dataCFDbasic::RHO_MIX()
{
    if ((m_densities.size() + 1) != m_mapping_v)
    {
        double rho_mix = 0.0;

        for (int s = 0; s < m_mapping_v; s ++) rho_mix += m_densities[s];
        m_densities.resize(m_mapping_v+1);
        m_densities[m_mapping_v] = rho_mix;
        return(m_densities[m_mapping_v]);

    }
    
    return(m_densities[m_mapping_v]);
}



// 2. Class for Source terms for CFD
dataCFDsource::dataCFDsource()
{
    
}


dataCFDsource::dataCFDsource(unsigned int NS, unsigned int ND, unsigned int NE)
: Source(NS+ND+NE), Source2(NS+ND+NE), Reaction(NS)
{
    
}


dataCFDsource::~dataCFDsource()
{
    
}


void dataCFDsource::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    Source.resize(NS+ND+NE);
    Source2.resize(NS+ND+NE);
    Reaction.resize(NS);
}


// 3. Class for thermodynamics and transport parameters
dataCFDtransport::dataCFDtransport()
{
    
}

dataCFDtransport::~dataCFDtransport()
{
    
}

dataCFDtransport::dataCFDtransport(unsigned int NS)
:Xs(NS), Ys(NS), mu_s(NS), kappa_s(NS), D_s(NS), kappa_tra(NS), kappa_rot(NS), kappa_ve(NS), mu(0.0), kappa(0.0), Cv_tra(0.0), Cv_rot(0.0)
{
    
}


void dataCFDtransport::assignSize(unsigned int NS)
{
    Xs.resize(NS);
    Ys.resize(NS);
    mu_s.resize(NS);
    kappa_s.resize(NS);
    D_s.resize(NS);
    kappa_tra.resize(NS);
    kappa_rot.resize(NS);
    kappa_ve.resize(NS);
}


// 4. Class for Implicit time integration
dataCFDimplicit::dataCFDimplicit()
{
    
}

dataCFDimplicit::dataCFDimplicit(unsigned int NS, unsigned int ND, unsigned int NE)
: dSource(NS+ND+NE, std::vector<double>(NS+ND+NE)), dT(NE, std::vector<double>(NS+ND+NE)), dP(NS+ND+NE), dPe(NS+ND+NE)
{
    
}

dataCFDimplicit::~dataCFDimplicit()
{
    
}

void dataCFDimplicit::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    int N = NS+ND+NE;
    Common::MultiVector::resize2D(dSource, N, N);
    Common::MultiVector::resize2D(dT, NE, N);
    
    dP.resize(N);
    dPe.resize(N);

}


// 5. Class for Updating
dataCFDupdate::dataCFDupdate()
{
    
}

dataCFDupdate::dataCFDupdate(unsigned int NS, unsigned int ND, unsigned int NE)
: dS(NS+ND+NE), RHS(NS+ND+NE)
{
    
}


dataCFDupdate::~dataCFDupdate()
{
    
}


void dataCFDupdate::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    int N = NS+ND+NE;
    dS.resize(N);
    RHS.resize(N);

}



// 6. Data class for CFD
dataCFD::dataCFD() { }

dataCFD::dataCFD(unsigned int NS, unsigned int ND, unsigned int NE)
:basic(NS, ND, NE), source(NS, ND, NE), transport(NS), update(NS, ND, NE)
{
    
}

dataCFD::~dataCFD()
{
    
}

void dataCFD::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    basic.assignSize(NS, ND, NE);
    source.assignSize(NS, ND, NE);
    transport.assignSize(NS);
    update.assignSize(NS, ND, NE);
}


// 7. Data class for CFD1 (Imlicit)
dataCFD2::dataCFD2()  {}
dataCFD2::~dataCFD2() {}

dataCFD2::dataCFD2(unsigned int NS, unsigned int ND, unsigned int NE)
:dataCFD(NS, ND, NE), implicit(NS, ND, NE)
{
    
}

void dataCFD2::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    basic.assignSize(NS, ND, NE);
    source.assignSize(NS, ND, NE);
    transport.assignSize(NS);
    update.assignSize(NS, ND, NE);
    implicit.assignSize(NS, ND, NE);
}

