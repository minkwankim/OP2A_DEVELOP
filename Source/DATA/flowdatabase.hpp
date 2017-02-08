//
//  flowdatabase.hpp
//  OP2A
//
//  Created by Kim M.K. on 22/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef flowdatabase_hpp
#define flowdatabase_hpp

#include <stdio.h>
#include <vector>
#include "dataDef.hpp"




class flowDataBase {
public:
    std::vector<double> rhos;   // Species Densities
    std::vector<double> u;      // Velocities
    std::vector<double> T;      // Temperature of each energy modes

    
protected:
    bool m_assigned;
    
public:
    flowDataBase();
    flowDataBase(int NS);
    
    ~flowDataBase();
    
    
    void assignSize(int NS, int ND, int NE);
    void reassign(int NS, int ND, int NE);
    bool check();
    
    void allocateU(int NS, int ND, int E_Tr, int E_Tv, int E_Tele, int E_Te, std::vector<double>& U);
    //void allocateU(std::vector<int>&NS, int ND, std::vector<int>&NE, int n_fluid, )
};











#endif /* flowdatabase_hpp */
