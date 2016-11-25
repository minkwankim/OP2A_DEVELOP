//
//  wallMaterial.hpp
//  OP2A
//
//  Created by Kim M.K. on 23/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef wallMaterial_hpp
#define wallMaterial_hpp

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <string>

#include "../COMM/map1D.hpp"
#include "../COMM/assert_mk.hpp"
#include "../COMM/readdatafromstring.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"
#include "../COMM/StringOps.hpp"
#include "../COMM/VectorCompare.hpp"


#define DATA_WALL_START     "#MAT_WALL_START"
#define DATA_WALL_END       "#MAT_WALL_END"


class wallMaterial {
public:
    std::string name;
    
    int    emissivity_Model;
    double emissivity_T0;
    std::vector<double> emissivity_coeff_above;
    std::vector<double> emissivity_coeff_below;
    
    
public:
    wallMaterial();
    ~wallMaterial();
};


class wallMaterialDataBase
{
protected:
    Common::Map1D<std::string, int> datamap;
    std::vector<wallMaterial> data;
    
public:
    wallMaterialDataBase();
    ~wallMaterialDataBase();
    
    void read(const std::string& filename);
    void add(const std::string& filename);
    
    wallMaterial find(std::string name);
};


#endif /* wallMaterial_hpp */
