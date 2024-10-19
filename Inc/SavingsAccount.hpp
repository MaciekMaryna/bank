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
        void CapitaliseIterest(void);
        void Withdraw(const double) override;           
};

#endif /* #ifndef SAVINGSACCOUNT_H */