#ifndef ACCOUNT_H
#define ACCOUNT_H
/******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <stdint.h>
#include "Account.hpp"

/******************************************************************************
 * Typedefs
 ******************************************************************************/

enum Status_t
{
    OPERATION_OK = 0,
    COMMON_FAULT,
    NO_ANOUGH_FUNDS,
    NO_ANOUGH_DEBIT,
    NO_ANOUGH_CURRENCY,
    CANNOT_SET_SUCH_BALANCE,
    INVALID_CURRENCY_NAME,
    INVALID_IBAN_NUMBER,
    CAPITALIZATION_NOT_AVAILABLE,

    NUMBER_OF_STATUSES
};

/*
std::string ErrorNames[] =
{
    "OPERATION_OK",
    "COMMON_FAULT",
    "NO_ANOUGH_FUNDS",
    "NO_ANOUGH_DEBIT",
    "NO_ANOUGH_CURRENCY",
    "CANNOT_SET_SUCH_BALANCE",
    "INVALID_CURRENCY_NAME",
    "INVALID_IBAN_NUMBER"
};
*/

/*********** Class Account (base class) ***********/
class Account
{
    private:

    protected:
        static uint64_t NumberOfInctances;
        uint64_t IBAN;
        double Balance;
        std::string Currency; // = "---";        //czy wartości początkowe można nadać wyłącznie konstruktorem lub seterem, a nie w ten sposób?
    public:
        void Set_IBAN(const uint64_t);
        uint64_t Get_IBAN(void);
        void Set_Balance(const double);
        double Get_Balance(void);        
        std::string Get_Currency(void);
        void Set_Currency(std::string);        
        virtual void Deposit(const double) = 0;        
        virtual Status_t Withdraw(const double) = 0;  /*std::cout << __PRETTY_FUNCTION__ << std::endl; //verry useful macro*/
        virtual Status_t Capitalise(void) = 0;
        
        void operator+=(const double);
        void operator-=(const double);
        friend std::ostream & operator<<(std::ostream &, const Account &); 
        Account();
        // Account(uint64_t iban, double bal, std::string cur);
};

#endif /* #ifndef ACCOUNT_H */