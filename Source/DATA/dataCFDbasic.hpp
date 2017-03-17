//
//  dataCFDbasic.hpp
//  OP2A
//
//  Created by Kim M.K. on 08/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef dataCFDbasic_hpp
#define dataCFDbasic_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/MultiVector.hpp"
#include "../MATH_MK/matrix.hpp"





// Basic Data class for CFD
class dataCFDbasic_ver1 {
    
    // Section for DATA
public:
    std::vector<double> Q;    // Premitive variables
    std::vector<double> U;    // Conservative variables
    
protected:
    
    
    
    // Section for Constructor/destructor
public:
    explicit dataCFDbasic_ver1();
    explicit dataCFDbasic_ver1(unsigned int ns, unsigned int nd, unsigned int ne);
    ~dataCFDbasic_ver1();
    
    
    // Section for Functions
public:
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};








#endif /* dataCFDbasic_hpp */
