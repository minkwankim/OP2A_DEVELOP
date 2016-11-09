//
//  element.hpp
//  OP2A
//
//  Created by Kim M.K. on 12/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef element_hpp
#define element_hpp

#include <stdio.h>
#include "basicinfo.hpp"
#include "index.hpp"
#include "stencilinfo.hpp"


template <class D, class S1, class S2>
class ElementBasic : public GridBasicInfo, grid_index, stencil_info<S1, S2>
{
    
    // Constructor and Destructor
public:
    ElementBasic()
    :data(NULL)
    {
        
    };
    
    
    ~ElementBasic()
    {
        data = NULL;
    };
    
public:
    D* data;
};


template <class D, class S1, class S2, class E1>
class ElementAdvance1 : public ElementBasic<D, S1, S2>
{
public:
    ElementAdvance1()
    :num_subelements(0)
    {
        subelements.reserve(4);
    };
    
    ElementAdvance1(unsigned int num)
    :num_subelements(num), subelements(num)
    {

    };
    
     
    ~ElementAdvance1()
    {
        
    };
    
    
public:
    std::vector<E1> subelements;
    unsigned int num_subelements;
    
};



template <class D, class S1, class S2, class E1, class E2>
class ElementAdvance2 : public ElementAdvance1<D, S1, S2, E1>
{
public:
    ElementAdvance2()
    :num_subelements(0), num_subelements2(0)
    {
        subelements.reserve(4);
        subelements2.reserve(4);
    };
    
    ElementAdvance2(unsigned int num1, unsigned int num2)
    :num_subelements(num1), subelements(num1), num_subelements2(num2), subelements2(num2)
    {
        
    };
    
    
    ~ElementAdvance2()
    {
        
    };
    
    
public:
    std::vector<E2> subelements2;
    unsigned int num_subelements2;
};



template <class GEO, class CONN, class DATA>
class GridElement
{
public:
    GEO* geometry;
    CONN* connectivity;
    DATA* data;
    
public:
    GridElement()
    {
        geometry = NULL;
        connectivity = NULL;
        data = NULL;
    }
    
    ~GridElement()
    {
        geometry = NULL;
        connectivity = NULL;
        data = NULL;
    }
};








#endif /* element_hpp */
