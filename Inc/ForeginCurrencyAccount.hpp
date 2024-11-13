#ifndef FOREGINCURRENCYACCOUNT_H
#define FOREGINCURRENCYACCOUNT_H
/******************************************************************************
 * Includes
 ******************************************************************************/
//#include <iostream>
//#include <stdint.h>
#include "Account.hpp"

/*********** Class ForeginCurrencyAccount  ***********/
class ForeginCurrencyAccount : public Account
{
    private:
    protected:
    public:
        void Deposit(const double) override; 
        Status_t Withdraw(const double) override;
        Status_t Capitalise(void) override;               
};

#endif /* #ifndef FOREGINCURRENCYACCOUNT_H */