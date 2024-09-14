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
typedef enum 
{
    PLN = 0,
    EUR,
    USD,
    CHF,
    RUB,
    RUP,
    SEK,
    HOK,
    HUF
} Currencies_t;
/******************************************************************************
 * Classes
 ******************************************************************************/
/*********** Class Accout (base class) ***********/
class Account
{
    private:
    protected:
    public:
        uint64_t IBAN;
        Currencies_t DomesticCurrency;
        double Balance;
        void Deposit(const double);
        void Withdraw(const double); 
        double GetBalance(void);
        void operator+=(double);
        void operator-=(double);
        friend std::ostream & operator<<(std::ostream & console, const Account &obj) // *** dlaczego nie mogę definicji wynieść poza klasę?
        {
            console << obj.Balance;
            return console;
        }

        Account()
        {
            this->IBAN = (uint64_t)0;
            this->DomesticCurrency = PLN;
            this->Balance = (double)0;            
        }

        Account(uint64_t iban, double bal): IBAN(iban), Balance(bal)
        {
            this->IBAN = (uint64_t)0;
            this->DomesticCurrency = PLN;
            this->Balance = (double)0;            
        }
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

void Account::operator+=(double dep)
{
    this->Balance += dep;
}

void Account::operator-=(double wit)
{
    this->Balance -= wit;
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
        void CapitaliseIterest(void);
};

void SavingsAccount::CapitaliseIterest(void)
{
    this->Balance *= (1 + this->InterestRate);
}

/*********** Class ForeginCurrencyAccout  ***********/
class ForeginCurrencyAccout : public Account
{
    private:
    protected:
    public:
        Currencies_t ForreignCurrency;
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
    CheckingAccout MyAccount1;
    MyAccount1 += 1000;
    MyAccount1 -= 5;
    std::cout<<"Balance: "<< MyAccount1 <<std::endl;

    PersonalAccount MyAccount2;
    MyAccount2.OverdraftInterestRate = 5.0/100;
    MyAccount2 += 2000;
    MyAccount2 -= 3000;
    MyAccount2.PayOverdraftInterest();
    std::cout<<"Balance: "<< MyAccount2 <<std::endl;

    SavingsAccount MyAccount3;
    MyAccount3.InterestRate = 2.0/100;
    MyAccount3 -= 100;
    MyAccount3.CapitaliseIterest();
    std::cout<<"Balance: "<< MyAccount3 <<std::endl;

    MyAccount3 += 5000;
    MyAccount3 -= 1000;
    std::cout<<"Balance: "<< MyAccount3 <<std::endl;

    // vector<Account*> accounts = {&MyAccount1, &MyAccount2, &MyAccount3};
    // accounts.insert (&MyAccount4);
    
    Account* myTab[] = {&MyAccount1, &MyAccount2, &MyAccount3}; //Jak hurtowo zwiększyć balans

    for (int i = 0; i < sizeof(myTab)/sizeof(myTab[0]); i++)
    {
        myTab[i] -> Balance += 3;
        std::cout<<"Balance: "<< myTab[i] -> Balance <<std::endl;
    }

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
*   Zadania ze spotkania 13.09.2024  
*       - diagram klas uml
*       - Jak hurtowo zwiększyć balans  
*       - Generyczne (hurtowe) podejście do obiektów
*       - Powtórzenie przeładowań
*
*   1. Czy możliwa i sensowna jest sytuacja kiedy klasa posiada dwa konstruktory inicjujące.
*      Pierwszy, który inicjuje podstawowy set parametrów, a drugi który inicjuje więcej parametrów,
*      ale w taki sposób, ze zawoła ten podstawowy i dodatkowao zainicjuje w swoim ciele jeszcze dodatkowe.
*   2. Czy sensowne jest przerobienie typu enum Currencies_t na prostą klasę?
*   3. Przeładowałem operator+=() i operator-=(). Nie bardzo rozumiem celowość przeciążania operator+() i operator-(). 
*   4. Przeładowałem operator<<, ale są pytania ***
*
*******************************************************************************/