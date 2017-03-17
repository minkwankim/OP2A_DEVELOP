//
//  limiters.hpp
//  OP2A
//
//  Created by Kim M.K. on 13/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef limiters_hpp
#define limiters_hpp

#include <stdio.h>
#include <vector>

#include "../COMM/noninstantiable.hpp"
#include "../COMM/error_codes.hpp"
#include "../COMM/error_exception.hpp"

class limiter: public Common::NonInstantiable<limiter> {

public:
    static double Superbee(double& R);
    static double BarthJespersen(double& R);
    static double vanLeer(double& R);
    static double vanAlbada(double& R);
    static double min(double& R);
};


class limiter_slope: public Common::NonInstantiable<limiter_slope> {
    
public:
    static double Superbee(double& R);
    static double BarthJespersen(double& R);
    static double vanLeer(double& R);
    static double vanAlbada(double& R);
    static double min(double& R);
};


class limiter_w: public Common::NonInstantiable<limiter_w> {
    
public:
    static double Superbee(double& f);
    static double sin(double& f);
    static double vanLeer(double& f);
    static double vanAlbada(double& f);
    static double min(double& f);
};

#endif /* limiters_hpp */
