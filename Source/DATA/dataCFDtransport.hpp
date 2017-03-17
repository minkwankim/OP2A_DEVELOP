//
//  dataCFDtransport.hpp
//  OP2A
//
//  Created by Kim M.K. on 09/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef dataCFDtransport_hpp
#define dataCFDtransport_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/MultiVector.hpp"
#include "../MATH_MK/matrix.hpp"



class dataCFDtransport_ver1 {
    
    // [DATA]
public:
    std::vector<double> Xs;         // species molar fracion
    std::vector<double> Ys;         // species mass fraction
    
    std::vector<double> mu_s;       // species coefficient of viscosity
    std::vector<double> D_s;        // species diffusion coefficient
    vector2D kappa_s;               // species thermal conductivity
    
    double mu;
    double kappa;
    
protected:
    
    
    // [Constructor / Destructor]
public:
    explicit dataCFDtransport_ver1();
    explicit dataCFDtransport_ver1(unsigned int NS, unsigned int NE);
    
    ~dataCFDtransport_ver1();
    
    
    
    // [Functions]
public:
    void assignSize(unsigned int NS, unsigned int NE);
};


#endif /* dataCFDtransport_hpp */
