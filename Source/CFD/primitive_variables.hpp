//
//  primitive_variables.hpp
//  OP2A
//
//  Created by Kim M.K. on 20/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef primitive_variables_hpp
#define primitive_variables_hpp


#include "primitive_variables_fluid0.hpp"
#include "primitive_variables_fluid1.hpp"
#include "primitive_variables_fluid3.hpp"
#include "primitive_variables_fluid4.hpp"
#include "primitive_variables_fluid5.hpp"
#include "primitive_variables_fluid9.hpp"
#include "primitive_variables_fluid10.hpp"
#include "primitive_variables_fluid11.hpp"
#include "primitive_variables_fluid12.hpp"
#include "primitive_variables_fluid13.hpp"
#include "primitive_variables_fluid14.hpp"
#include "primitive_variables_fluid15.hpp"
#include "primitive_variables_fluid16.hpp"
#include "primitive_variables_fluid17.hpp"

#include "primitive_variables_fluid27.hpp"





variableMapCFD* nonequilibriumModel(variableMap& model);





void UtoQ(variableMapCFD& info, std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q);
void UtoW(variableMapCFD& info, std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W);

void QtoU(variableMapCFD& info, std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U);




#endif /* premitive_variables_hpp */
