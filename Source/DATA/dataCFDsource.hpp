//
//  dataCFDsource.hpp
//  OP2A
//
//  Created by Kim M.K. on 08/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef dataCFDsource_hpp
#define dataCFDsource_hpp

#include <stdio.h>
#include <vector>
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/MultiVector.hpp"
#include "../MATH_MK/matrix.hpp"



class dataCFDsource_ver1 {
    
    // Section for DATA
public:
    std::vector<double> SourceChem;
    std::vector<double> SourceMHD;
    std::vector<double> SourceTemp;
    
protected:
    
    
    // Section for Constructor/destructor

public:
    explicit dataCFDsource_ver1();
    explicit dataCFDsource_ver1(unsigned int NS, unsigned int ND, unsigned int NE);
    
    ~dataCFDsource_ver1();
    
    // Section for Functions
public:
    void assignSize(unsigned int NS, unsigned int ND, unsigned int NE);
};



#endif /* dataCFDsource_hpp */
