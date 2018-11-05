echo off

rem **********************************************************************
rem * Default Value Setting                                              *
rem *                                                                    *
rem * Decryption Key (Specified by the 16-digit hexadecimal)             *
set X_K=CF222F1FE0748978
rem *                                                                    *
rem * Decryption Keys                                                    *
rem * CF222F1FE0748978: Default Key                                      *
rem * CC55463930DBE1AB: Phantasy Star Online 2                           *
rem * 0000000077EDF21C: Ro-Kyu-Bu! Himitsu No Otoshimono                 *
rem * 00000000012C9A53: JoJo's Bizarre Adventure All Star Battle         *
rem * 00003657F27E3B22: THE iDOLM@STER Cinderella Girls: Starlight Stage *
rem * 0011DCDD0DC57F48: Grimoire - Private Grimoire Magic Academy        *
rem * 30DBE1ABCC554639: Old Phantasy Star Online 2 Encryption Key        *
rem *                                                                    *
rem **********************************************************************

if "%~1" == "" (
  echo Please close this window.
  echo To decode a single file, please drag and drop a file onto the the HCADecoder.exe
  echo To decode multiple files, please drag and drop the files onto the this .bat file
  pause
  exit /b
)

echo:
echo If you don't specify a decryption key, the key used in PSO2 will be used.
set /P X_K="Decryption key (Specified by the 16-digit hexadecimal):"
echo:
set X=-c -a %X_K:~8,8% -b %X_K:~0,8%
for %%f in (%*) do "%~dp0HCADecoder.exe" %X% %%f
echo:
pause
