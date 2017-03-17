//
//  ProbIO.hpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef ProbIO_hpp
#define ProbIO_hpp

#include <stdio.h>
#include <string>
#include "problemDef.hpp"



class ProbIO_ver1 {
public:
    std::string filename_ProblemSetup;
    std::string filename_grid;
    std::string filename_speciesdatabase;
    std::string filename_wallmaterial;
    std::string filename_Output;
    
    
public:
    ProbIO_ver1();
    ~ProbIO_ver1();
    
    void read(const std::string& filename);
    void errorcheck_and_shows();
};



class ProbIO : public CURRENT_VERSION_PROBID
{
public:
    
public:
    ProbIO()  {   };
    ~ProbIO() {   };
};


#endif /* ProbIO_hpp */
