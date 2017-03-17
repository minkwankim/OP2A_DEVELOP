//
//  dataCFDtransport.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "dataCFDtransport.hpp"


dataCFDtransport_ver1::dataCFDtransport_ver1()
{
    
}

dataCFDtransport_ver1::dataCFDtransport_ver1(unsigned int NS, unsigned int NE)
:Xs(NS, 0.0), Ys(NS, 0.0),
mu_s(NS, 0.0), D_s(NS, 0.0), kappa_s(NS, std::vector<double>(NE, 0.0)),
mu(0.0), kappa(0.0)
{
    
}

dataCFDtransport_ver1::~dataCFDtransport_ver1()
{
    
}




void dataCFDtransport_ver1::assignSize(unsigned int NS, unsigned int NE)
{
    Xs.resize(NS);
    Ys.resize(NS);
    
    mu_s.resize(NS);
    D_s.resize(NS);
    
    Common::VectorMulti<double>::resize(kappa_s, NS, NE);
}