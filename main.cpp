/******************************************************************************
 * C++ Mentoring Playgroud
 ******************************************************************************
 *      Mentor: Tomasz Gujda
 *      Mentee: Maciej Marynowski
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdint.h>

/******************************************************************************
 * Defines and macros
 ******************************************************************************/


/******************************************************************************
 * Typedefs
 ******************************************************************************/
/*
enum 
{
    PLN = 0,
    EUR,
    USD,
    CHF,
    RUB,
    RUP,
    SEK,
    HOK,
    HUF,
    NUMBER_OF_CURRENCIES
};
*/

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

    NUMBER_OF_STATUSES
};

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

/******************************************************************************
 * Global variables
 ******************************************************************************/
uint32_t OperationNumber;
std::string DomesticCurrency = "PLN";

/******************************************************************************
 * Classes
 ******************************************************************************/
/*********** Class Accout (base class) ***********/
class Account
{
    private:

    protected:
        uint64_t IBAN;
        double Balance;
        double BalanceOld = 0;   
        Status_t LastOperStatus = OPERATION_OK;        
        std::string Currency = "---";        //czy wartości początkowe można nadać wyłącznie konstruktorem lub seterem, a nie w ten sposób?
    public:
        void Set_IBAN(const uint64_t);
        uint64_t Get_IBAN(void);
        void Set_Balance(const double);
        double Get_Balance(void);        
        double Get_BalanceOld(void);
        Status_t Get_LastOperStatus(void);
        std::string Get_Currency(void);
        void Set_Currency(std::string);        
        void Deposit(const double);        
        virtual void Withdraw(const double) = 0;         
        void operator+=(const double);
        void operator-=(const double);
        friend std::ostream & operator<<(std::ostream &, const Account &); 
        Account()
        {
            this -> IBAN = (uint64_t)0;
            this -> Currency = DomesticCurrency;
            this -> Balance = (double)0;            
        }

        Account(uint64_t iban, double bal, std::string cur)
        {
            this -> IBAN = iban;
            this -> Currency = cur;
            this -> Balance = bal;            
        }
};

std::ostream & operator<<(std::ostream & console, const Account &obj)
{
    console << obj.Balance;
    return console;
}

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

/*************** Class CheckingAccout  ***************/
class CheckingAccout : public Account
{
    private:
    protected:
    public:
        void PayOverdraftInterest(void);    
        void Withdraw(const double) override;      
};

void CheckingAccout::Withdraw(const double wit)
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

/*********** Class PersonalAccount (debit) ************/
class PersonalAccount : public Account
{
    private:
    protected:
    public:
        double OverdraftLimit; // should be a positive number
        float OverdraftInterestRate;
        void PayOverdraftInterest(void);
        void Withdraw(const double) override;
};

void PersonalAccount::Withdraw(const double wit)
{
    if(Balance - wit < (-OverdraftLimit))
    {
        this -> LastOperStatus = NO_ANOUGH_DEBIT;        
    }
    else 
    {
        this -> BalanceOld = this -> Balance;
        this -> Balance -= wit;
        this -> LastOperStatus = OPERATION_OK; 
    }
} 

