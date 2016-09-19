//
//  celldatabase.hpp
//  OP2A
//
//  Created by Kim M.K. on 16/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef celldatabase_hpp
#define celldatabase_hpp

#include <stdio.h>
#include <vector>



class CellDataBase {
public:
    CellDataBase();
    ~CellDataBase();
    
public:
    std::vector<double> Q;      // Primitive variavles
    
};

#endif /* celldatabase_hpp */
