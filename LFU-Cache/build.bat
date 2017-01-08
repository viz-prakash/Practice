@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64     
rem call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat"
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:LFU-Cache.exe
cl.exe %compilerflags% LFU-Cache.cpp /link %linkerflags%