#ifndef TESTAPP_H
#define TESTAPP_H

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Account.hpp"

namespace TestApp  /* BEGIN: namespace TestApp */
{

void ShowSeparationLine(void);
void ShowColumnNames(void);
void ShowReport(Account* Tab);
void SetCursorPosition(int, int);
void ClearConsole();
void HideCursor(void);
void ShowCursor(void);
int AsciiIfKeyPressed(void);
void TestApp_main(void);
void Run(void);

#endif /* #ifndef TESTAPP_H */

} /* END: namespace TestApp */