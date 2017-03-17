//
//  gridCFD.cpp
//  OP2A
//
//  Created by Kim M.K. on 11/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "gridCFD.hpp"
#include "../COMM/VectorCompare.hpp"


namespace CFD {
    

// 1. Class for GRID
//       [Part B]: Section for Constructor/Destructor
    Grid::Grid()
    {
        info  = NULL;
        mpi   = NULL;
        geo   = NULL;
        index = NULL;
        data  = NULL;
    }
    
    Grid::~Grid()
    {
        info  = NULL;
        mpi   = NULL;
        geo   = NULL;
        index = NULL;
        data  = NULL;
    }

    
    
    
    // [Part C]: Functions
    void Grid::allocateIndex()
    {
        if (info != NULL)
        {
            index = new GridData<grid_index_ver2>(info);
        }
        else
        {
            Common::ExceptionError(FromHere(), "Grid Inforamtion POINTER is not allocated. You need to allocate it FIRST!", Common::ErrorCodes::NotAllocated());
        }
    }
    
    
    void Grid::allocateData(std::vector<int>& NS, int ND, std::vector<int>& NE,
                            int type_node, int type_face, int type_cell,
                            bool f_implicit, int n_fluid)
    {
        if (info == NULL)
        {
            Common::ExceptionError(FromHere(), "Grid Inforamtion POINTER is not allocated. You need to allocate it FIRST!", Common::ErrorCodes::NotAllocated());
        }
        
        
        data = new GridDataVec<dataCFD>(info, n_fluid);

        for (int n= 0; n < n_fluid; n++)
        {
            for (int i = 0; i < data->nodes.size(); i++)    data->nodes[i][n].allocate(NS[n], ND, NE[n], f_implicit, type_node);
            for (int i = 0; i < data->faces.size(); i++)    data->faces[i][n].allocate(NS[n], ND, NE[n], f_implicit, type_face);
            for (int i = 0; i < data->cells.size(); i++)    data->cells[i][n].allocate(NS[n], ND, NE[n], f_implicit, type_cell);
            for (int i = 0; i < data->ghost.size(); i++)    data->ghost[i][n].allocate(NS[n], ND, NE[n], f_implicit, type_cell);
        }
        
        m_nodes.resize(data->nodes.size());
        m_faces.resize(data->faces.size());
        m_cells.resize(data->cells.size());
        m_ghost.resize(data->ghost.size());
    }
    
    
    void Grid::allocateInternalData()
    {
        if (info == NULL)
        {
            Common::ExceptionError(FromHere(), "Grid Inforamtion POINTER is not allocated. You need to allocate it FIRST!", Common::ErrorCodes::NotAllocated());
        }
        
        
        m_nodes.resize(info->NNM);
        m_faces.resize(info->NFM);
        m_cells.resize(info->NCM);
        m_ghost.resize(info->NCM);
        
        for (int i = 0; i < m_nodes.size(); i++)    m_nodes[i] = new Node;
        for (int i = 0; i < m_faces.size(); i++)    m_faces[i] = new Face;
        for (int i = 0; i < m_cells.size(); i++)    m_cells[i] = new Cell;
        for (int i = 0; i < m_ghost.size(); i++)    m_ghost[i] = new Cell;

        
        // Geometry
        if (geo != NULL)
        {
            for (int i = 0; i < m_nodes.size(); i++)    m_nodes[i]->geom = &geo->nodes[i];
            for (int i = 0; i < m_faces.size(); i++)    m_faces[i]->geom = &geo->faces[i];
            for (int i = 0; i < m_cells.size(); i++)    m_cells[i]->geom = &geo->cells[i];
            for (int i = 0; i < m_ghost.size(); i++)    m_ghost[i]->geom = &geo->ghost[i];
        }
        else
        {
            for (int i = 0; i < m_nodes.size(); i++)    m_nodes[i]->geom = NULL;
            for (int i = 0; i < m_faces.size(); i++)    m_faces[i]->geom = NULL;
            for (int i = 0; i < m_cells.size(); i++)    m_cells[i]->geom = NULL;
            for (int i = 0; i < m_ghost.size(); i++)    m_ghost[i]->geom = NULL;
        }
        
        // Index
        if (index != NULL)
        {
            for (int i = 0; i < m_nodes.size(); i++)    m_nodes[i]->inde = &index->nodes[i];
            for (int i = 0; i < m_faces.size(); i++)    m_faces[i]->inde = &index->faces[i];
            for (int i = 0; i < m_cells.size(); i++)    m_cells[i]->inde = &index->cells[i];
            for (int i = 0; i < m_ghost.size(); i++)    m_ghost[i]->inde = &index->ghost[i];
        }
        else
        {
            for (int i = 0; i < m_nodes.size(); i++)    m_nodes[i]->inde = NULL;
            for (int i = 0; i < m_faces.size(); i++)    m_faces[i]->inde = NULL;
            for (int i = 0; i < m_cells.size(); i++)    m_cells[i]->inde = NULL;
            for (int i = 0; i < m_ghost.size(); i++)    m_ghost[i]->inde = NULL;
        }
        
        // DATA
        if (data != NULL)
        {
            for (int i = 0; i < m_nodes.size(); i++)    m_nodes[i]->data = &data->nodes[i];
            for (int i = 0; i < m_faces.size(); i++)    m_faces[i]->data = &data->faces[i];
            for (int i = 0; i < m_cells.size(); i++)    m_cells[i]->data = &data->cells[i];
            for (int i = 0; i < m_ghost.size(); i++)    m_ghost[i]->data = &data->ghost[i];
        }
        else
        {
            for (int i = 0; i < m_nodes.size(); i++)    m_nodes[i]->data = NULL;
            for (int i = 0; i < m_faces.size(); i++)    m_faces[i]->data = NULL;
            for (int i = 0; i < m_cells.size(); i++)    m_cells[i]->data = NULL;
            for (int i = 0; i < m_ghost.size(); i++)    m_ghost[i]->data = NULL;
        }
    }
    
