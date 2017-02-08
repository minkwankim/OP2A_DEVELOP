//
//  primitive_variables_fluid0.hpp
//  OP2A
//
//  Created by Kim M.K. on 07/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef primitive_variables_fluid0_hpp
#define primitive_variables_fluid0_hpp

#include <stdio.h>
#include "variableMapCFD.hpp"

class variableMapCFD_fluid_0 : public variableMapCFD
{
public:
    explicit variableMapCFD_fluid_0()                  : variableMapCFD() {};
    explicit variableMapCFD_fluid_0(variableMap input) : variableMapCFD(input) {};
    ~variableMapCFD_fluid_0()  {};
    
public:
    void UtoQ(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q);
    void UtoW(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W);
    void QtoU(std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U);
};

#endif /* primitive_variables_fluid0_hpp */
