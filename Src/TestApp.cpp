/******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdint.h>
#include <conio.h>
#include "Account.hpp"
#include "CheckingAccount.hpp"
#include "PersonalAccount.hpp"
#include "SavingsAccount.hpp"
#include "ForeginCurrencyAccount.hpp"
#include "TestApp.hpp"

/******************************************************************************
 * Magic number defines
 ******************************************************************************/
#define ESC     27

/******************************************************************************
 * Global variables 
 ******************************************************************************/
uint32_t OperationNumber;
uint64_t Account::NumberOfInctances = 1; //static member of class need to have initialisation out of the class

/*******************************************************************************
* Function: ShowSeparationLine 
*******************************************************************************/
void TestApp::ShowSeparationLine(void)
{
    std::cout << "+-----+----------------------------+------------------+" << std::endl;    
}

/*******************************************************************************
* Function: ShowColumnNames 
********************************************************************************/
void TestApp::ShowColumnNames(void)
{
    ShowSeparationLine();
    std::cout << "| No. | IBAN number                | Balance          |" << std::endl;
    ShowSeparationLine();
}

/*******************************************************************************
* Function: ShowReport 
********************************************************************************/
void TestApp::ShowReport(Account* Tab)
{
    std::cout <<    std::right << "| " <<
                    std::setw(3) << std::setfill(' ') << OperationNumber  << " | " <<
                    std::setw(26) << std::setfill(' ') << Tab -> Get_IBAN() << " | " << 
                    std::setw(12) << std::setfill(' ') << Tab -> Get_Balance()  <<  " " <<
                    std::setw(3) << Tab -> Get_Currency() <<  " | " <<
                    std::endl;
}

/*******************************************************************************
* Function: SetCursorPosition 
********************************************************************************/
void TestApp::SetCursorPosition(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

/*******************************************************************************
* Function: ClearConsole 
********************************************************************************/
void TestApp::ClearConsole()
{
    std::cout << "\033[2J";
}

/*******************************************************************************
* Function: HideCursor 
********************************************************************************/
void TestApp::HideCursor(void)
{
    std::cout << "\033[?25l";
}

/*******************************************************************************
* Function: ShowCursor 
********************************************************************************/
void TestApp::ShowCursor(void)
{
    std::cout << "\033[?25h";
}

/*******************************************************************************
* Function: AsciiIfKeyPressed - non-blocking function
********************************************************************************/
int TestApp::AsciiIfKeyPressed(void)
{
    int ReturnValue = 0;
    if (_kbhit()) 
    { 
        ReturnValue = _getch(); 
    }
    return ReturnValue;
}
/*******************************************************************************
* Function: Run 
********************************************************************************/
void TestApp::TestApp_main(void)
{
    auto StartTimeStamp = std::chrono::high_resolution_clock::now();
    //TestApp::Run();
    auto CurrentTimeStamp = std::chrono::high_resolution_clock::now();
    auto Duration = 0;    
    HideCursor();
    ClearConsole();   
    Run(); 

    bool  DoNotFinish = true;

    do
    {
        CurrentTimeStamp = std::chrono::high_resolution_clock::now();
        Duration = std::chrono::duration_cast<std::chrono::seconds>(CurrentTimeStamp - StartTimeStamp).count();
        SetCursorPosition(0,0);
        std::cout << "Time[h]: " << Duration << "\n";

        switch(AsciiIfKeyPressed())
        {
            case ESC: 
                    DoNotFinish = false;
                    break;
            default: break;
        }

    }
    while(DoNotFinish);
}

/*******************************************************************************
* Function: Run 
********************************************************************************/
void TestApp::Run(void)
{

    ShowColumnNames();

    CheckingAccount MyAccount1;

    PersonalAccount MyAccount2;    
    MyAccount2.Set_OverdraftLimit(1000);        
    MyAccount2.Set_OverdraftInterestRate(0.15);

    SavingsAccount MyAccount3; 

    ForeginCurrencyAccount MyAccount4;   

    // vector<Account*> accounts = {&MyAccount1, &MyAccount2, &MyAccount3};
    // accounts.insert (&MyAccount4);
    
    Account* MyTab[] = {&MyAccount1, &MyAccount2, &MyAccount3, &MyAccount4};
    MyAccount1.Withdraw(0);
    MyTab[0] -> Withdraw(0);
    return;
    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Currency("PL");
        OperationNumber++;        
        ShowReport(MyTab[i]);
    }
    ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Currency("PLN");
        OperationNumber++;
        ShowReport(MyTab[i]);
    }
    ShowSeparationLine();

    MyAccount4.Set_Currency("CHF");
    OperationNumber++;
    ShowReport(&MyAccount4);
    ShowSeparationLine();


    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Set_Balance(1000);
        OperationNumber++;
        ShowReport(MyTab[i]);
    }
    ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Withdraw(1001);    
        OperationNumber++;
        ShowReport(MyTab[i]);        
    }    
    ShowSeparationLine();

    for (int i = 0; i < sizeof(MyTab)/sizeof(MyTab[0]); i++)
    {
        MyTab[i] -> Deposit(300); 
        OperationNumber++;
        ShowReport(MyTab[i]);        
    }    
    ShowSeparationLine();
}
