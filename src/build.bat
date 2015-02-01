@echo on

call vcvars32
call localvars

cd msvcproject\libaducid
msbuild libaducid.sln /p:Configuration=Release /t:rebuild /p:IncludePath="%INCLUDE%"

