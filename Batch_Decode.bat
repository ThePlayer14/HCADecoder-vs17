@echo off

rem **********************************************************************
rem * Default value Settings                                             *
rem *                                                                    *
rem * Volume (Default volume is 1.0)                                     *
set X_V=1.0
rem *                                                                    *
rem * Bit Depth (8, 16, 24, 32, float)                                   *
set X_M=16
rem *                                                                    *
rem * Number of loops (0 or greater)                                     *
set X_L=0
rem *                                                                    *
rem * Decryption key (Specified by the 16-digit hexadecimal)             *
set X_K = CF222F1FE0748978
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
  echo To decode a single file, please drag and drop a file to HCADecoder.exe
  echo To decode multiple files, please drag and drop the files to Batch_Decode.bat
  pause
  exit /b
)

echo:
set X_I=
echo Do you want to display the file header information?
set /P X_I="Press any key and then enter to display the file header information. To continue decoding just press enter"
if "%X_I%" neq "" (
  echo:
  for %%f in (%*) do "%~dp0HCADecoder.exe" -i %%f
  pause
  exit /b
)

echo:
echo If you do not enter a volume number, it will be output as the default (1.0).
set /P X_V="Volume (Default number is 1.0)"
echo:
echo If you do not enter a bit depth, it will be output as 16-bit PCM.
set /P X_M="Bit Depth (Specify a bit depth of 8, 16, 24, 32, float):"
echo:
echo If you do not enter a loop count, it will be decoded without a loop.
set /P X_L="Number of times looped (0 or greater):"
echo:
echo If you do not enter a decryption key, you can use the key that is used in PSO2.
set /P X_K="Decryption key (Specified by the 16-digit hexadecimal):"
echo:
if "%X_M%" == "float" (set X_M=0)
set X=-v %X_V% -m %X_M% -l %X_L% -a %X_K:~8,8% -b %X_K:~0,8%
for %%f in (%*) do "%~dp0HCADecoder.exe" %X% %%f
echo:
pause
