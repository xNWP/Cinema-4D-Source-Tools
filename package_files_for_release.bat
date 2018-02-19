@ECHO OFF
CLS

SET BuildDir="Build\x64_Release"
SET Package="Cinema 4D Source Tools"
SET ArchName="C4D_Source_Tools-major_minor-tag"

ECHO Moving files to build directory.

MKDIR %BuildDir%\%Package%
XCOPY res %BuildDir%\%Package%\res /I /S /E /W
XCOPY lib\*.dll %BuildDir%\%Package%\lib /I
XCOPY Package\*.* %BuildDir% /I
MOVE %BuildDir%\*.cdl64 %BuildDir%\%Package%

CD %BuildDir%

7z a -tzip %ArchName%.zip *.* %Package%
MOVE %ArchName%.zip ..\..\%ArchName%.zip
7z a -t7z %ArchName%.7z *.* %Package%
MOVE %ArchName%.7z ..\..\%ArchName%.7z

ECHO.
ECHO Packaged.
PAUSE > NUL