//
//  dataCFDimplicit.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "dataCFDimplicit.hpp"


dataCFDimplicit_ver1::dataCFDimplicit_ver1()
{
    
}

dataCFDimplicit_ver1::dataCFDimplicit_ver1(unsigned int NS, unsigned int ND, unsigned int NE)
: dSource(NS+ND+NE, std::vector<double>(NS+ND+NE)),
  dT(NE, std::vector<double>(NS+ND+NE)),
  dP(NS+ND+NE),
  dPe(NS+ND+NE)
{
    
}

dataCFDimplicit_ver1::~dataCFDimplicit_ver1()
{
    
}



void dataCFDimplicit_ver1::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    int N = NS+ND+NE;
    Common::MultiVector::resize2D(dSource,  N, N);
    Common::MultiVector::resize2D(dT,      NE, N);
    
    dP.resize(N);
    dPe.resize(N);
}