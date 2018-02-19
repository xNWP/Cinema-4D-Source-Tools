@ECHO OFF
CLS

SET RDIR="Build\x64_Release"

ECHO About to delete every file in release folder, press any key to continue.
PAUSE > nul

RMDIR /S /Q %RDIR%
MKDIR %RDIR%

ECHO Done.
PAUSE > nul