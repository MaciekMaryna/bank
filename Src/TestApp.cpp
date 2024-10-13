#include "../Inc/TestApp.hpp"

/*******************************************************************************
* Function: ShowSeparationLine 
*******************************************************************************/
void ShowSeparationLine(void)
{
    std::cout << "+-----+----------------------------+------------------+------------------+--------------------------------+" << std::endl;    
}

/*******************************************************************************
* Function: ShowColumnsNames 
********************************************************************************/
void ShowColumnsNames(void)
{
    ShowSeparationLine();
    std::cout << "| No. | IBAN number                | BalaceBefore     | BalanceAfter     | OperStatus                     |" << std::endl;
    ShowSeparationLine();
}

/*******************************************************************************
* Function: ShowLastOperationRaport 
********************************************************************************/
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

