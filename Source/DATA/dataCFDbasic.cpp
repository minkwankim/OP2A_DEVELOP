//
//  dataCFDbasic.cpp
//  OP2A
//
//  Created by Kim M.K. on 08/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "dataCFDbasic.hpp"



// Section for Constructor/destructor
dataCFDbasic_ver1::dataCFDbasic_ver1()
{
    
}


dataCFDbasic_ver1::dataCFDbasic_ver1(unsigned int ns, unsigned int nd, unsigned int ne)
: Q(ns+nd+ne, 0.0), U(ns+nd+ne, 0.0)
{
    
}


dataCFDbasic_ver1::~dataCFDbasic_ver1()
{
    
}


// Section for Functions
void dataCFDbasic_ver1::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    int N_tot = NS+ND+NE;
    Q.resize(N_tot);
    U.resize(N_tot);
}