@echo off
set location=C:\Z0302
cd %location%
set folderName=\TXT
md %folderName%
robocopy %location% %location%\%folderName% *.txt /MOV
pause