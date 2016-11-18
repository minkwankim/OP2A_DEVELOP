//
//  index.cpp
//  OP2A
//
//  Created by Kim M.K. on 08/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "index.hpp"
#include "../COMM/error_codes.hpp"

// Constructor and Destructor
grid_index::grid_index()
    : i(0), j(0), k(0), lvl(0), pos(MAX_REFINE_LVL, 0), hasChildren(false)
{
    
};

grid_index::~grid_index()
{
    
};



// Functions
void grid_index::refine(unsigned int position)
{
    if (position > 7) Common::OP2A_ERROR2(FromHere(), 0, 24, __FUNCTION__, "position", position);
    
    lvl++;
    pos[lvl] = position;
};







// Grobal Index class

