@ECHO OFF
CLS

SET BuildDir="Build\x64_Release"

ECHO Moving files to build directory.

XCOPY res %BuildDir%\res /I /S /E /W
XCOPY lib\*.dll %BuildDir%\lib /I
XCOPY Package\readme.txt %BuildDir% /I

CD %BuildDir%

SET ArchName="C4D_Source_Tools-major_minor-tag"
7z a -tzip %ArchName%.zip @..\..\7zipfilelist.txt
7z a -t7z %ArchName%.7z @..\..\7zipfilelist.txt

MOVE %ArchName%.7z ..\..\%ArchName%.7z
MOVE %ArchName%.zip ..\..\%ArchName%.zip

ECHO.
ECHO Packaged.
PAUSE > NUL