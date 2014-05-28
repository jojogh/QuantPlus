for /f "tokens=5" %%i in ('SubWCRev ../../^|find "Last committed at revision"') do set version=%%i 
echo %version%