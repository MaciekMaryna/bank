#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
/******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <stdint.h>
#include "Account.hpp"
#include "CheckingAccount.hpp"

/******************************************************************************
 * Typedefs
 ******************************************************************************/

/*************** Class CheckingAccount  ***************/
class CheckingAccount : public Account
{
    private:
    protected:
    public:
        CheckingAccount();
        void PayOverdraftInterest(void);    
        void Withdraw(const double) override;      
};

#endif /* #ifndef CHECKINGACCOUNT_H */