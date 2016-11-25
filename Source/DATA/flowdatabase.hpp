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


#define FLUID_DATA_MAX_SPECIES 11
#define FLUID_DATA_MAX_ENERGY_MODE 4



class flowDataBase {
public:
    std::vector<double> rhos;   // Species Densities
    std::vector<double> u;      // Velocities
    std::vector<double> rho_u;  // Momentum
    std::vector<double> T;      // Temperature of each energy modes
    std::vector<double> E;      // Energy of each energy modes
    

    std::vector<double*> Q;      // Premitive variables
    std::vector<double*> U;      // Conservative variables
    
protected:
    bool m_assigned;
    
public:
    flowDataBase();
    flowDataBase(int NS, int ND, int NE);
    
    ~flowDataBase();
    
    
    void assignSize(int NS, int ND, int NE);
    void reassign(int NS, int ND, int NE);
    bool check();

    
};










#endif /* flowdatabase_hpp */
