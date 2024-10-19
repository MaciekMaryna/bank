/******************************************************************************
 * Includes
 ******************************************************************************/
//#include <iostream>
//#include <stdint.h>
#include "Account.hpp"
#include "ForeginCurrencyAccount.hpp"

/*********** Class ForeginCurrencyAccount  ***********/
void ForeginCurrencyAccount::Withdraw(const double wit)
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