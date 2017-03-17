//
//  variableMapCFD.hpp
//  OP2A
//
//  Created by Kim M.K. on 26/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef variableMapCFD_hpp
#define variableMapCFD_hpp

#include <stdio.h>
#include "../DATA/variableMap.hpp"
#include "../CHEM/species.hpp"


class variableMapCFDBase :public variableMap
{
public:
    std::vector<unsigned int> startIndex;
    
protected:
    double m_rho;
    
public:
    explicit variableMapCFDBase();
    explicit variableMapCFDBase(variableMap input);
    ~variableMapCFDBase();
    

    variableMapCFDBase&	operator= (variableMap input);
    void setting(int density, int velocity, int energy);
    void setting();
    
    int Qid(int s, int mode);
    int EinQ(int mode);
    int Pressure();
};





class variableMapCFD :public variableMapCFDBase
{
    /*
public:
    std::vector<unsigned int> startIndex;
    
protected:
    double m_rho;

public:
    explicit variableMapCFD();
    explicit variableMapCFD(variableMap input);
     ~variableMapCFD();
    
    // [Part C]: Functions
    variableMapCFD&	operator= (variableMap input);
    void setting(int density, int velocity, int energy);
    void setting();
    
    int Qid(int s, int mode);
    int EinQ(int mode);
    int Pressure();
    */
    
public:
    explicit variableMapCFD()                  : variableMapCFDBase() {};
    explicit variableMapCFD(variableMap input) : variableMapCFDBase(input) {};
    
    void constructU(std::vector<double>&rho_s, std::vector<double>& u, std::vector<double>& Ts, std::vector<double>& U);
    void constructUfromGlobal(std::vector<double>&rho_s, std::vector<double>& u, std::vector<double>& Ts, std::vector<double>& U, int flag);

    
    void UtoQ_Common(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q);
    void UtoW_Common(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W);
    void QtoU_Common(std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U);

    virtual void UtoQ(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& Q) = 0;
    virtual void UtoW(std::vector<double>& U, std::vector<species>& speciesdata, std::vector<double>& W) = 0;
    virtual void QtoU(std::vector<double>& Q, std::vector<species>& speciesdata, std::vector<double>& U) = 0;
    
    

};


#endif /* variableMapCFD_hpp */