    // Calling functions
    Node* Grid::NODE(int id)
    {
        op_assert(id > 0);
        int npos = geo->whereisNodes[id];
        return (m_nodes[npos]);
    }
    
    
    Face* Grid::FACE(int id)
    {
        op_assert(id > 0);
        int npos = geo->whereisFaces[id];
        return (m_faces[npos]);
    }
    
    Cell* Grid::CELL(int id)
    {
        int pos;
        
        if (id < 0)
        {
            pos = geo->whereisGhost[-id];
            return (m_ghost[pos]);
        }
        else
        {
            pos = geo->whereisCells[id];
            return (m_cells[pos]);
        }
    }
    
    
    void Grid::errorCheck()
    {
        std::cout << "[Checking Memory allocation of Grid DATA.....]" << std::endl;
        
        // Basic Checking
        if (info == NULL)   Common::ExceptionError(FromHere(), "GridBasic Inforamtion POINTER is not allocated.", Common::ErrorCodes::NotAllocated());
        if (mpi  == NULL)   Common::ExceptionError(FromHere(), "GridMPI Inforamtion POINTER is not allocated.", Common::ErrorCodes::NotAllocated());
        if (data == NULL)   Common::ExceptionError(FromHere(), "GridData Inforamtion POINTER is not allocated.", Common::ErrorCodes::NotAllocated());
        
        std::cout << "  ---> Grid Basic Infomation:  O.K !" << std::endl;
        std::cout << "  ---> Grid MPI Infomation  :  O.K !" << std::endl;
        
        std::cout << "  ---> Grid Index Infomation:  ";
        if (index == NULL) std::cout << "O.K (It is not allocated) !" << std::endl;
        else               std::cout << "O.K !" << std::endl;
        
        std::cout << "  ---> Grid DATA Infomation :  O.K !" << std::endl;
        
        
        // Internal member checking
        bool flag;
        
        std::cout << "  ---> Internal DATA(NODE)  :  ";
        flag = Common::VectorCompare::hasSameComponent<Node*> (m_nodes);
        if (flag == true)  Common::ExceptionError(FromHere(), "Problem on allocated memory for internal Node DATA.", Common::ErrorCodes::Mismatch());
        else               std::cout << "O.K !" << std::endl;

        std::cout << "  ---> Internal DATA(FACE)  :  ";
        flag = Common::VectorCompare::hasSameComponent<Face*> (m_faces);
        if (flag == true)  Common::ExceptionError(FromHere(), "Problem on allocated memory for internal Face DATA.", Common::ErrorCodes::Mismatch());
        else               std::cout << "O.K !" << std::endl;
        
        std::cout << "  ---> Internal DATA(CELL)  :  ";
        flag = Common::VectorCompare::hasSameComponent<Cell*> (m_cells);
        if (flag == true)  Common::ExceptionError(FromHere(), "Problem on allocated memory for internal Cell DATA.", Common::ErrorCodes::Mismatch());
        else               std::cout << "O.K !" << std::endl;
        
        std::cout << "  ---> Internal DATA(Ghost) :  ";
        flag = Common::VectorCompare::hasSameComponent<Cell*> (m_ghost);
        if (flag == true)  Common::ExceptionError(FromHere(), "Problem on allocated memory for internal Ghost DATA.", Common::ErrorCodes::Mismatch());
        else               std::cout << "O.K !" << std::endl;
        
        std::cout << "[DONE]" << std::endl << std::endl;
    }
}















