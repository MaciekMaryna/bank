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

void CheckingAccount::Withdraw(const double wit)
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
