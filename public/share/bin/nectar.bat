@echo off

cls
echo ===================================
echo NCC: Nectar Compiler Collection
echo ===================================

if "%~1"=="" (
    echo nectar: No argument supplied
)

for %%i in (%*) do (
    echo nectar: translating:  %%i.nc.pp
    cpp -P %%i.nc -o %%i.pp.nc
    pef-amd64-necdrv -fuse-nasm %%i.pp.nc
)