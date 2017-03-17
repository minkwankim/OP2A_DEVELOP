//
//  problemDef.h
//  OP2A
//
//  Created by Kim M.K. on 21/11/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#ifndef problemDef_h
#define problemDef_h

// Version Setting
#define CURRENT_VERSION_PROBBASIC   ProbBasicInfo_ver1
#define CURRENT_VERSION_PROBNUMCOM  ProbNumericalMethodBase_ver1
#define CURRENT_VERSION_PROBNUMCFD  ProbNumericalMethodCFD_ver1
#define CURRENT_VERSION_PROBNUMDSMC ProbNumericalMethodDSMC_ver1
#define CURRENT_VERSION_PROBNUMHYBR ProbNumericalMethodHybrid_ver1
#define CURRENT_VERSION_PROBPHYS    ProbPhysicalModel_ver1
#define CURRENT_VERSION_PROBICBC    ProbICBC_ver1
#define CURRENT_VERSION_PROBCOMP    ProbCOMP_ver1
#define CURRENT_VERSION_PROBID      ProbIO_ver1







// Definitions
#define PROB_SETUP_TITLE                "Title:"

#define PROB_SETUP_MODE                 "Mode:"
#define PROB_SETUP_COV_CRI              "Convergence Criterion:"
#define PROB_SETUP_DT_MAX               "Max Time-step:"
#define PROB_SETUP_T_MAX                "Max Time:"
#define PROB_SETUP_N_MAX                "Max Iteration:"


#define PROB_SETUP_CFD_ORDER            "Order:"
#define PROB_SETUP_INTEGRATION_TIME     "Time Integration Method:"
#define PROB_SETUP_INTEGRATION_SPACE    "Spatial Integration Method:"
#define PROB_SETUP_FLUX_LIMITER         "Limiter:"
#define PROB_SETUP_GRADIENT_CALCULATION "Gradient Calculation Method:"
#define PROB_SETUP_CFL_INI              "Initial CFL Number:"
#define PROB_SETUP_CFL_MAX              "Max CFL Number:"
#define PROB_SETUP_CFL_MET              "CFL Increase Method:"
#define PROB_SETUP_CFL_SAT              "Number of Iteration before CFL 1.0:"
#define PROB_SETUP_REX_INV              "Relaxation(Inviscid):"
#define PROB_SETUP_REX_VIC              "Relaxation(Viscous):"
#define PROB_SETUP_PRESSURE_SWITCH      "Pressure Switch Factor:"
#define PROB_SETUP_SLIP_ACCOM           "Accommodation Coefficient for Slip BCs:"

#define PROB_SETUP_TEMP                 "Temperature Model:"
#define PROB_SETUP_FLU                  "Fluid Model:"
#define PROB_SETUP_MIX_RULE             "Mixing Rule:"
#define PROB_SETUP_VIS                  "Viscosity Model:"
#define PROB_SETUP_DIF                  "Diffusivity Model:"
#define PROB_SETUP_CON                  "Conductivity Model:"
#define PROB_SETUP_LEWIS                "Lewis number:"

#define PROB_SETUP_INI_METHOD           "Initialisation method:"
#define PROB_SETUP_INI_START            "#COND NUM[START]:"
#define PROB_SETUP_INI_END              "#COND NUM[END]"
#define PROB_SETUP_INLET                "Inlet Condition"
#define PROB_SETUP_WALL                 "Wall Condition"
#define PROB_SETUP_WALL_MAT             "Wall Material"

#define PROB_SETUP_NUM_FLUID            "Number of Fluids:"
#define PROB_SETUP_MIX_RULE             "Mixing Rule:"
#define PROB_SETUP_VISCOSITY            "Viscosity Model:"
#define PROB_SETUP_DIFFUSITY            "Diffusivity Model:"
#define PROB_SETUP_CONDUCTIVITY         "Conductivity Model:"
#define PROB_SETUP_LEWIS                "Lewis number:"
#define PROB_SETUP_SPECIES              "Species List:"

#define PROB_SETUP_NTHREAD              "THREAD PER NODE:"






#define GRID_FILENAME	"Grid file name:"
#define OUT_FILENAME	"Result file name:"







#endif /* problemDef_h */
