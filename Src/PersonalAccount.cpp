/******************************************************************************
 * Includes
 ******************************************************************************/
// #include <iostream>
// #include <stdint.h>
#include "Account.hpp"
#include "PersonalAccount.hpp"

/*********** Class PersonalAccount (debit) ************/
void PersonalAccount::Deposit(const double dep)
{
    this -> Balance += dep;
}

Status_t PersonalAccount::Withdraw(const double wit)
{
    Status_t RetStatus = OPERATION_OK;
    if(Balance - wit < (-OverdraftLimit))
    {
        RetStatus = NO_ANOUGH_FUNDS;
    }
    else 
    {
        this -> Balance -= wit;
        RetStatus = OPERATION_OK;
    }
    return RetStatus;
} 

Status_t PersonalAccount::Capitalise(void)
{
    Status_t RetStatus = OPERATION_OK;
    if (this->Balance < 0)
    {
        this -> Balance *= (1 + this->OverdraftInterestRate);
    }
    return RetStatus;
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

