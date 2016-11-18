//
//  grid.cpp
//  OP2A
//
//  Created by Kim M.K. on 10/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "grid.hpp"

GridBasicInfo::GridBasicInfo()
:gridFactor(0.0), isAxisymmeric(0), DIM(0), NNM(0), NFM(0), NCM(0), NGM(0), m_completed(false)
{
    
}

GridBasicInfo::~GridBasicInfo()
{
    
}

bool GridBasicInfo::isCompleted()
{
    return (m_completed);
}

void GridBasicInfo::setComplete()
{
    m_completed = true;
}

void GridBasicInfo::needToUpdate()
{
    m_completed = false;
}

void GridBasicInfo::read(const std::string& mesh_file_name)
{
    // 1. Open file to read
    std::ifstream mesh_file;
    mesh_file.open(mesh_file_name.c_str());
    if (!mesh_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find grid file. Please check your grid file!", Common::ErrorCodes::FileSystem());
    }
    
    DIM = -1;
    NNM = -1;
    NFM = -1;
    NCM = -1;
    NGM = -1;
        
    
    int tempInt;
    std::string line;
        
        
    // Over information read
    while (!mesh_file.eof())
    {
        getline(mesh_file, line);
            
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "DIM= ");
        if (tempInt != -1)	DIM = tempInt;
            
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "NNM= ");
        if (tempInt != -1)	NNM = tempInt;
            
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "NFM= ");
        if (tempInt != -1)	NFM = tempInt;
        
        tempInt = -1;
        tempInt = Common::read_data_from_string::read_numeric<int>(line, "NCM= ");
        if (tempInt != -1)	NCM = tempInt;
    }
        
    if (DIM == -1) Common::ExceptionError(FromHere(), "Cannot find dimension information in the gridfile!", Common::ErrorCodes::NoSuchValue());
    if (NNM == -1) Common::ExceptionError(FromHere(), "Cannot find NNM information in the grid file!", Common::ErrorCodes::NoSuchValue());
    if (NFM == -1) Common::ExceptionError(FromHere(), "Cannot find NFM information in the grid file!", Common::ErrorCodes::NoSuchValue());
    if (NCM == -1) Common::ExceptionError(FromHere(), "Cannot find NCM information in the grid file!", Common::ErrorCodes::NoSuchValue());
    
    m_completed = true;
}


// Class for MPI Data
GridMPI::GridMPI()
: numLines(0), sendGhost(NULL), receiveGhost(NULL)
{
    
}

GridMPI::~GridMPI()
{
    sendGhost = NULL;
    receiveGhost = NULL;
}


















































