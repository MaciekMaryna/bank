#ifndef PERSONALACCOUNT_H
#define PERSONALACCOUNT_H

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"
#include "PersonalAccount.hpp"

/*********** Class PersonalAccount (debit) ************/
class  PersonalAccount : public Account
{
    protected:
        float OverdraftInterestRate;
        double OverdraftLimit;
    public:
        void Deposit(const double) override; 
        Status_t Withdraw(const double) override;
        Status_t Capitalise(void) override;
        void Set_OverdraftInterestRate(const double);
        double Get_OverdraftInterestRate(void);
        void Set_OverdraftLimit(const double);
        double Get_OverdraftLimit(void);          
};

#endif /* #ifndef PERSONALACCOUNT_H */