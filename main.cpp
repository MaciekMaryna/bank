/******************************************************************************
 * C++ Mentoring Playgroud
 ******************************************************************************
 *      Mentor: Tomasz Gujda
 *      Mentee: Maciej Marynowski
 ******************************************************************************/

#include <iostream>
#include <chrono>
//#include <string>
#include <stdint.h>

/******************************************************************************
 * Defines and macros
 ******************************************************************************/

/******************************************************************************
 * Typedefs
 ******************************************************************************/

/******************************************************************************
 * Classes
 ******************************************************************************/
/*********** Class Accout (abstract class) ***********/
class Account
{
    private:
    protected:
    public:
        uint64_t IBAN;
        char DomesticCurrency[3];
        double Balance;
        void Deposit(const double);
        void Withdraw(const double); 
        double GetBalance(void);
        void operator=(const double);
        void operator+(const double);
        void operator-(const double);
};

void Account::Deposit(const double dep)
{
    this -> Balance += dep;
}

void Account::Withdraw(const double wit)
{
        this -> Balance -= wit;
}

double Account::GetBalance(void)
{
    return this->Balance;
}

void Account::operator=(const double val)
{
    this -> Balance = val;
}

void Account::operator+(const double dep)
{
    Account::Deposit(dep);
}

void Account::operator-(const double wit)
{
    Account::Withdraw(wit);
}

/*************** Class CheckingAccout  ***************/
class CheckingAccout : public Account
{
    private:
    protected:
    public:
};

/*********** Class PersonaAccount (debit) ************/
class PersonalAccount : public Account
{
    private:
    protected:
    public:
        double OverdraftLimit; // should be a positive number
        float OverdraftInterestRate;
        void PayOverdraftInterest(void);
};

void PersonalAccount::PayOverdraftInterest(void)
{
    if (this->Balance < 0)
    {
        this->Balance *= (1 + this->OverdraftInterestRate);
    }
}


/*************** Class SavingsAccout  ***************/
class SavingsAccount : public Account
{
    private:
    protected:
    public:
        float InterestRate;
        void CapitaliesIterest(void);
};

void SavingsAccount::CapitaliesIterest(void)
{
    this->Balance *= (1 + this->InterestRate);
}

/*********** Class ForeginCurrencyAccout  ***********/
class ForeginCurrencyAccout : public Account
{
    private:
    protected:
    public:
        char ForreignCurrency[3];
};



/******************************************************************************
 * Non class-member functions
 ******************************************************************************/
/*
std::ostream & operator<<(std::ostream & Os, const Person & Prs) 
{
    Os  << std::endl << "\t\tFORENAME:     " << Prs.Forename
        << std::endl << "\t\tSURNAME:    " << Prs.Surname 
        << std::endl << "\t\tHOME ADDRESS : " << Prs.HomeAddress
        << std::endl << "\t\tBIRTH DATE :   " << Prs.BirthDate;
    return Os;
}

std::ostream & operator<<(std::ostream & Os, const Account & Acc)
{
        Os  << std::endl 
        << std::endl << "ID NUMBER:        " << Acc.IdNum 
        << std::endl << "DATE OF EXPIRY:   " << Acc.ExpiryDate 
        << std::endl << "FUNDS :           " << Acc.Funds
        << std::endl << "LAST OP. STATUS : " << Acc.LastOperationStatus       
        << std::endl << "OWNER :           " << Acc.Owner;
    return Os;
}
*/
/*******************************************************************************
* Main function
*******************************************************************************/
int main()
{
    /*
    TOTO
    Przeciążyć GetBalance tak żeby zwracało watość 
    Przeciążyć +
    Przciążyć - 
    */
    CheckingAccout MyAccount1;
    MyAccount1.Deposit(1000);
    MyAccount1.Withdraw(5);
    std::cout<<"Balance: "<< MyAccount1.GetBalance()<<std::endl;

    PersonalAccount MyAccount2;
    MyAccount2.OverdraftInterestRate = 5.0/100;
    MyAccount2.Deposit(2000);
    MyAccount2.Withdraw(3000);
    MyAccount2.PayOverdraftInterest();
    std::cout<<"Balance: "<< MyAccount2.GetBalance()<<std::endl;

    SavingsAccount MyAccount3;
    MyAccount3.InterestRate = 2.0/100;
    MyAccount3.Deposit(100);
    MyAccount3.CapitaliesIterest();
    std::cout<<"Balance: "<< MyAccount3.GetBalance()<<std::endl;
    return 0;
}

/*******************************************************************************
*   Zadanie: Serwer bankowy
*   Mozna zaczac od klasy konto i operacji deposit/withdraw (oprocz dedykowanych funckji mozna tez przeladowac operatory +/-)
*
*   Pytania:
*   - czy do rozmiarów tablic stosować #define czy constexpr?
*   - czy jeśli klasa ma tylko tylko publiczne elementy i żadnych metod to nadal trzymać ją jako klasę czy zrobić z tego strukturę
*   - nie rozwiązana zagadka friend. To chyba nie jest problem z namespace tylko właśnie z przyjaźnią.
*   - czy istnieje coś takiego jak referencja do funkcji? To przecież też jest jakiś obiekt.
*
*   Zadania ze spotkania 16.08.2024
*       - Praca z kodem: posprzątać, zbudować hierarchię dziedziczenia klasy Account
*       - Praca z kodem: przeładowanie operator+() i operator-() - dodaj do rachunku i odejmij do rachunku
*       - Literatura: doczytać Virtual Function in C++
*       - Literatura: powtórzyć przeładowanie funkcji
*
*   Zadania ze spotkania 23.08.2024
*       - Literatura: warto powtórnie przestudiować wirtualizm - niezwykle istotny mechanizm
*       - Literatura: powtórzyć przeładowanie funkcji (zaległe z poprzedniego spotkania)
*       - Praca z kodem: oba zadania z poprzedniego spotkania
*  


*******************************************************************************/