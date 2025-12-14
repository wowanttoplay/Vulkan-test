@echo off
REM ============================================================================
REM CMake Automatic Installation Script
REM ============================================================================

echo ========================================
echo CMake Automatic Installation
echo ========================================
echo.

REM Check if CMake is already installed
where cmake >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [INFO] CMake is already installed!
    for /f "tokens=*" %%i in ('cmake --version 2^>^&1 ^| findstr /C:"cmake version"') do (
        echo        %%i
    )
    echo.
    choice /C YN /M "Do you want to reinstall/update CMake"
    if errorlevel 2 goto :end
    echo.
)

echo Downloading CMake installer...
echo.

REM Define CMake version and download URL
REM Using a stable, recent version
set CMAKE_VERSION=3.28.1
set CMAKE_INSTALLER=cmake-%CMAKE_VERSION%-windows-x86_64.msi
set CMAKE_URL=https://github.com/Kitware/CMake/releases/download/v%CMAKE_VERSION%/%CMAKE_INSTALLER%

echo Version: %CMAKE_VERSION%
echo URL: %CMAKE_URL%
echo.

REM Download CMake installer using PowerShell
echo Downloading... (this may take 1-2 minutes)
powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -Uri '%CMAKE_URL%' -OutFile '%TEMP%\%CMAKE_INSTALLER%'}"

if not exist "%TEMP%\%CMAKE_INSTALLER%" (
    echo.
    echo [ERROR] Download failed!
    echo.
    echo Manual installation:
    echo 1. Visit: https://cmake.org/download/
    echo 2. Download "Windows x64 Installer"
    echo 3. Run the installer
    echo 4. Check "Add CMake to PATH for all users"
    echo.
    pause
    exit /b 1
)

echo.
echo [OK] Download complete!
echo.

REM Run installer
echo ========================================
echo Installing CMake...
echo ========================================
echo.
echo IMPORTANT: During installation:
echo   [x] Add CMake to the system PATH for all users
echo.
echo Starting installer in 3 seconds...
timeout /t 3 >nul

echo Running installer...
msiexec /i "%TEMP%\%CMAKE_INSTALLER%" /qb ADD_CMAKE_TO_PATH=System

echo.
echo Waiting for installation to complete...
timeout /t 10 >nul

REM Clean up
echo Cleaning up temporary files...
del "%TEMP%\%CMAKE_INSTALLER%" >nul 2>&1

echo.
echo ========================================
echo Installation Complete!
echo ========================================
echo.

echo IMPORTANT: You must restart your command prompt!
echo.
echo Next steps:
echo   1. CLOSE this command window
echo   2. Open a NEW command prompt
echo   3. Run: cmake --version
echo   4. If successful, run: build_project.bat
echo.

:end
pause
