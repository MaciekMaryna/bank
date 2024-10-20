/******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdint.h>
#include "Account.hpp"
#include "CheckingAccount.hpp"
#include "PersonalAccount.hpp"
#include "SavingsAccount.hpp"
#include "ForeginCurrencyAccount.hpp"

/******************************************************************************
 * Global variables
 ******************************************************************************/
uint32_t OperationNumber;

/*******************************************************************************
* Function: TestApp_ShowSeparationLine 
*******************************************************************************/
void TestApp_ShowSeparationLine(void)
{
    std::cout << "+-----+----------------------------+------------------+------------------+--------------------------------+" << std::endl;    
}

/*******************************************************************************
* Function: TestApp_ShowColumnNames 
********************************************************************************/
void TestApp_ShowColumnNames(void)
{
    TestApp_ShowSeparationLine();
    std::cout << "| No. | IBAN number                | BalaceBefore     | BalanceAfter     | OperStatus                     |" << std::endl;
    TestApp_ShowSeparationLine();
}

/*******************************************************************************
* Function: TestApp_ShowLastOperationReport 
********************************************************************************/
void TestApp_ShowLastOperationReport(Account* Tab)
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
* Function: TestApp_Run 
********************************************************************************/
void TestApp_Run(void)
{
    TestApp_ShowColumnNames();

    CheckingAccount MyAccount1;
    MyAccount1.Set_IBAN(0);

    PersonalAccount MyAccount2;    
    MyAccount2.Set_OverdraftLimit(1000);        
    MyAccount2.Set_OverdraftInterestRate(0.15);

    SavingsAccount MyAccount3; 

    ForeginCurrencyAccount MyAccount4;   

    // vector<Account*> accounts = {&MyAccount1, &MyAccount2, &MyAccount3};
    // accounts.insert (&MyAccount4);
    
    Account* MyTab[] = {&MyAccount1, &MyAccount2, &MyAccount3, &MyAccount4};

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Currency("PL");
        OperationNumber++;        
        TestApp_ShowLastOperationReport(MyTab[i]);
    }
    TestApp_ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Currency("PLN");
        OperationNumber++;
        TestApp_ShowLastOperationReport(MyTab[i]);
    }
    TestApp_ShowSeparationLine();

    MyAccount4.Set_Currency("CHF");
    OperationNumber++;
    TestApp_ShowLastOperationReport(&MyAccount4);
    TestApp_ShowSeparationLine();


    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Balance(1000);
        OperationNumber++;
        TestApp_ShowLastOperationReport(MyTab[i]);
    }
    TestApp_ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Withdraw(1001);    
        OperationNumber++;
        TestApp_ShowLastOperationReport(MyTab[i]);        
    }    
    TestApp_ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Deposit(300); 
        OperationNumber++;
        TestApp_ShowLastOperationReport(MyTab[i]);        
    }    
    TestApp_ShowSeparationLine();
}

