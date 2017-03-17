//
//  dataCFD.hpp
//  OP2A
//
//  Created by Kim M.K. on 01/12/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef dataCFD_hpp
#define dataCFD_hpp

#include "dataCFDbasic.hpp"
#include "dataCFDsource.hpp"
#include "dataCFDtransport.hpp"
#include "dataCFDimplicit.hpp"
#include "dataCFDupdate.hpp"


#define dataCFDbasic        dataCFDbasic_ver1
#define dataCFDsource       dataCFDsource_ver1
#define dataCFDtransport    dataCFDtransport_ver1
#define dataCFDimplicit     dataCFDimplicit_ver1
#define dataCFDupdate       dataCFDupdate_ver1
#define dataCFD             dataCFD_ver1




// Data class for CFD
class dataCFD_ver1
{
    // [DATA]
public:
    dataCFDbasic*      basic;
    dataCFDsource*     source;
    dataCFDtransport*  transport;
    dataCFDupdate*     update;
    dataCFDimplicit*   implicit;

    
    // [Constructor/Destructor]
public:
    dataCFD_ver1();
    dataCFD_ver1(unsigned int NS, unsigned int ND, unsigned int NE, bool f_implicit, int type);
    
    ~dataCFD_ver1();

    
    // [Functions]
public:
    void allocate(unsigned int NS, unsigned int ND, unsigned int NE, bool f_implicit, int type);
};

















#endif /* dataCFD_hpp */
