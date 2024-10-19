/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"

/*********** Class Account (base class) ***********/
void Account::Deposit(const double dep)
{
    this -> BalanceOld = this -> Balance;
    this -> Balance += dep;
    this -> LastOperStatus = OPERATION_OK;
}

void Account::Set_IBAN(const uint64_t iban)
{
    if (0 != iban)
    {
        this -> IBAN = iban;
        this -> LastOperStatus = OPERATION_OK;
    }
    else
    {
        this -> LastOperStatus = INVALID_IBAN_NUMBER;       
    }
}

uint64_t Account::Get_IBAN(void)
{
    return this -> IBAN;
}

void Account::Set_Balance(const double bal)
{
    this -> BalanceOld = this -> Balance;
    this -> Balance = bal;
}

double Account::Get_Balance(void)
{
    return this -> Balance;
}

double Account::Get_BalanceOld(void)
{
    return this -> BalanceOld;
}

std::string Account::Get_Currency(void)
{
    std::string result;
    if (3 != this -> Currency.length())
    {
        result = "---\0";
    }
    else
    {
        result = this -> Currency;
    }
    return result;
}

void Account::Set_Currency(std::string curr)
{
    if (3 != curr.length())
    {
        this -> LastOperStatus = INVALID_CURRENCY_NAME;
    }
    else
    {
        this -> Currency = curr;
        this -> LastOperStatus = OPERATION_OK;
    }
}

Status_t Account::Get_LastOperStatus(void)
{
    return this -> LastOperStatus;
}

void Account::operator+=(const double dep)
{
    this -> BalanceOld = this -> Balance;
    this -> Balance += dep;
}

void Account::operator-=(const double wit)
{
    this -> BalanceOld = this -> Balance;
    this -> Balance -= wit;
}