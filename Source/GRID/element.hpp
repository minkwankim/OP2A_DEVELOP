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
#include "geometry.hpp"
#include "connection.hpp"

#include "index.hpp"
#include "stencilinfo.hpp"

#define MAX_NUMBER_CHILDER_PER_FACE 4
#define MAX_NUMBER_CHILDER_PER_CELL 8


template <class GEO, class CONN, class DATA>
class GridElement
{
public:
    GEO geometry;
    CONN connectivity;
    DATA data;
    
public:
    GridElement()
    {
    
    }
    
    ~GridElement()
    {
    
    }
};



// NODE types
template <class DATA>
class NodeNormal : public GridElement<GeometryNode, ConnectionNode, DATA>
{
public:
    NodeNormal() { };
    ~NodeNormal() { };
};

template <class DATA>
class NodeCart : public NodeNormal<DATA>
{
public:
    grid_index index;

public:
    NodeCart() { };
    ~NodeCart() { };
};



// FACE Types
//  A. Normal grid
template <class DATA>
class FaceNormal : public GridElement<GeometryFace, ConnectionFace, DATA>
{
public:
    FaceNormal() { };
    ~FaceNormal() { };
};

// B. Cartesian grid
template <class DATA>
class FaceCart : public FaceNormal<DATA>
{
public:
    grid_index index;
    FaceCart* parent;
    std::vector<FaceCart*> children;
    
public:
    FaceCart()
    : parent(NULL)
    {
        children.reserve(MAX_NUMBER_CHILDER_PER_FACE);
    };
    
    ~FaceCart()
    {
        
    };
};



// CELL Types
// A. Normal Grid
template <class DATA>
class CellNormal : public GridElement<GeometryCell, ConnectionCell, DATA>
{
public:
    CellNormal() { };
    ~CellNormal() { };
};

template <class DATA>
class CellPIC : public GridElement<GeometryCellPIC, ConnectionCell, DATA>
{
public:
    CellPIC() { };
    ~CellPIC() { };
};

template <class DATA>
class CellHybrid : public GridElement<GeometryCellHybrid, ConnectionCell, DATA>
{
public:
    CellHybrid() { };
    ~CellHybrid() { };
};

// B. Cartesian Grid
template <class DATA>
class CellCart : public CellNormal<DATA>
{
public:
    grid_index index;
    CellCart* parent;
    std::vector<CellCart*> children;
    
public:
    CellCart()
    : parent(NULL)
    {
        children.reserve(MAX_NUMBER_CHILDER_PER_CELL);
    };
    
    ~CellCart()
    {
        
    };
};

template <class DATA>
class CellCartPIC : public CellPIC<DATA>
{
public:
    grid_index index;
    CellCartPIC* parent;
    std::vector<CellCartPIC*> children;
    
public:
    CellCartPIC()
    : parent(NULL)
    {
        children.reserve(MAX_NUMBER_CHILDER_PER_CELL);
    };
    
    ~CellCartPIC()
    {
        
    };
};

template <class DATA>
class CellCartHybrid : public CellHybrid<DATA>
{
public:
    grid_index index;
    CellCartHybrid* parent;
    std::vector<CellCartHybrid*> children;
    
public:
    CellCartHybrid()
    : parent(NULL)
    {
        children.reserve(MAX_NUMBER_CHILDER_PER_CELL);
    };
    
    ~CellCartHybrid()
    {
        
    };
};




















#endif /* element_hpp */
