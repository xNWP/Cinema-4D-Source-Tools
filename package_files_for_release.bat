@ECHO OFF
CLS

SET BuildDir="Build\x64_Release"
SET Package="Cinema 4D Source Tools"
ECHO Moving files to build directory.

MKDIR %BuildDir%\%Package%
XCOPY res %BuildDir%\%Package%\res /I /S /E /W
XCOPY lib\*.dll %BuildDir%\%Package%\lib /I
XCOPY Package\readme.txt %BuildDir%\%Package%\ /I
MOVE %BuildDir%\*.cdl64 %BuildDir%\%Package%

CD %BuildDir%

SET ArchName="C4D_Source_Tools-major_minor-tag"
7z a -tzip %ArchName%.zip %Package%
7z a -t7z %ArchName%.7z %Package%

MOVE %ArchName%.7z ..\..\%ArchName%.7z
MOVE %ArchName%.zip ..\..\%ArchName%.zip

ECHO.
ECHO Packaged.
PAUSE > NUL