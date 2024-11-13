/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"
#include "CheckingAccount.hpp"
/*************** Class CheckingAccount  ***************/

CheckingAccount::CheckingAccount()
{
    this -> IBAN = Account::IBAN;
}

void CheckingAccount::Deposit(const double dep)
{
    this -> Balance += dep;
}

Status_t CheckingAccount::Capitalise(void)
{
    Status_t RetStatus = CAPITALIZATION_NOT_AVAILABLE;
    return RetStatus;
}

Status_t CheckingAccount::Withdraw(const double wit)
{
    /* std::cout << __PRETTY_FUNCTION__ << std::endl; //verry usefull macro */
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
