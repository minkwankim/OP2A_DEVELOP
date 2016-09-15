//
//  basicInfo.hpp
//  OP2A
//
//  Created by Kim M.K. on 08/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef basicInfo_hpp
#define basicInfo_hpp

#include <stdio.h>
#include <vector>
#include "../MATH_MK/matrix.hpp"


class GridBasicInfo {
public:
    GridBasicInfo();
    ~GridBasicInfo();
    
public:
    int type;
    int id;
    int bc;
    
    matrix X;
    double S;
    
};


#endif /* basicInfo_hpp */
