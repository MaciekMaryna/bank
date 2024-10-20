/******************************************************************************
 * Includes
 ******************************************************************************/
// #include <iostream>
// #include <stdint.h>
#include "Account.hpp"
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

void PersonalAccount::Set_OverdraftInterestRate(const double rat)
{
    if(rat > 0)
    {
        this -> OverdraftInterestRate = rat;
    }
    else 
    {
        this -> OverdraftInterestRate = -rat;  // Beter then set to zero form bank iterest perpective
    }
}

double PersonalAccount::Get_OverdraftInterestRate(void)
{
    return this -> OverdraftInterestRate;
}

void PersonalAccount::Set_OverdraftLimit(const double lim)
{
    if(lim > 0)
    {
        this -> OverdraftLimit = lim;
    }
    else 
    {
        this -> OverdraftLimit = -lim;  // Limit shoud be a positve number
    }    
}

double PersonalAccount::Get_OverdraftLimit(void)
{
    return this -> OverdraftLimit;
}

