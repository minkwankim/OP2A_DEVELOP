//
//  main.cpp
//  OP2A
//
//  Created by Kim M.K. on 15/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include <iostream>
#include <mkl.h>

#include "./MATH_MK/matrix.hpp"
#include "./GRID/element.hpp"
#include "./CFD/OP2ACFD.hpp"
#include "./COMM/error_codes.hpp"

int main(int argc, char **argv) {
    double res = 10.0;
    
    
    preProcessingPart1Version(argc, argv, res);

    
    
    
    
    // insert code here...
    std::cout << "Hello, World!  " << res << "\n";
    return 0;
    
    
}
