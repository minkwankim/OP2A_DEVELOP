//
//  dataCFD.cpp
//  OP2A
//
//  Created by Kim M.K. on 01/12/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "dataCFD.hpp"


// Data class for CFD ver1
dataCFD_ver1::dataCFD_ver1()
{
    basic     = NULL;
    source    = NULL;
    transport = NULL;
    update    = NULL;
    implicit  = NULL;
}

dataCFD_ver1::~dataCFD_ver1()
{
    basic     = NULL;
    source    = NULL;
    transport = NULL;
    update    = NULL;
    implicit  = NULL;
}

dataCFD_ver1::dataCFD_ver1(unsigned int NS, unsigned int ND, unsigned int NE, bool f_implicit, int type)
{
    switch (type)
    {
        case 0: // Node
            basic     = new dataCFDbasic(NS, ND, NE);
            source    = NULL;
            transport = NULL;
            update    = NULL;
            implicit  = NULL;
            break;
            
        case 1:  //  Face
            basic     = new dataCFDbasic(NS, ND, NE);
            source    = NULL;
            transport = NULL;
            update    = NULL;
            implicit  = NULL;
            break;
            
        case 2:  // Cell
            basic     = new dataCFDbasic(NS, ND, NE);
            source    = new dataCFDsource(NS, ND, NE);
            transport = new dataCFDtransport(NS, NE);
            update    = new dataCFDupdate(NS, ND, NE);
            
            if (f_implicit == true) implicit = new dataCFDimplicit(NS, ND, NE);
            else                    implicit = NULL;
            break;
    }
}



void dataCFD_ver1::allocate(unsigned int NS, unsigned int ND, unsigned int NE, bool f_implicit, int type)
{
    switch (type)
    {
        case 0: // Node
            basic     = new dataCFDbasic(NS, ND, NE);
            source    = NULL;
            transport = NULL;
            update    = NULL;
            implicit  = NULL;
            break;
            
        case 1:  //  Face
            basic     = new dataCFDbasic(NS, ND, NE);
            source    = NULL;
            transport = NULL;
            update    = NULL;
            implicit  = NULL;
            break;
            
        case 2:  // Cell
            basic     = new dataCFDbasic(NS, ND, NE);
            source    = new dataCFDsource(NS, ND, NE);
            transport = new dataCFDtransport(NS, NE);
            update    = new dataCFDupdate(NS, ND, NE);
            
            if (f_implicit == true) implicit = new dataCFDimplicit(NS, ND, NE);
            else                    implicit = NULL;
            break;
    }
}

