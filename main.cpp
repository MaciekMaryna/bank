/******************************************************************************
 * C++ Mentoring Playgroud
 ******************************************************************************
 *      Mentor: Tomasz Gujda
 *      Mentee: Maciej Marynowski
 ******************************************************************************/

/******************************************************************************
 * Common includes
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <chrono>

/******************************************************************************
 * Project specific includes
 ******************************************************************************/
#include "Inc\TestApp.hpp"

/******************************************************************************
 * Typedefs
 ******************************************************************************/

/******************************************************************************
 * Global variables
 ******************************************************************************/
std::string DomesticCurrency = "PLN";

/******************************************************************************
 * Classes
 ******************************************************************************/

std::ostream & operator<<(std::ostream & console, const Account &obj)
{
    console << obj.Balance;
    return console;
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
/*
void ShowSeparationLine(void)
{
    std::cout << "+-----+----------------------------+------------------+------------------+--------------------------------+" << std::endl;    
}

void ShowColumnNames(void)
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
*/
/*******************************************************************************
* Main function
*******************************************************************************/
int main()
{

    TestApp_Run();

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
*         (C++11 wprwowadza słówko override, aby z perspektywy klasy dziedziczącej było widać, ze po stronie klasy macieżystej jesy to metoda typu virtual)
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
*    Zadania ze spotkania 18.10.2024:
*       - Dokończyć konfiurację build systemu cmake
*       - Kontynuować zadania z poprzedniego tygodnia
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