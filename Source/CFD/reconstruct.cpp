//
//  reconstruct.cpp
//  OP2A
//
//  Created by Kim M.K. on 10/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "reconstruct.hpp"
#include "limiters.hpp"
#include "../COMM/utilities.hpp"
#include "../MATH_MK/math_basic.hpp"



double Reconstruct_ver1::reconstruct(double Qcll , double Qcl, double Qcr, double Xm, double Xf, double Xp)
{
    double Dp;
    double Dm;
    double Di;
    double Rp;
    
    
    Dp = (Qcr - Qcl)  / Xp;
    Dm = (Qcl - Qcll) / Xm;
    Di = (Qcr - Qcll) / (Xm + Xp);
    Rp = Dp / Dm;
    
    double dQ  = Xf * phi(Rp) * Di;
    double Q_L = Qcl + dQ;
    
    double L   = fmin(Qcl, Qcr);
    double R   = fmax(Qcl, Qcr);
    
    if (Q_L < L || Q_L > R) Q_L = Qcl - dQ;
    if (Q_L < L || Q_L > R) Q_L = Qcl;

    return (Q_L);
}


void Reconstruct_ver1::reconstructVector(std::vector<double>& Qcll,
                                         std::vector<double>& Qcl,
                                         std::vector<double>& Qcr,
                                         double Xm,
                                         double Xf,
                                         double Xp,
                                         std::vector<double>& Q_L)
{
    int m = Qcll.size();
    if (Qcl.size() != m) Common::ExceptionError(FromHere(), "Qcl has different dimenstion", Common::ErrorCodes::Mismatch());
    if (Qcr.size() != m) Common::ExceptionError(FromHere(), "Qcr has different dimenstion", Common::ErrorCodes::Mismatch());

    Q_L.resize(m);
    std::vector<double> Q_Lp1(m, 0.0);
    std::vector<double> Q_Lp2(m, 0.0);

    for (int s = 0; s < m; s++)
    {
        double Dp;
        double Dm;
        double Di;
        double Rp;
        double dQ;
        
        Dp = (Qcr[s] - Qcl[s])  / Xp;
        Dm = (Qcl[s] - Qcll[s]) / Xm;
        Di = (Qcr[s] - Qcll[s]) / (Xp + Xm);
        Rp = Dp / Dm;
        dQ = Xf * phi(Rp) * Di;
        
        Q_Lp1[s] = Qcl[s] + dQ;
        Q_Lp2[s] = Qcl[s] - dQ;
    }
    
    for (int s = 0; s < m; s++)
    {
        double L   = fmin(Qcl[s], Qcr[s]);
        double R   = fmax(Qcl[s], Qcr[s]);
    
        if (Q_Lp1[s] < L || Q_Lp1[s] > R) Q_L[s] = Q_Lp2[s];
        if (Q_L[s]   < L || Q_L[s]   > R) Q_L[s] = Qcl[s];
    }
}






double Reconstruct_Roe::phi(double r)
{
    double aux = limiter_slope::min(r);
    return (aux);
}



double Reconstruct_vanLeer::phi(double r)
{
    double aux = limiter_slope::vanLeer(r);
    return (aux);
}


double Reconstruct_vanAlbada::phi(double r)
{
    double aux = limiter_slope::vanAlbada(r);
    return (aux);
}


double Reconstruct_BarthJespersen::phi(double r)
{
    double aux = limiter_slope::BarthJespersen(r);
    return (aux);
}


double Reconstruct_Superbee::phi(double r)
{
    double aux = limiter_slope::Superbee(r);
    return (aux);
}








