/******************************************************************************
 * Includes
 ******************************************************************************/
//#include <iostream>
//#include <stdint.h>
#include "Account.hpp"
#include "SavingsAccount.hpp"

/*************** Class SavingsAccount  ***************/

void SavingsAccount::Withdraw(const double wit)
{
    if(Balance - wit < 0)
    {
        this -> LastOperStatus = NO_ANOUGH_FUNDS;        
    }
    else 
    {   
        this -> BalanceOld = this -> Balance;
        this -> Balance -= wit;
        this -> LastOperStatus = OPERATION_OK;        
    }
} 

void SavingsAccount::CapitaliseIterest(void)
{
    this -> BalanceOld = this -> Balance;
    this -> Balance *= (1 + this->InterestRate);
}
