//
//  OP2ACFD.hpp
//  OP2A
//
//  Created by Kim M.K. on 16/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef OP2ACFD_hpp
#define OP2ACFD_hpp


#include "../CHEM/speciesDataBase.hpp"
#include "../DATA/problemSetup.hpp"
#include "../DATA/wallMaterial.hpp"

#include "gridCFD.hpp"
#include "primitive_variables.hpp"

void OP2A_CFD_ver1(ProbleSetup& problem,
                   GridBasicInfo& gridinfo,
                   GridMPI& gridmpi, GridGeo& gridgeo,
                   std::vector<species>& speciesdata,
                   wallMaterialDataBase& wall_material_database);



void initizliseFlowCondition(ProbleSetup* problem,
                             CFD::Grid* grid,
                             std::vector<variableMapCFD*>& CFD_variables,
                             std::vector< std::vector< std::vector<double> > >& U_flow,
                             std::vector< std::vector< std::vector<double> > >& Q_flow);
//void preProcessingPart1Version(int argc, char *argv[], double& t0);





#endif /* OP2ACFD_hpp */







