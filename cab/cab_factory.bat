@echo off
:: Path subject to modifications
:: Author: MikeTangoEcho
:: Function: Generate CAB file to distribute webrtc-everywhere trough codebase
:: Date: 2015/15/08
:: Version: 0.5
:: HOWTO-
:: Replace variable keyname/keypass with the name and pass of the PFX file
SETLOCAL
set winsdk="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Bin\"
set win32="C:\Windows\System32\"
set lib_folder="..\webrtc-everywhere\"
set cab_folder=webrtc-dll
set cab_ddt=cab_result
set cab_filename=webrtc-everywhere
:: Key
set keyname=fake
set keypass=pfxfake
set keytimestamp=/tr http://www.startssl.com/timestamp

:: Main
IF "%1%" == "gencrt" GOTO GENCRT
IF "%1%" == "genpfx" GOTO GENPFX
IF "%1%" == "gencab" GOTO GENCAB
IF "%1%" == "sigcab" GOTO SIGCAB
IF "%1%" == "sigdll" GOTO SIGDLL
IF "%1%" == "sigchk" GOTO SIGCHK
IF "%1%" == "source" (
 copy /Y %lib_folder%"\Release\webrtc-everywhere-ie.dll"			%cab_folder%"\webrtc-everywhere-ie.dll"
 copy /Y %lib_folder%"\Release\webrtc-everywhere-common.dll"		%cab_folder%"\webrtc-everywhere-common.dll"
 copy /Y %lib_folder%"\Release\webrtc-sharepermissions-ie.dll"		%cab_folder%"\webrtc-sharepermissions-ie.dll"
 copy /Y %lib_folder%"\x64\Release\webrtc-everywhere-ie.dll" 		%cab_folder%"\x64\webrtc-everywhere-ie.dll"
 copy /Y %lib_folder%"\x64\Release\webrtc-everywhere-common.dll"	%cab_folder%"\x64\webrtc-everywhere-common.dll"
)
GOTO EOF

:GENKEY
:: Create Root Privater Key and Ceriticate
%winsdk%makecert -r -pe -n "CN=Fake ROOT" -ss CA -sr CurrentUser -a sha256 -len 2048 -cy authority -sky signature -sv %keyname%_root.pvk %keyname%_root.cer
certutil -user -addStore Root %keyname%_root.cer
:: Create Ceriticate for Object Signing
%winsdk%makecert -pe -n "CN=Instadeo SPC" -a sha256 -cy end -sky signature -ic %keyname%_root.cer -iv %keyname%_root.pvk -sv %keyname%_os.pvk %keyname%_os.cer
:: Create Publisher Certifcate
%winsdk%cert2spc %keyname%_os.cer %keyname%_os.spc
GOTO EOF

:GENPFX
:: Create PFX file
:: Create PFX file
%winsdk%pvk2pfx -pvk %keyname%_os.pvk -spc %keyname%_os.cer -pfx %keyname%.pfx
GOTO EOF

:SIGDLL
:: Sign DLL
%winsdk%signtool sign /v /f %keyname%.pfx /p %keypass% %keytimestamp% "%cab_folder%\webrtc-everywhere-common.dll"
%winsdk%signtool sign /v /f %keyname%.pfx /p %keypass% %keytimestamp% "%cab_folder%\webrtc-everywhere-ie.dll"
%winsdk%signtool sign /v /f %keyname%.pfx /p %keypass% %keytimestamp% "%cab_folder%\webrtc-sharepermissions-ie.dll"
%winsdk%signtool sign /v /f %keyname%.pfx /p %keypass% %keytimestamp% "%cab_folder%\x64\webrtc-everywhere-common.dll"
%winsdk%signtool sign /v /f %keyname%.pfx /p %keypass% %keytimestamp% "%cab_folder%\x64\webrtc-everywhere-ie.dll"
GOTO EOF

:GENCAB
:: Create Cab file
%win32%makecab /F webrtc-everywhere.ddf
GOTO EOF

:SIGCAB
:: Sign Cab
%winsdk%signtool sign /v /f %keyname%.pfx /p %keypass% %keytimestamp% "%cab_ddt%\%cab_filename%.cab"
GOTO EOF

:SIGCHK
:: Verify File
%winsdk%signtool verify "%cab_folder%\x64\webrtc-everywhere-common.dll"
%winsdk%signtool verify "%cab_folder%\x64\webrtc-everywhere-ie.dll"
%winsdk%signtool verify "%cab_folder%\webrtc-sharepermissions-ie.dll"
%winsdk%signtool verify "%cab_folder%\webrtc-everywhere-common.dll"
%winsdk%signtool verify "%cab_folder%\webrtc-everywhere-ie.dll"
%winsdk%signtool verify "%cab_ddt%\%cab_filename%.cab"

:EOF
ENDLOCAL