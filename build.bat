@echo off
cls
make clean
make
rd /s /q Build
echo Press any key...
pause >nul
