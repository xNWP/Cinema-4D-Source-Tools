@ECHO OFF
cls

rmdir /S /Q "X:\C4D\plugins\Cinema 4D Source Tools"
xcopy "res\*.*" /F /S /Y "X:\C4D\plugins\Cinema 4D Source Tools\res\"
copy "Cinema4DSourceTools.cdl64" "X:\C4D\plugins\Cinema 4D Source Tools\"

xcopy "lib\*.dll" "X:\C4D\plugins\Cinema 4D Source Tools\lib\"

echo Pushed.
pause > nul