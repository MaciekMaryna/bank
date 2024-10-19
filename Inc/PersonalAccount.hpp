#ifndef PERSONALACCOUNT_H
#define PERSONALACCOUNT_H

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"

/*********** Class PersonalAccount (debit) ************/
class  PersonalAccount
{
    public:
        void PayOverdraftInterest(void);
        void Withdraw(const double);
};

#endif /* #ifndef PERSONALACCOUNT_H */