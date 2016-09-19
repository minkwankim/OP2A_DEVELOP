//
//  particle.hpp
//  OP2A
//
//  Created by Kim M.K. on 15/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef particle_hpp
#define particle_hpp

#include <stdio.h>
#include <vector>

class particle_base {

public:
    particle_base();
    ~particle_base();
    
    
public:
    int spec;
    std::vector<double> X;
    std::vector<double> V;
    
    double Erot;
    double Evib;
    double Eele;
    
    double Wratio;
};





#endif /* particle_hpp */
