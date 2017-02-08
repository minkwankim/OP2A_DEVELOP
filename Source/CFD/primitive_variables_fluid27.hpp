//
//  primitive_varibles_fluid27.hpp
//  OP2A
//
//  Created by Kim M.K. on 08/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef primitive_varibles_fluid27_hpp
#define primitive_varibles_fluid27_hpp

#include <stdio.h>
#include "variableMapCFD.hpp"


class variableMapCFD_fluid_27 : public variableMapCFD
{
public:
    explicit variableMapCFD_fluid_27()                  : variableMapCFD() {};
    explicit variableMapCFD_fluid_27(variableMap input) : variableMapCFD(input) {};
    ~variableMapCFD_fluid_27()  {};
    
public:
    void UtoQ(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q);
    void UtoW(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W);
    void QtoU(std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U);
};




#endif /* primitive_varibles_fluid27_hpp */
