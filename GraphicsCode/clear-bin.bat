@echo off

cd bin
echo INFO: I am running from '%cd%'

mkdir temp
move conanfile.txt temp
erase *.*
move temp\* .
rmdir temp

pause