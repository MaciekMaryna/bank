/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"
#include "SavingsAccount.hpp"

/*************** Class SavingsAccount  ***************/

void SavingsAccount::Withdraw(const double wit)
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

void SavingsAccount::CapitaliseIterest(void)
{
    this -> Balance *= (1 + this->InterestRate);
}
