//
//  dataCFD.hpp
//  OP2A
//
//  Created by Kim M.K. on 01/12/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef dataCFD_hpp
#define dataCFD_hpp

#include <stdio.h>
#include <vector>




class dataCFDbasic {
public:
    double rho_mix;
    std::vector<double> Q;      // Premitive variables
    std::vector<double> U;      // Conservative variables

    
    
public:
    <#member functions#>
};




#endif /* dataCFD_hpp */
