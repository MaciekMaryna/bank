/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"
#include "CheckingAccount.hpp"
/*************** Class CheckingAccount  ***************/

void CheckingAccount::Withdraw(const double wit)
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
