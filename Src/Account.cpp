/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"

/*********** Class Account (base class) ***********/
Account::Account() : Balance(0.0), Currency("PLN")
{
    //empty for the moment
    this -> IBAN = NumberOfInctances;
    NumberOfInctances++;
}

void Account::Deposit(const double dep)
{
    this -> Balance += dep;
}

void Account::Set_IBAN(const uint64_t iban)
{
    if (0 == iban)
    {
        //no action
    }
    else
    {
        this -> IBAN = iban;
    }
}

uint64_t Account::Get_IBAN(void)
{
    return this -> IBAN;
}

void Account::Set_Balance(const double bal)
{
    this -> Balance = bal;
}

double Account::Get_Balance(void)
{
    return this -> Balance;
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
        //no action
    }
    else
    {
        this -> Currency = curr;
    }
}

void Account::operator+=(const double dep)
{
    this -> Balance += dep;
}

void Account::operator-=(const double wit)
{
    this -> Balance -= wit;
}