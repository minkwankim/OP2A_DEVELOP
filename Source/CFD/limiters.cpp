//
//  limiters.cpp
//  OP2A
//
//  Created by Kim M.K. on 13/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//
#include <math.h>
#include <cmath>
#include "limiters.hpp"


double limiter::Superbee(double& R)
{
    double phi = 0.0;
    
    if (R > 0)
    {
        double aux1 = 0.0;
        aux1 = fmax(1.0, R);
        aux1 = fmin(2.0, aux1);
        
        phi  = fmin(aux1, 2*R);
    }
    
    return (phi);
}

double limiter::BarthJespersen(double& R)
{
    double phi = 0.0;
    
    if (R > 0)
    {
        double aux1 = 0.0;
        double aux2 = 0.0;
        
        aux1 = fmin(1.0, (4*R)/(R + 1.0));
        aux2 = fmin(1.0,   4.0/(R + 1.0));
        
        phi  = 0.5 * (R + 1) * fmin(aux1, aux2);
    }
    
    return (phi);
}


double limiter::vanLeer(double& R)
{
    double phi = 0.0;
    
    if (R > 0.0)
    {
        phi = (2.0*R) / (R + 1.0);
    }
    
    return (phi);
}


double limiter::vanAlbada(double& R)
{
    double phi = 0.0;

    if (R > 0)
    {
        phi = (R*R + R) / (R*R + 1.0);
    }
    
    return (phi);
}


double limiter::min(double& R)
{
    double phi = 0.0;
    
    if (R > 0.0)
    {
        phi = fmin(1.0, R);
        
    }
    return (phi);

}





double limiter_slope::BarthJespersen(double& R)
{
    double phi = 0.0;
    
    if (R >= 0.0)
    {
        double aux1 = 0.0;
        aux1 = 4.0 / (R + 1);
        
        aux1 = fmin (1, aux1);
        phi  = fmin (aux1, 4*R / (R + 1));
    }
    
    return (phi);
}

double limiter_slope::vanLeer(double& R)
{
    double phi = 0.0;
    
    if (R >= 0.0)
    {
        phi = 4.0*R / pow(R+1.0, 2.0);
    }
    
    return (phi);
}

double limiter_slope::vanAlbada(double& R)
{
    double phi = 0.0;
    
    if (R >= 0.0)
    {
        phi = 2.0*R / (R*R + 1.0);
    }
    
    return (phi);
}

double limiter_slope::min(double& R)
{
    double phi = 0.0;
    
    if (R >= 0.0)
    {
        phi = fmin(2.0 / (1 + R), 2.0*R / (1 +R));
    }
    
    return (phi);
}


double limiter_slope::Superbee(double& R)
{
    double phi = 0.0;
    
    if (R >= 0.0)
    {
        double aux1 = limiter::Superbee(R);
        double aux2 = (R + 1.0 ) / 2.0;
        
        phi = aux1 / aux2;
    }
    
    return (phi);
}



double limiter_w::Superbee(double& f)
{
    double w = 0.0;
    
    if (w >= 0.0 && w <= 1.0)
    {
        double aux1 = 0.0;
        aux1 = fmin(1.0, 4*f);
        w    = fmin(aux1, 4.0*(1.0 - f));
    }
    
    return (w);
}


double limiter_w::vanLeer(double& f)
{
    double w = 0.0;
    
    if (w >= 0.0 && w <= 1.0)
    {
        w    = 4.0 * f * (1.0-f);
    }
    
    return (w);
}

double limiter_w::vanAlbada(double& f)
{
    double w = 0.0;
    
    if (w >= 0.0 && w <= 1.0)
    {
        w = (2.0*f)*(1.0-f) / (f*f + pow(1.0-f, 2.0));
    }
    
    return (w);
}

double limiter_w::sin(double& f)
{
    double w = 0.0;
    
    if (w >= 0.0 && w <= 1.0)
    {
        double aux = 3.141592 * f;
        w = sin(aux);
    }
    
    return (w);
}

double limiter_w::min(double& f)
{
    double w = 0.0;
    
    if (w >= 0.0 && w <= 1.0)
    {
        w = fmin(2.0*f, 2.0*(1.0-f));
    }
    
    return (w);
}
