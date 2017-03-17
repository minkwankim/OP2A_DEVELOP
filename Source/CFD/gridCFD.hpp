//
//  gridCFD.hpp
//  OP2A
//
//  Created by Kim M.K. on 11/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef gridCFD_hpp
#define gridCFD_hpp

#include <stdio.h>
#include "../DATA/dataCFD.hpp"
#include "../GRID/grid.hpp"


namespace CFD {
    
    typedef Elem_ver2<NodeBase, grid_index_ver2, std::vector<dataCFD> >  Node;
    typedef Elem_ver2<FaceBase, grid_index_ver2, std::vector<dataCFD> >  Face;
    typedef Elem_ver2<CellBase, grid_index_ver2, std::vector<dataCFD> >  Cell;
    
    
    
    // 1. Class for GRID
    class Grid
    {
        // [Part A]: Section for Data
    public:
        GridBasicInfo*             info;
        GridMPI*                   mpi;
        GridGeo*                   geo;
        GridData<grid_index_ver2>* index;
        GridDataVec<dataCFD>*      data;
        
    protected:
        std::vector<Node*>          m_nodes;
        std::vector<Face*>          m_faces;
        std::vector<Cell*>          m_cells;
        std::vector<Cell*>          m_ghost;
        
        
        // [Part B]: Section for Constructor/Destructor
    public:
        Grid();
        ~Grid();
        
        // [Part C]: Functions
    public:
        void allocateIndex();
        void allocateData(std::vector<int>& NS, int ND, std::vector<int>& NE,
                          int type_node, int type_face, int type_cell,
                          bool f_implicit, int n_fluid);
        void allocateInternalData();
        void errorCheck();
        
        Node* NODE(int id);
        Face* FACE(int id);
        Cell* CELL(int id);
    };
}





#endif /* gridCFD_hpp */
