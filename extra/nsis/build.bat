rmdir /S /Q files

mkdir files

"c:\WINDOWS\microsoft.net\Framework\v4.0.30319\MSBuild.exe" "..\msvc2010\Chaotic Rage.vcxproj"

xcopy /E /I ..\..\data files\data
xcopy /E /I ..\..\maps files\maps
xcopy /E /I ..\..\docs files\docs
xcopy /E /I ..\..\manual files\manual

copy /-Y ..\..\*.bmp files
copy /-Y ..\lib\*.dll files
copy /-Y ..\redist-msvc\*.dll files
copy /-Y ..\..\datatool\lib\*.dll files
copy /-Y ..\redist-msvc\*.manifest files

copy /-Y blank.txt files\stdout.txt
copy /-Y blank.txt files\stderr.txt

copy /-Y ..\..\datatool\bin\Debug\datatool.exe files

copy /-Y ..\msvc2010\Debug\chaoticrage.exe files

"C:\Program Files (x86)\NSIS\makensis.exe" chaoticrage.nsi