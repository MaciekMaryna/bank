/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"
#include "SavingsAccount.hpp"

/*************** Class SavingsAccount  ***************/
void SavingsAccount::Deposit(const double dep)
{
    this -> Balance += dep;
}

Status_t SavingsAccount::Withdraw(const double wit)
{
    Status_t RetStatus = OPERATION_OK;
    if(Balance - wit < 0)
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

Status_t SavingsAccount::Capitalise(void)
{
    Status_t RetStatus = OPERATION_OK;
    this -> Balance *= (1 + this->InterestRate);
    return RetStatus;
}
