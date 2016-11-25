//
//  main.cpp
//  OP2A
//
//  Created by Kim M.K. on 15/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include <iostream>
#include <mkl.h>

#include "./CHEM/speciesDataBase.hpp"
#include "./DATA/problemSetup.hpp"
#include "./DATA/wallMaterial.hpp"

#include "./MATH_MK/matrix.hpp"
#include "./GRID/grid.hpp"
#include "./CFD/OP2ACFD.hpp"
#include "./COMM/error_codes.hpp"




int main(int argc, char **argv) {
    double res = 10.0;
    
    
    // TEST SECTION
    ProbBasicInfo probbasic;
    probbasic.read("/Users/mkk1u16/Desktop/Code_Development/OP2A/problem.pro");
    
    ProbICBC    probIC;
    probIC.read("/Users/mkk1u16/Desktop/Code_Development/OP2A/problem.pro");
    
    
    
    speciesDataBase testSpecies;
    testSpecies.read("/Users/mkk1u16/Desktop/Code_Development/OP2A/dat/species.dat");
    
    
    //wallMaterialDataBase testwallmat;
    //testwallmat.read("/Users/mkk1u16/Desktop/Code_Development/OP2A/dat/wall_material.dat");
    //testwallmat.add("/Users/mkk1u16/Desktop/Code_Development/OP2A/dat/wall_material.dat");
    //wallMaterial testmat;
    //testmat = testwallmat.find("Quartz wall");

    //GridBasicInfo gridinfo;
    //GridData<NodeNormal<double>, FaceNormal<double>, CellNormal<double> > gridtemp;
    //readGridFromFile("/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2.op2", gridinfo, gridtemp);
    //processingGrid(gridinfo, gridtemp);
    //writeGridTecplot("/Users/mkk1u16/Desktop/Code_Development/OP2A/grid2", gridinfo, gridtemp);

    
    
    
    
    
    // insert code here...
    std::cout << "Hello, World!  " << res << "\n";
    return 0;
   
    
}
