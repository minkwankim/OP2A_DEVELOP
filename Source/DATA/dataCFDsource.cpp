//
//  dataCFDsource.cpp
//  OP2A
//
//  Created by Kim M.K. on 08/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "dataCFDsource.hpp"


dataCFDsource_ver1::dataCFDsource_ver1()
{
    
}


dataCFDsource_ver1::dataCFDsource_ver1(unsigned int NS, unsigned int ND, unsigned int NE)
: SourceTemp(NS+ND+NE, 0.0), SourceMHD(NS+ND+NE, 0.0), SourceChem(NS+ND+NE, 0.0)
{
    
}


dataCFDsource_ver1::~dataCFDsource_ver1()
{
    
}


void dataCFDsource_ver1::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    int N_tot = NS + ND + NE;
    
    SourceTemp.resize(N_tot);
    SourceMHD.resize(N_tot);
    SourceTemp.resize(N_tot);
}
