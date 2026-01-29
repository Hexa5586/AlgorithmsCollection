@ECHO OFF
SETLOCAL EnableDelayedExpansion

:: Define ANSI Escape Characters for colors
FOR /F %%A IN ('echo prompt $E ^| cmd') DO SET "ESC=%%A"
SET "C_RESET=%ESC%[0m"
SET "C_BOLD=%ESC%[1m"
SET "C_RED=%ESC%[91m"
SET "C_GREEN=%ESC%[92m"
SET "C_YELLOW=%ESC%[93m"
SET "C_CYAN=%ESC%[96m"
SET "C_GRAY=%ESC%[90m"

:: Setup Build Directory
IF NOT EXIST build MKDIR build
CD build

:: CMake Configuration & Build
ECHO %C_GRAY%[1/2] Configuring CMake...%C_RESET%
cmake .. > nul
IF %ERRORLEVEL% NEQ 0 (
    ECHO %C_RED%[ERROR] CMake configuration failed. Check your CMakeLists.txt.%C_RESET%
    PAUSE
    GOTO QUIT
) 

ECHO %C_GRAY%[2/2] Building project...%C_RESET%
cmake --build . --config Release --parallel 4
IF %ERRORLEVEL% NEQ 0 (
    ECHO %C_RED%[ERROR] Build failed. Fix syntax errors and try again.%C_RESET%
    PAUSE
    GOTO QUIT
) 

:: UI Header
CLS
ECHO %C_CYAN%=============================================================%C_RESET%
ECHO %C_BOLD%%C_GREEN%   ALGORITHMS TESTING PLAYGROUND - HOSHI-INORI'S COLLECTION   %C_RESET%
ECHO %C_CYAN%=============================================================%C_RESET%
ECHO %C_GRAY% (Type 'Q' to exit, 'CLS' to clear screen)%C_RESET%
ECHO. 

:INPUT
SET "PROB_ID="
SET /p PROB_ID="%C_YELLOW%>> ENTER SOLUTION NAME (or 'LIST'): %C_RESET%"

IF "%PROB_ID%"=="" GOTO INPUT
IF /I "%PROB_ID%"=="Q" GOTO QUIT

:: Handle Empty Input or Exit
IF "%PROB_ID%"=="" GOTO INPUT
IF /I "%PROB_ID%"=="Q" GOTO QUIT
IF /I "%PROB_ID%"=="CLS" (
    CLS
    GOTO :INPUT
)

:: Locate and Execute
:: Checking both root build and Debug/Release subfolders for compatibility
SET "EXE_PATH="
IF EXIST "TestAlgorithms.exe" (SET "EXE_PATH=TestAlgorithms.exe")
IF EXIST "Release\TestAlgorithms.exe" (SET "EXE_PATH=Release\TestAlgorithms.exe")
IF EXIST "Debug\TestAlgorithms.exe" (SET "EXE_PATH=Debug\TestAlgorithms.exe")

:: Logic to handle the list command
IF /I "%PROB_ID%"=="LIST" (
    ECHO %C_CYAN%-------------------------------------------------------------%C_RESET%
    %EXE_PATH% --list
    ECHO %C_CYAN%-------------------------------------------------------------%C_RESET%
    GOTO INPUT
)

IF DEFINED EXE_PATH (
    ECHO %C_GRAY%Running %PROB_ID%...%C_RESET%
    ECHO %C_CYAN%-------------------------------------------------------------%C_RESET%
    %EXE_PATH% %PROB_ID%
    SET "RUN_STATUS=%ERRORLEVEL%"
    ECHO %C_CYAN%-------------------------------------------------------------%C_RESET%
    IF !RUN_STATUS! NEQ 0 (
        ECHO %C_RED%[PROCESS EXIT WITH CODE !RUN_STATUS!]%C_RESET%
    ) ELSE (
        ECHO %C_GREEN%[SUCCESS]%C_RESET%
    )
) ELSE (
    ECHO %C_RED%[ERROR] Executable 'TestAlgorithms.exe' not found.%C_RESET%
)

ECHO.
GOTO INPUT

:QUIT
ECHO %C_GRAY%Terminating playground...%C_RESET%
CD ..