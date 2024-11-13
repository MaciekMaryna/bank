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
        void Deposit(const double) override;   
        Status_t Withdraw(const double) override; 
        Status_t Capitalise(void) override;
};

#endif /* #ifndef CHECKINGACCOUNT_H */