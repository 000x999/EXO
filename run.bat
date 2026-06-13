@echo off
setlocal enabledelayedexpansion

set BUILD_DIR=build
set MAIN_EXE=%BUILD_DIR%\EXO.exe
set FOUND_EXAMPLES=0
set EXIT_CODE=0

echo ========= RUNNING EXO =========

if exist "%MAIN_EXE%" (
    echo.
    echo [run_EXO] Running %MAIN_EXE%...
    "%MAIN_EXE%"
    if errorlevel 1 (
        echo [run_EXO] ERROR: %MAIN_EXE% failed.
        set EXIT_CODE=1
    )
) else (
    echo [run_EXO] Main executable not found: %MAIN_EXE%
)

if exist "%BUILD_DIR%\examples" (
    echo.
    echo ========= RUNNING EXAMPLES =========

    for /r "%BUILD_DIR%\examples" %%F in (*.exe) do (
        set FOUND_EXAMPLES=1
        echo.
        echo [run_EXO] Running example: %%F
        "%%F"

        if errorlevel 1 (
            echo [run_EXO] ERROR: Example failed: %%F
            set EXIT_CODE=1
        )
    )
)

echo.
echo ========= CHECKING BUILD ROOT EXECUTABLES =========

for %%F in ("%BUILD_DIR%\*.exe") do (
    if /i not "%%~nxF"=="EXO.exe" (
        set FOUND_EXAMPLES=1
        echo.
        echo [run_EXO] Running build executable: %%F
        "%%F"

        if errorlevel 1 (
            echo [run_EXO] ERROR: Executable failed: %%F
            set EXIT_CODE=1
        )
    )
)

if "%FOUND_EXAMPLES%"=="0" (
    echo [run_EXO] No example executables found.
    echo Expected examples under: %BUILD_DIR%\examples\
)

echo.
if "%EXIT_CODE%"=="0" (
    echo ========= ALL RUNS COMPLETE =========
) else (
    echo ========= SOME RUNS FAILED =========
)

exit /b %EXIT_CODE%
