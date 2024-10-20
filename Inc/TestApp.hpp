#ifndef TESTAPP_H
#define TESTAPP_H

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"

uint64_t Account::NumberOfInctances = 1; //static member of class need to have initialisation out of the class

void TestApp_ShowSeparationLine(void);
void TestApp_ShowColumnNames(void);
void TestApp_ShowLastOperationReport(Account* Tab);
void TestApp_Run(void);

#endif /* #ifndef TESTAPP_H */