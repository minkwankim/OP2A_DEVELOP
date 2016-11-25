//
//  wallMaterial.cpp
//  OP2A
//
//  Created by Kim M.K. on 23/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "wallMaterial.hpp"


wallMaterial::wallMaterial()
:emissivity_Model(0), emissivity_T0(0), emissivity_coeff_above(6), emissivity_coeff_below(6)
{
    
}

wallMaterial::~wallMaterial()
{
    
}






wallMaterialDataBase::wallMaterialDataBase()
{
    
}


wallMaterialDataBase::~wallMaterialDataBase()
{
    
}


void wallMaterialDataBase::read(const std::string& filename)
{
    // Open File to read
    std::ifstream	prob_file;
    prob_file.open(filename.c_str());
    if (!prob_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Wall Material Data file. Please check your file!", Common::ErrorCodes::FileSystem());
    }

    
    // Read DATA
    std::string	line;
    std::string tempText;
    int tempInt;
    int n = 0;
    double tempDouble;

    
    while (! prob_file.eof())
    {
        getline(prob_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        if (line == DATA_WALL_START)
        {
            data.resize(n+1);
            
            while (line != DATA_WALL_END)
            {
                getline(prob_file, line);
                Common::read_data_from_string::remove_comments(line, "%");
                
                tempText = "";
                tempText = Common::read_data_from_string::read_string(line, "NAME:");
                if (tempText != "") data[n].name = tempText;
                
                if (line.compare(0, 11, "EMISSIVITY:") == 0)
                {
                    tempDouble = -1.0;
                    tempInt    = 1;
                    sscanf(line.c_str(), "EMISSIVITY: %lf %d", &tempDouble, &tempInt);
                    
                    if (tempDouble != -1.0) data[n].emissivity_T0 = tempDouble;
                    if (tempInt != -1.0) data[n].emissivity_Model = tempInt;
                    
                    switch (data[n].emissivity_Model)
                    {
                        case 0:
                            prob_file >> data[n].emissivity_coeff_below[0] >> data[n].emissivity_coeff_below[1] >> data[n].emissivity_coeff_below[2] >> data[n].emissivity_coeff_below[3] >> data[n].emissivity_coeff_below[4] >> data[n].emissivity_coeff_below[5];
                            
                            prob_file >> data[n].emissivity_coeff_above[0] >> data[n].emissivity_coeff_above[1] >> data[n].emissivity_coeff_above[2] >> data[n].emissivity_coeff_above[3] >> data[n].emissivity_coeff_above[4] >> data[n].emissivity_coeff_above[5];
                            break;
                    }
                }
            }
            
            datamap.insert(data[n].name, n);
            n++;
        }
    }
    
    
    prob_file.close();
}




void wallMaterialDataBase::add(const std::string& filename)
{
    // Open File to read
    std::ifstream	prob_file;
    prob_file.open(filename.c_str());
    if (!prob_file.is_open())
    {
        Common::ExceptionError(FromHere(), "Cannot find Wall Material Data file. Please check your file!", Common::ErrorCodes::FileSystem());
    }
    
    
    // Read DATA
    std::string	line;
    std::string tempText;
    int tempInt;
    int n;
    double tempDouble;
    
    wallMaterial temp_data;
    n = data.size();
    
    
    while (! prob_file.eof())
    {
        getline(prob_file, line);
        Common::read_data_from_string::remove_comments(line, "%");
        
        temp_data.name = "N/A";
        
        if (line == DATA_WALL_START)
        {
            while (line != DATA_WALL_END)
            {
                getline(prob_file, line);
                Common::read_data_from_string::remove_comments(line, "%");
                
                tempText = "";
                tempText = Common::read_data_from_string::read_string(line, "NAME:");
                if (tempText != "") temp_data.name = tempText;
                    
         
                if (line.compare(0, 11, "EMISSIVITY:") == 0)
                {
                    tempDouble = -1.0;
                    tempInt    = 1;
                    sscanf(line.c_str(), "EMISSIVITY: %lf %d", &tempDouble, &tempInt);
                    
                    if (tempDouble != -1.0) temp_data.emissivity_T0 = tempDouble;
                    if (tempInt != -1.0) temp_data.emissivity_Model = tempInt;
                    
                    switch (data[n].emissivity_Model)
                    {
                        case 1:
                            prob_file >> temp_data.emissivity_coeff_below[0] >> temp_data.emissivity_coeff_below[1] >> temp_data.emissivity_coeff_below[2] >> temp_data.emissivity_coeff_below[3] >> temp_data.emissivity_coeff_below[4] >> temp_data.emissivity_coeff_below[5];
                            
                            prob_file >> temp_data.emissivity_coeff_above[0] >> temp_data.emissivity_coeff_above[1] >> temp_data.emissivity_coeff_above[2] >> temp_data.emissivity_coeff_above[3] >> temp_data.emissivity_coeff_above[4] >> temp_data.emissivity_coeff_above[5];
                            break;
                    }
                }
            }
        }
        
        
        if (temp_data.name != "N/A" && datamap.exists(temp_data.name) != true)
        {
            data.resize(n++);
            data[n] = temp_data;
            n++;
        }
    }
    
    prob_file.close();
}



wallMaterial wallMaterialDataBase::find(std::string name)
{
    int n = datamap.find(name);
    return (data[n]);
}

























