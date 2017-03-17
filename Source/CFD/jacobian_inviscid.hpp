//
//  jacobian_inviscid.hpp
//  OP2A
//
//  Created by Kim M.K. on 07/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef jacobian_inviscid_hpp
#define jacobian_inviscid_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/MultiVector.hpp"
#include "./variableMapCFD.hpp"




class Jacobian_Inviscid : public variableMapCFDBase
{
public:
    explicit Jacobian_Inviscid()                  : variableMapCFDBase()      {  };
    explicit Jacobian_Inviscid(variableMap input) : variableMapCFDBase(input) {  };
    ~Jacobian_Inviscid()                                                      {  };
    
    
public:
    void calculate_dYs_dQ(std::vector<double>& Q, vector2D& dYs_dQ);
    void calculate_du_dQ(std::vector<double>& V,   vector2D& du_dQ);


    
    
    
    
};










#endif /* jacobian_inviscid_hpp */
