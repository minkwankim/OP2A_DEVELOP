//
//  dataCFDupdate.hpp
//  OP2A
//
//  Created by Kim M.K. on 09/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef dataCFDupdate_hpp
#define dataCFDupdate_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/MultiVector.hpp"
#include "../MATH_MK/matrix.hpp"



class dataCFDupdate_ver1 {
    
    // [DATA]
public:
    std::vector<double> dQ;
    std::vector<double> RHS;
    
    
    // [Constructor /Destructor]
public:
    dataCFDupdate_ver1();
    dataCFDupdate_ver1(unsigned int NS, unsigned int ND, unsigned int NE);
    ~dataCFDupdate_ver1();
    
public:
    //
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};

#endif /* dataCFDupdate_hpp */
