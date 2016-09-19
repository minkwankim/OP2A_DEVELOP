//
//  object.cpp
//  OP2A
//
//  Created by Kim M.K. on 15/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//
#include <algorithm>
#include "object.hpp"


object::object()
: next(NULL)
{
    
};

object::~object()
{
    next = NULL;
}


void object::getobject(object& b)
{
    *this = b;
    b = *(b.next);
    
    next = NULL;
}



void object::insertFront(object& a)
{
    std::swap(a, *this);
    next = &a;
}

void object::insertBack(object& a)
{
    a.next = next;
    next = &a;
}


void object::removeFromLink()
{
    object* temp = next;
    
    prop = next->prop;
    next = next->next;

    temp->~object();
}
void removeFromLink();



// Add object A to the head of a linked list
void addobj(object* A, object* B)
{
    A->next = B;
    B = A;
}


// Get object A from B(unused list)
void getobj(object* a, object* b)
{
    if (b !=  NULL)
    {
        a = b;
        b = b->next;
        a->next = NULL;
    }
    else
    {
        a = new object;
        a->next = NULL;
    }
}
