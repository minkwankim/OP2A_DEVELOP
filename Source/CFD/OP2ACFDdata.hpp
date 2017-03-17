//
//  OP2ACFDdata.hpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef OP2ACFDdata_hpp
#define OP2ACFDdata_hpp

#include <stdio.h>
#include <vector>

#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/MultiVector.hpp"

#include "../MATH_MK/matrix.hpp"



// 1. Base Data Function
class OP2ACFD_DataBase {
public:
    // Flow informations
    std::vector<double> U;
    std::vector<double> Q;
    
    
public:
    explicit OP2ACFD_DataBase();
    explicit OP2ACFD_DataBase(int s);
    ~OP2ACFD_DataBase();
};




#endif /* OP2ACFDdata_hpp */
