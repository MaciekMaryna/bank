/******************************************************************************
 * Includes
 ******************************************************************************/
// #include <iostream>
// #include <stdint.h>
// #include "Account.hpp"
#include "PersonalAccount.hpp"

/*********** Class PersonalAccount (debit) ************/
void PersonalAccount::PayOverdraftInterest(void)
{
    if (this->Balance < 0)
    {
        this -> BalanceOld = this -> Balance;
        this -> Balance *= (1 + this->OverdraftInterestRate);
    }
}

void PersonalAccount::Withdraw(const double wit)
{
    if(Balance - wit < (-OverdraftLimit))
    {
        this -> LastOperStatus = NO_ANOUGH_DEBIT;        
    }
    else 
    {
        this -> BalanceOld = this -> Balance;
        this -> Balance -= wit;
        this -> LastOperStatus = OPERATION_OK; 
    }
} 
