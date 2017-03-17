//
//  dataCFDimplicit.hpp
//  OP2A
//
//  Created by Kim M.K. on 09/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef dataCFDimplicit_hpp
#define dataCFDimplicit_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/MultiVector.hpp"
#include "../MATH_MK/matrix.hpp"



class dataCFDimplicit_ver1 {
    // [DATA]
public:
    vector2D dSource;
    vector2D dT;
    std::vector<double> dP;
    std::vector<double> dPe;
    
    matrix A;
protected:
    
    
    // [Constructor / destructor]
public:
    explicit dataCFDimplicit_ver1();
    explicit dataCFDimplicit_ver1(unsigned int NS, unsigned int ND, unsigned int NE);
    
    ~dataCFDimplicit_ver1();
    
    
    // [Function]
public:
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};






#endif /* dataCFDimplicit_hpp */
