@echo off
call clean.bat
if %ERRORLEVEL% NEQ 0 (
    echo Clean error: %ERRORLEVEL%
    timeout /t 2
)

call build.bat
if %ERRORLEVEL% NEQ 0 (
    echo Build error: %ERRORLEVEL%
    echo Check also build.log and error.log
    exit
) else (
echo     _  _  _  _      _           _                     _
echo   _^(_^)^(_^)^(_^)^(_^)_   ^(_^)       _ ^(_^)                   ^(_^)
echo  ^(_^)          ^(_^)  ^(_^)    _ ^(_^)                      ^(_^)
echo  ^(_^)          ^(_^)  ^(_^) _ ^(_^)                         ^(_^)
echo  ^(_^)          ^(_^)  ^(_^)^(_^) _                          ^(_^)
echo  ^(_^)          ^(_^)  ^(_^)   ^(_^) _
echo  ^(_^)_  _  _  _^(_^)  ^(_^)      ^(_^) _                     _
echo    ^(_^)^(_^)^(_^)^(_^)    ^(_^)         ^(_^)                   ^(_^)
rem timeout /t 2
main.exe 1> output.log
)

