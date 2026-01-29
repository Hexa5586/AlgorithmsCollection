@ECHO OFF
SETLOCAL EnableDelayedExpansion

:: 定义 ANSI 转义字符 (ASCII 27)
FOR /F %%A IN ('echo prompt $E ^| cmd') DO SET "ESC=%%A"

:: 定义颜色代码
SET "C_RESET=%ESC%[0m"
SET "C_GRAY=%ESC%[90m"
SET "C_RED=%ESC%[91m"
SET "C_GREEN=%ESC%[92m"
SET "C_YELLOW=%ESC%[93m"
SET "C_CYAN=%ESC%[96m"
SET "C_WHITE=%ESC%[97m"

:: 自动创建 ./build
IF NOT EXIST build (
    MKDIR build
)
CD build

:: CMake 过程
ECHO %C_GRAY%=== CMAKE PROCESS ===
cmake ..
IF %ERRORLEVEL% NEQ 0 (
    ECHO %C_RED%[ERROR] CMake configuration failed.%C_RESET%
    GOTO QUIT
)

cmake --build .
IF %ERRORLEVEL% NEQ 0 (
    ECHO %C_RED%[ERROR] Build failed.%C_RESET%
    GOTO QUIT
)

:: 交互界面
ECHO.
ECHO %C_GREEN%=== ALGORITHMS TESTING PLAYGROUND FOR HOSHI-INORI'S COLLECTION ===%C_RESET%

:INPUT
:: 使用自定义前缀提示颜色
SET /p PROB_ID="%C_YELLOW%ENTER SOLUTION NAME, OR Q TO QUIT: %C_RESET%"

IF /I "%PROB_ID%"=="Q" (
    GOTO QUIT
)

:: 执行程序
IF EXIST TestAlgorithms.exe (
    TestAlgorithms.exe %PROB_ID%
) ELSE (
    ECHO %C_RED%[ERROR] Executable not found.%C_RESET%
)

GOTO INPUT

:QUIT
ECHO %C_GRAY%=== QUITTING PLAYGROUND ===%C_RESET%