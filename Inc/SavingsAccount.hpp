#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

/******************************************************************************
 * Includes
 ******************************************************************************/
//#include <iostream>
//#include <stdint.h>
#include "Account.hpp"

/*************** Class SavingsAccount  ***************/
class SavingsAccount : public Account
{
    private:
    protected:
    public:
        float InterestRate;
        void Deposit(const double) override; 
        Status_t Withdraw(const double) override;           
        Status_t Capitalise(void);        
};

#endif /* #ifndef SAVINGSACCOUNT_H */