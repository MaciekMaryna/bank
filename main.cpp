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
#define NUMBER_OF_CLEINTS   10
#define MAX_LIMIT_OF_FUNDS  1000000
#define MIN_LEVEL_OF_FUNDS  -1000 //Can be negative in overdraft case

/******************************************************************************
 * Typedefs
 ******************************************************************************/
typedef enum
{
    O_OK,
    NO_ENOUGH_FUNDS,
    MAX_LIMIT_REACHED
} Status_t;

/******************************************************************************
 * Classes
 ******************************************************************************/

/*************** class Person  ***************/
class Person 
{
    private:    
        std::string Forename;
        std::string Surname;
        std::string HomeAddress;
        std::string BirthDate;    
    protected:        
    public:

    std::ostream & operator<<(const Person &, const Person); // Cały czas coś robię źle. Mimo przyjaźni, nie mogę sięgać do pól private. Dlatego obecnie są one w sekcji public
};

/*************** class Account  ***************/
class Account : Person
{
    private:

    protected:        

    public:
        uint32_t IdNum;
        std::string ExpiryDate;        
        Person Owner;
        double Funds;
        Status_t LastOperationStatus;

        Account Deposit(double);
        Account Withdraw(double);
        double Check();
        Account &operator=(const double &);
        Account operator+(const double &);
        Account operator-(const double &);

        friend std::ostream & operator<<(std::ostream &, const Account &);
};

Account Account::Deposit(double dep)
{
    this -> LastOperationStatus = O_OK;
    double FundsAfterOperation = (this -> Funds) + dep;

    if (MAX_LIMIT_OF_FUNDS < FundsAfterOperation)
    {
        this -> LastOperationStatus = MAX_LIMIT_REACHED;
    }
    else 
    {
        this -> Funds = FundsAfterOperation;
        this -> LastOperationStatus = O_OK;
    }
    return *this;
}

Account Account::Withdraw(double wit)
{
    this -> LastOperationStatus = O_OK;
    double FundsAfterOperation = (this -> Funds) - wit;
    if (MIN_LEVEL_OF_FUNDS > FundsAfterOperation)
    {
        this -> LastOperationStatus = NO_ENOUGH_FUNDS;
    }
    else
    {
        this -> Funds = FundsAfterOperation;
        this -> LastOperationStatus = O_OK;
    }
    return *this;
}

double Account::Check()
{
    return this -> Funds;
}

Account &Account::operator=(const double &val)
{
    this -> Funds = val;
    return *this;
}

Account Account::operator+(const double &dep)
{
    return Account::Deposit(dep);
}

Account Account::operator-(const double &wit)
{
    return Account::Withdraw(wit);
}

/******************************************************************************
 * Non class-member functions
 ******************************************************************************/

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

/*******************************************************************************
* Main function
*******************************************************************************/
int main()
{
    Person Clients[NUMBER_OF_CLEINTS];

    Clients[0].Forename = "Mayer";
    Clients[0].Surname = "Jane";
    Clients[0].HomeAddress = "123 Main St, Apt 4B, Springfield, IL 62704";
    Clients[0].BirthDate = "12/12/2002";

    std::cout << Clients[0] << std::endl;

    Account MyAccount;
    MyAccount.IdNum = 1;
    MyAccount.ExpiryDate = "01/01/2025";
    MyAccount.Owner = Clients[0];
    MyAccount.Funds = 0;
    std::cout << MyAccount << std::endl;

    MyAccount.Deposit(200);
    MyAccount.Deposit(100);
    MyAccount.Withdraw(550);
    std::cout << MyAccount << std::endl;

    MyAccount = MyAccount - 2000;
    std::cout << MyAccount << std::endl;

    MyAccount = MyAccount + 1000;
    std::cout << MyAccount << std::endl;

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
*   
*******************************************************************************/