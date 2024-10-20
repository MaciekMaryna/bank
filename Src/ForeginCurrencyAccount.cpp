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
        //no action
    }
    else 
    {
        this -> Balance -= wit;
    }
} 