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
#include "./GRID/grid.hpp"
#include "./CFD/OP2ACFD.hpp"
#include "./COMM/error_codes.hpp"




int main(int argc, char **argv) {
    double res = 10.0;
    
    GridBasicInfo gridinfo;
    GridData<NodeNormal<double>, FaceNormal<double>, CellNormal<double> > gridtemp;
    readGridFromFile("/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2.op2", gridinfo, gridtemp);
    processingGrid(gridinfo, gridtemp);
    
    
    writeGridTecplot("/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2", gridinfo, gridtemp);

    
    //Node node = gridData.node(1);
    //readGrid("test.op2", grid);
    
    
    // insert code here...
    std::cout << "Hello, World!  " << res << "\n";
    return 0;
   
    
}
