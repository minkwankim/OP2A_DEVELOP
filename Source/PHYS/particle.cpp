//
//  particle.cpp
//  OP2A
//
//  Created by Kim M.K. on 15/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "particle.hpp"

particle_base::particle_base()
    : spec(-1), X(3, 0.0), V(3, 0.0), Erot(0.0), Evib(0.0), Eele(0.0), Wratio(1.0)
{
    
};


particle_base::~particle_base()
{
    
}

