@echo off
setlocal

REM === CONFIG ===
set WORKDIR=%USERPROFILE%\Downloads
set PYTHON=python
set FILE=pc_drive.py
set URL=https://github.com/MasonCenterForRobotics/BananaBoat/blob/Robotic-Raptors/pc_drive.py

REM === CHECK PYTHON ===
where %PYTHON% >nul 2>nul
IF ERRORLEVEL 1 (
    echo Python not found in PATH.
    pause
    exit /b
)

REM === GO TO WORK DIR ===
cd /d "%WORKDIR%"

REM === CHECK IF FILE EXISTS ===
IF EXIST "%FILE%" (
    echo %FILE% already exists. Skipping download.
) ELSE (
    echo %FILE% not found. Downloading...
    curl -L -o "%FILE%" "%URL%"
    IF ERRORLEVEL 1 (
        echo Download failed.
        pause
        exit /b
    )
)

REM === CHECK / INSTALL PYSERIAL ===
%PYTHON% -m pip show pyserial >nul 2>nul
IF ERRORLEVEL 1 (
    echo Installing pyserial...
    %PYTHON% -m pip install pyserial
)

REM === RUN SCRIPT ===
echo Starting robot control...
%PYTHON% "%FILE%"

pause

