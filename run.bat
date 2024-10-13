rem @echo off
rem call clean.bat
rem if %ERRORLEVEL% NEQ 0 (
rem     echo Clean error: %ERRORLEVEL%
rem     timeout /t 2
rem )
rem 
rem call build.bat
rem if %ERRORLEVEL% NEQ 0 (
rem     echo Build error: %ERRORLEVEL%
rem     echo Check also build.log and error.log
rem     exit
rem ) else (
rem echo     _  _  _  _      _           _                     _
rem echo   _^(_^)^(_^)^(_^)^(_^)_   ^(_^)       _ ^(_^)                   ^(_^)
rem echo  ^(_^)          ^(_^)  ^(_^)    _ ^(_^)                      ^(_^)
rem echo  ^(_^)          ^(_^)  ^(_^) _ ^(_^)                         ^(_^)
rem echo  ^(_^)          ^(_^)  ^(_^)^(_^) _                          ^(_^)
rem echo  ^(_^)          ^(_^)  ^(_^)   ^(_^) _
rem echo  ^(_^)_  _  _  _^(_^)  ^(_^)      ^(_^) _                     _
rem echo    ^(_^)^(_^)^(_^)^(_^)    ^(_^)         ^(_^)                   ^(_^)
rem rem timeout /t 2
rem main.exe 1> output.log
rem )

.\build\BankServer.exe
