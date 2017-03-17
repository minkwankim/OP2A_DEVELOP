//
//  reconstruct.hpp
//  OP2A
//
//  Created by Kim M.K. on 10/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef reconstruct_hpp
#define reconstruct_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/common.hpp"
#include "../COMM/noninstantiable.hpp"

#include "./OP2ACFD_def.hpp"


class Reconstruct_ver1
{
public:
    
    
protected:
    
    
public:
    Reconstruct_ver1()  {  };
    ~Reconstruct_ver1() {  };
    
public:
    double reconstruct(double Qcll, double Qcl, double Qcr, double Xm, double Xf, double Xp);
    void   reconstructVector(std::vector<double>& Qcll,
                                    std::vector<double>& Qcl,
                                    std::vector<double>& Qcr,
                                    double Xm,
                                    double Xf,
                                    double Xp,
                                    std::vector<double>& Q_L);
    
    virtual double phi(double r) = 0;
};




class Reconstruct_Roe : public Reconstruct
{
public:
    Reconstruct_Roe()   {  };
    ~Reconstruct_Roe()  {  };
    
public:
    double phi(double r);
};


class Reconstruct_vanLeer : public Reconstruct
{
public:
    Reconstruct_vanLeer()   {  };
    ~Reconstruct_vanLeer()  {  };
    
public:
    double phi(double r);
};


class Reconstruct_vanAlbada : public Reconstruct
{
public:
    Reconstruct_vanAlbada()   {  };
    ~Reconstruct_vanAlbada()  {  };
    
public:
    double phi(double r);
};


class Reconstruct_BarthJespersen : public Reconstruct
{
public:
    Reconstruct_BarthJespersen()   {  };
    ~Reconstruct_BarthJespersen()  {  };
    
public:
    double phi(double r);
};


class Reconstruct_Superbee : public Reconstruct
{
public:
    Reconstruct_Superbee()   {  };
    ~Reconstruct_Superbee()  {  };
    
public:
    double phi(double r);
};






/*
class Reconstruct
{
public:
    explicit Reconstruct(int ND): m_ND(ND)
    {
        
    };
    
    ~Reconstruct() { };
    
protected:
    int m_ND;
    
    
public:
    double reconstruct(double Qcll, double Qcl, double Qcr,
                       std::vector<double>& xcll,
                       std::vector<double>& xcl,
                       std::vector<double>& xf,
                       std::vector<double>& xcr);
    
    void   reconstructVector(std::vector<double>& Qcll,
                             std::vector<double>& Qcl,
                             std::vector<double>& Q_l,
                             std::vector<double>& Qcr,
                             int n,
                             std::vector<double>& xcll,
                             std::vector<double>& xcl,
                             std::vector<double>& xf,
                             std::vector<double>& xcr);
    virtual double phi(double r) = 0;
};







class Reconstruct2
{
public:
    explicit Reconstruct2() { };
    ~Reconstruct2() { };

    
public:
    double reconstruct(double Qcll, double Qcl, double Qcr, double len2, double lenf, double len);
    virtual double phi(double r) = 0;
};














// 1. Base for Reconstruction 1D
class Reconstruct1DBase {
public:
    
protected:
    
public:
    Reconstruct1DBase()  { };
    ~Reconstruct1DBase() { };
    
    
public:
    virtual double reconstruct(double Qcll,
                               double Qcl,
                               double Qcr,
                               double xcll,
                               double xcl,
                               double xf,
                               double xcr) = 0;
    
    
    virtual void   reconstructVector(std::vector<double>& Qcll,
                                     std::vector<double>& Qcl,
                                     std::vector<double>& Q_l,
                                     std::vector<double>& Qcr,
                                     double xcll,
                                     double xcl,
                                     double xf,
                                     double xcr, unsigned int n) = 0;
    virtual double phi(double r) = 0;
};


// 2. 1st Order
class Reconstruct1D_1stOrder : public Reconstruct1DBase
{
public:
    Reconstruct1D_1stOrder()  { };
    ~Reconstruct1D_1stOrder() { };
    
public:
    double reconstruct(double Qcll, double Qcl, double Qcr, double xcll, double xcl, double xf, double xcr);
};



// 3. 2nd Order
class Reconstruct1D : public Reconstruct1DBase
{
public:
    Reconstruct1D() { };
    ~Reconstruct1D() { };
    
    
public:
    double reconstruct(double Qcll, double Qcl, double Qcr, double xcll, double xcl, double xf, double xcr);
    void   reconstructVector(std::vector<double>& Qcll, std::vector<double>& Qcl, std::vector<double>& Q_l, std::vector<double>& Qcr, double xcll, double xcl, double xf, double xcr);
    virtual double phi(double r) = 0;
};


*/












//

#endif /* reconstruct_hpp */
