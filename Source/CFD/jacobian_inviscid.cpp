//
//  jacobian_inviscid.cpp
//  OP2A
//
//  Created by Kim M.K. on 07/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "jacobian_inviscid.hpp"


void Jacobian_Inviscid::calculate_dYs_dQ(std::vector<double>& Q, vector2D& dYs_dQ)
{
    int index;
    int N_tot = NS+ND+NE;
    
    m_rho  = 0.0;
    for (int s = 0; s < NS; s++)
    {
        index    = Qid(s,0);
        m_rho   += Q[index];
    }
    
    
    // Initialize dYs_dQ
    Common::VectorMulti<double>::resize(dYs_dQ, NS, N_tot);
    for (int s = 0; s < NS; s++)
    {
        for (int r = 0; r < N_tot; r++)
        {
            dYs_dQ[s][r] = 0.0;
        }
    }
    
    
    
    for (int s = 0; s < NS; s++)
    {
        index    = Qid(s,0);
        dYs_dQ[s][index] = 1.0;
        
        double Ys = Q[s]/m_rho;
        for (int r = 0; r < NS; r++)
        {
            index    = Qid(r,0);
            dYs_dQ[s][index] -= Ys;
        }
    }

    for (int s = 0; s < NS; s++)
    {
        for (int r = 0; r < NS; r++)
        {
            index            = Qid(r,0);
            dYs_dQ[s][index] = dYs_dQ[s][index]/m_rho;
        }
    }
}


void Jacobian_Inviscid::calculate_du_dQ(std::vector<double>& V,   vector2D& du_dQ)
{
    // Initialize dYs_dQ
    int index;
    int N_tot = NS+ND+NE;
    
    Common::VectorMulti<double>::resize(du_dQ, ND, N_tot);
    for (int s = 0; s < ND; s++)
    {
        for (int r = 0; r < N_tot; r++)
        {
            du_dQ[s][r] = 0.0;
        }
    }
    
    
    for (int s = 0; s < ND; s++)
    {
        index = Qid(s, 1);
        double u = V[index];
        du_dQ[index][index] = 1.0;

        
        for (int r = 0; r < NS; r++)
        {
            index = Qid(r, 0);
            du_dQ[s][index] += -u;
        }
    }
    
}
