//
//  object.hpp
//  OP2A
//
//  Created by Kim M.K. on 15/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef object_hpp
#define object_hpp

#include <stdio.h>
#include "../PHYS/particle.hpp"

class object {
public:
    object();
    ~object();
    
public:
    particle_base prop;
    class object *next;
    
    void getobject(object& b);
    
    void insertFront(object& a);
    void insertBack(object& a);
    void removeFromLink();
    
};

void addobj(object* A, object* B);      // Add object A to the head of a linked list
void getobj(object* A, object* B);      // Get object A from B(unused list)




#endif /* object_hpp */
