@echo on

call vcvars32
call localvars

REM this is for VS2010
REM cd msvcproject\libaducid
REM msbuild libaducid.sln /p:Configuration=Release /t:rebuild /p:IncludePath="%INCLUDE%"

REM this is for VS 2013 community
cd msvcproject\libaducid
devenv libaducid.sln /rebuild Release