/*
double Reconstruct::reconstruct(double Qcll, double Qcl, double Qcr,
                                std::vector<double>& xcll,
                                std::vector<double>& xcl,
                                std::vector<double>& xf,
                                std::vector<double>& xcr)
{
    std::vector<double> hp(m_ND, 0.0);
    std::vector<double> hm(m_ND, 0.0);
    std::vector<double> hc(m_ND, 0.0);
    std::vector<double> r (m_ND, 0.0);
    
    
    
    for (int i = 0; i < m_ND; i++)
    {
        hp[i] = xcr[i] - xcl[i];
        hm[i] = xcl[i] - xcll[i];
        hc[i] = xcr[i] - xcll[i];
        r[i]  = xf[i]  - xcl[i];
    }
    
    
    double Q_L        = Qcl;
    double Qcr_m_Qcl  = Qcr - Qcl;
    double Qcl_m_Qcll = Qcl - Qcll;
    double Qcr_m_Qcll = Qcr - Qcll;
    
    for (int i = 0; i < m_ND; i++)
    {
        double Dp = Qcr_m_Qcl  / hp[i];
        double Dm = Qcl_m_Qcll / hm[i];
        double Di = Qcr_m_Qcll / hc[i];
        double Rp = Dp /Dm;
        
        Q_L += r[i]*phi(Rp)*Di;
    }
    
    return (Q_L);
}



void Reconstruct::reconstructVector(std::vector<double>& Qcll,
                                    std::vector<double>& Qcl,
                                    std::vector<double>& Q_l,
                                    std::vector<double>& Qcr,
                                    int n,
                                    std::vector<double>& xcll,
                                    std::vector<double>& xcl,
                                    std::vector<double>& xf,
                                    std::vector<double>& xcr)
{
    Q_l.resize(n);
    Q_l = Qcl;
    
    
    std::vector<double> hp(m_ND, 0.0);
    std::vector<double> hm(m_ND, 0.0);
    std::vector<double> r (m_ND, 0.0);
    std::vector<double> hc(m_ND, 0.0);
    
    for (int i = 0; i < m_ND; i++)
    {
        hp[i] = xcr[i] - xcl[i];
        hm[i] = xcl[i] - xcll[i];
        hc[i] = xcr[i] - xcll[i];
        r[i]  = xf[i]  - xcl[i];
    }
    
    bool flag = false;
    
    for (int i = 0; i <= n; n++)
    {
        double Qcr_m_Qcl  = Qcr[i] - Qcl[i];
        double Qcl_m_Qcll = Qcl[i] - Qcll[i];
        double Qcr_m_Qcll = Qcr[i] - Qcll[i];
        
        for (int k = 0; k < m_ND; k++)
        {
            double Dp = Qcr_m_Qcl  / hp[k];
            double Dm = Qcl_m_Qcll / hm[k];

            double Rp = Dp /Dm;
            double Di = Qcr_m_Qcll / hc[k];

            Q_l[i] += r[k]*phi(Rp)*Di;
        }
        
        flag = Common::Utilities::isInvalueLimits(Q_l[i], Qcl[i], Qcr[i]);
        if (flag == true)
        {
            Q_l = Qcl;
            break;
        }
    }
}








double Reconstruct2::reconstruct(double Qcll, double Qcl, double Qcr, double len2, double lenf, double len)
{
    double Dp = (Qcr - Qcl)  / len;
    double Dm = (Qcl - Qcll) / len2;
    double Rp = Dp /Dm;
    
    double phi_Rp = 0.0;
    phi_Rp = phi(Rp);

    double Di, Q_L, dQ;
    
    Di  = (Qcr - Qcll) / (len + len2);
    dQ  = lenf*phi_Rp*Di;
    Q_L = Qcl + temp;
    
    if (Common::Utilities::isInvalueLimits(Q_L, Qcl, Qcr) == false) Q_L = Qcl - temp;
    if (Common::Utilities::isInvalueLimits(Q_L, Qcl, Qcr) == false) Q_L = Qcl;

    return (Qcl);
}



// 2. 1st Order
double Reconstruct1D_1stOrder::reconstruct(double Qcll, double Qcl, double Qcr, double xcll, double xcl, double xf, double xcr)
{
    return (Qcl);
}


// 3. 2nd Order
double Reconstruct1D::reconstruct(double Qcll, double Qcl, double Qcr, double xcll, double xcl, double xf, double xcr)
{
    double hp = xcr - xcl;
    double hm = xcl - xcll;
    
    double Dp = (Qcr - Qcl)  / hp;
    double Dm = (Qcl - Qcll) / hm;
    double Di = (Qcr - Qcll) / (xcr - xcll);
    
    double r  = xf - xcl;
    double Rp = Dp /Dm;
    
    double Q_L = 0.0;
    Q_L = Qcl + r*phi(Rp)*Di*sign(Di);
    
    
    if (Qcl < Qcr)
    {
        if (Q_L >= Qcl && Q_L <= Qcr)  return (Q_L);
        else                           return (Qcl);
    }
    else
    {
        if (Q_L >= Qcr && Q_L <= Qcl)  return (Q_L);
        else                           return (Qcl);
    }
    
    return (Q_L);
}

void Reconstruct1D::reconstructVector(std::vector<double>& Qcll, std::vector<double>& Qcl, std::vector<double>& Q_l, std::vector<double>& Qcr, double xcll, double xcl, double xf, double xcr)
{
    int n = Qcll.size();
    
    Q_l.resize(n);
    Q_l = Qcl;
    
    double hp = xcr - xcl;
    double hm = xcl - xcll;
    double hc = xcr - xcll;
    double r  = xf - xcl;
    
    
    for (int i =0; i < n; i++)
    {
        double Dp = (Qcr[i] - Qcl[i])  / hp;
        double Dm = (Qcl[i] - Qcll[i]) / hm;
        double Di = (Qcr[i] - Qcll[i]) / hc;
        double Rp = Dp /Dm;

        Q_l[i] += r*phi(Rp)*Di;
    }
}





*/











