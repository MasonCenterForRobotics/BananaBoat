@echo off
setlocal

REM === CONFIG ===
set WORKDIR=%USERPROFILE%\Downloads
set PYTHON=python
set FILE=pc_drive.py
set URL=https://raw.githubusercontent.com/MasonCenterForRobotics/BananaBoat/refs/heads/main/pc_drive.py

REM === GO TO WORK DIR ===
cd /d "%WORKDIR%"

REM === DOWNLOAD FILE ===
echo Downloading %FILE%...
curl -L -o %FILE% %URL%

IF ERRORLEVEL 1 (
    echo Download failed.
    pause
    exit /b
)

REM === RUN SCRIPT ===
echo Starting robot control...
%PYTHON% %FILE%

pause

