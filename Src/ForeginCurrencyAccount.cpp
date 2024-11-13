/******************************************************************************
 * Includes
 ******************************************************************************/
//#include <iostream>
//#include <stdint.h>
#include "Account.hpp"
#include "ForeginCurrencyAccount.hpp"

/*********** Class ForeginCurrencyAccount  ***********/
void ForeginCurrencyAccount::Deposit(const double dep)
{
    this -> Balance += dep;
}

Status_t ForeginCurrencyAccount::Withdraw(const double wit)
{
    Status_t RetStatus = OPERATION_OK;
    if(Balance - wit < 0)
    {
        RetStatus = NO_ANOUGH_CURRENCY;
    }
    else 
    {
        this -> Balance -= wit;
        RetStatus = OPERATION_OK;
    }
    return RetStatus;
} 

Status_t ForeginCurrencyAccount::Capitalise(void)
{
    Status_t RetStatus = CAPITALIZATION_NOT_AVAILABLE;
    return RetStatus;
}