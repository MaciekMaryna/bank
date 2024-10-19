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
        void Withdraw(const double) override;               
};

#endif /* #ifndef FOREGINCURRENCYACCOUNT_H */