void PersonalAccount::PayOverdraftInterest(void)
{
    if (this->Balance < 0)
    {
        this -> BalanceOld = this -> Balance;
        this -> Balance *= (1 + this->OverdraftInterestRate);
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
        void Withdraw(const double) override;           
};

void SavingsAccount::Withdraw(const double wit)
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

void SavingsAccount::CapitaliseIterest(void)
{
    this -> BalanceOld = this -> Balance;
    this -> Balance *= (1 + this->InterestRate);
}

/*********** Class ForeginCurrencyAccout  ***********/
class ForeginCurrencyAccout : public Account
{
    private:
    protected:
    public:
        void Withdraw(const double) override;               
};

void ForeginCurrencyAccout::Withdraw(const double wit)
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
/*******************************************************************************
* Common non class-member functions
*******************************************************************************/
void ShowSeparationLine(void)
{
    std::cout << "+-----+----------------------------+------------------+------------------+--------------------------------+" << std::endl;    
}

void ShowColumnsNames(void)
{
    ShowSeparationLine();
    std::cout << "| No. | IBAN number                | BalaceBefore     | BalanceAfter     | OperStatus                     |" << std::endl;
    ShowSeparationLine();
}

void ShowLastOperationRaport(Account* Tab)
{
    std::cout <<    std::right << "| " <<
                    std::setw(3) << std::setfill('0') << OperationNumber  << " | " <<
                    std::setw(26) << std::setfill(' ') << Tab -> Get_IBAN() << " | " << 
                    std::setw(12) << std::setfill(' ') << Tab -> Get_BalanceOld() << " " << 
                    std::setw(3) << Tab -> Get_Currency() <<  " | " <<
                    std::setw(12) << std::setfill(' ') << Tab -> Get_Balance()  <<  " " <<
                    std::setw(3) << Tab -> Get_Currency() <<  " | " <<
                    std::left << 
                    std::setw(30) << std::setfill(' ') << ErrorNames[Tab -> Get_LastOperStatus()]  <<  " | " <<
                    std::endl;
}
/*******************************************************************************
* Main function
*******************************************************************************/
int main()
{

    ShowColumnsNames();
    CheckingAccout MyAccount1;
    MyAccount1.Set_IBAN(0);
    PersonalAccount MyAccount2;    
    SavingsAccount MyAccount3; 
    ForeginCurrencyAccout MyAccount4;   

    MyAccount2.OverdraftLimit = 1000;    

    // vector<Account*> accounts = {&MyAccount1, &MyAccount2, &MyAccount3};
    // accounts.insert (&MyAccount4);
    
    Account* MyTab[] = {&MyAccount1, &MyAccount2, &MyAccount3, &MyAccount4};

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Currency("PL");
        OperationNumber++;        
        ShowLastOperationRaport(MyTab[i]);
    }
    ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Currency("PLN");
        OperationNumber++;
        ShowLastOperationRaport(MyTab[i]);
    }
    ShowSeparationLine();

    MyAccount4.Set_Currency("CHF");
    OperationNumber++;
    ShowLastOperationRaport(&MyAccount4);
    ShowSeparationLine();


    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Balance(1000);
        OperationNumber++;
        ShowLastOperationRaport(MyTab[i]);
    }
    ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Withdraw(1001);    
        OperationNumber++;
        ShowLastOperationRaport(MyTab[i]);        
    }    
    ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Deposit(300); 
        OperationNumber++;
        ShowLastOperationRaport(MyTab[i]);        
    }    
    ShowSeparationLine();

/*
    for (Account *acc:MyTab)
    {
        acc-> Balance += 3;
        std::cout<<"Balance: "<< acc -> Balance <<std::endl;     
    }
*/
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
*   Zadania ze spotkania 20.09.2024  
*       - Strzałki w diagramach klas UML a rodzaje relacji. Przyjrzeć się innym typom strzałek. Jakie typy relacji one reprezentują.
*       - Zaimplementować przeładowanie operatorów "+" i "+=". Będą podobne do siebie. Czy można je jakoś uwspólnić
*       - Nadpisywanie funkcji Withdraw() - przyjrzeć się. Która się wywoła, przy dostępie "hurtowym"? 
*
*   Pytania:
*       - Są 4 klasy, które powinny dostarczyć implementrację funkcji Withdraw(). Jaka jest praktyka odnośnie miejsca gdzie umieszcza się 
*           indywidualną wersję? Wszystkie abstrakcyjne wersje w jednym miejscu - np. tuż po klasie abstrakcyjnej? Czy może rozrzucone 
*           po klasach szczegółowych - ja umieściłem je tuż po definicji klasy jako zawsze pierwszą implementowaną metodę danej klasy. Odp: Nie, za to podział na pliki (plik per klasa)
*       - po co jest ""=0" Odp: oznacza, że klasa bazowa nie posiada implementacji danej metody, za to każdy potomek musi ją dostarczyć
         (C++11 wprwowadza słówko override, aby z perspektywy klasy dziedziczącej było widać, ze po stronie klasy macieżystej jesy to metoda typu virtual)
*   
*   Zadania ze spotkania 04.10.2024:
*       - podzielić na pliki
*       - Przygotować dla treningu inne metody które wymagają wirtualizmu (Balance też virtual, może kapitalizacja)  
*       - Enkapsulacja get/set schować pola jako prywatne lub protected i przygotować dla nich get-ery y set-ery
*       - Zaimplementować przeładowanie operatorów "+" i "+=". Będą podobne do siebie. Czy można je jakoś uwspólnić? (zaległość z poprzedniego soptkania)
* 
*    Pomysły 
*       - status operacji, stan przed i stan po - dużo kodu nadmiarowego
*       - w takim podejściu getery nie mogą zwracać statusu
*       - temat waluty jest źle wymyślony z logicznego punktu widzenia. 
*       
*   Zadania ze spotkania 11.10.2024:
*       - Wyprostować build system: spróbować cmake, ale w przypadku trudności można wrócić do skryptów batch-owych
*       - Waluta jest cechą konta nadaną przy konstrowaniu - nie kombinujemy.  
*       - LastBalance, jako pole przechowywane w koncie nie jest dobrym pomysłem. Lepiej zbudować jakiś
*         mechanizm (np. kolejkę) historycznych operacji na koncie i z każdą nową operacją dodawać rekord 
*         do tej struktury danych. Dlatego wycofujemy się z pomysłu LastOperation, 
*         który de facto od początku był zły i sztuczny. 
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*******************************************************************************/