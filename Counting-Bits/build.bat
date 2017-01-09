@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64     
rem call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat"
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:Counting-Bits.exe
cl.exe %compilerflags% Counting-Bits.cpp /link %linkerflags%