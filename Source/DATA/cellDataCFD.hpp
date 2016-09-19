//
//  cellDataCFD.hpp
//  OP2A
//
//  Created by Kim M.K. on 16/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef cellDataCFD_hpp
#define cellDataCFD_hpp

#include <stdio.h>
#include "celldatabase.hpp"


class CellDataCFD : public CellDataBase {
public:
    CellDataCFD();
    ~CellDataCFD();
    
public:
    std::vector<double> U;  // Conservative variables
    double p;
};


#endif /* cellDataCFD_hpp */
