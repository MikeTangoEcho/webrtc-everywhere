; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "webrtc-everywhere"
#define MyAppVersion "2.0.0.0"
#define MyAppPublisher "Doubango telecom"
#define MyAppURL "https://github.com/sarandogou/webrtc-everywhere"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{49969875-E6F2-4D13-84C9-BF58B9831869}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
VersionInfoVersion={#MyAppVersion}
AppVerName={#MyAppName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={userappdata}\{#MyAppName}
DefaultGroupName={#MyAppName}
DisableWelcomePage=no
DisableDirPage=yes
DisableReadyPage=no
DisableFinishedPage=no
DisableProgramGroupPage=yes
LicenseFile=C:\Projects\webrtc-everywhere\LICENSE-BSD
OutputDir=C:\Projects\webrtc-everywhere\wininstall
ShowLanguageDialog=no
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes

; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
; On all other architectures it will install in "32-bit mode".
ArchitecturesInstallIn64BitMode=x64
; Note: We don't set ProcessorsAllowed because we want this
; installation to run on all architectures (including Itanium,
; since it's capable of running 32-bit code too).
PrivilegesRequired=lowest

[Languages]
;Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "C:\Projects\webrtc-everywhere\Release\npwebrtc-everywhere-npapi.dll"; DestDir: "{userappdata}\{#MyAppName}"; Flags: ignoreversion;
Source: "C:\Projects\webrtc-everywhere\Release\webrtc-everywhere-common.dll"; DestDir: "{userappdata}\{#MyAppName}"; Flags: ignoreversion;
Source: "C:\Projects\webrtc-everywhere\Release\webrtc-everywhere-ie.dll"; DestDir: "{userappdata}\{#MyAppName}"; Flags: ignoreversion;
Source: "C:\Projects\webrtc-everywhere\x64\Release\npwebrtc-everywhere-npapi.dll"; DestDir: "{userappdata}\{#MyAppName}\x64"; Flags: ignoreversion; Check: IsWin64
Source: "C:\Projects\webrtc-everywhere\x64\Release\webrtc-everywhere-common.dll"; DestDir: "{userappdata}\{#MyAppName}\x64"; Flags: ignoreversion; Check: IsWin64
Source: "C:\Projects\webrtc-everywhere\x64\Release\webrtc-everywhere-ie.dll"; DestDir: "{userappdata}\{#MyAppName}\x64"; Flags: ignoreversion; Check: IsWin64


; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKCU64; Subkey: "SOFTWARE\Wow6432Node\MozillaPlugins\@ns313841.ovh.net/webrtc-everywhere"; ValueType: string; ValueName: "Description"; ValueData: "WebRTC everywhere"; Flags: uninsdeletekey; Check: IsWin64
Root: HKCU64; Subkey: "SOFTWARE\Wow6432Node\MozillaPlugins\@ns313841.ovh.net/webrtc-everywhere"; ValueType: string; ValueName: "Path"; ValueData: "{userappdata}\{#MyAppName}\x64\npwebrtc-everywhere-npapi.dll"; Flags: uninsdeletekey; Check: IsWin64
Root: HKCU64; Subkey: "SOFTWARE\Wow6432Node\MozillaPlugins\@ns313841.ovh.net/webrtc-everywhere"; ValueType: string; ValueName: "ProductName"; ValueData: "WebRTC everywhere"; Flags: uninsdeletekey; Check: IsWin64
Root: HKCU32; Subkey: "SOFTWARE\MozillaPlugins\@ns313841.ovh.net/webrtc-everywhere"; ValueType: string; ValueName: "Description"; ValueData: "WebRTC everywhere"; Flags: uninsdeletekey;
Root: HKCU32; Subkey: "SOFTWARE\MozillaPlugins\@ns313841.ovh.net/webrtc-everywhere"; ValueType: string; ValueName: "Path"; ValueData: "{userappdata}\{#MyAppName}\npwebrtc-everywhere-npapi.dll"; Flags: uninsdeletekey;
Root: HKCU32; Subkey: "SOFTWARE\MozillaPlugins\@ns313841.ovh.net/webrtc-everywhere"; ValueType: string; ValueName: "ProductName"; ValueData: "WebRTC everywhere"; Flags: uninsdeletekey;

; "regserver 32bit" removed from "webrtc-everywhere-ie.dll" "source" definition because of issue at http://stackoverflow.com/questions/4897685/how-do-i-register-a-dll-file-on-windows-7-64-bit
; also issue reported at https://groups.google.com/forum/#!topic/webrtc-everywhere/Od8ezlwpPBI

; Register both 32bit and 64bit versions
; http://www.cknotes.com/using-32-bit-or-64-bit-activex-components-on-x64-windows/
[Run]
Filename: "{sys}\regsvr32"; Parameters: "/s /i:user ""{userappdata}\{#MyAppName}\x64\webrtc-everywhere-ie.dll"" /n"; WorkingDir: {tmp}; Check: IsWin64;
Filename: "{syswow64}\regsvr32"; Parameters: "/s /i:user ""{userappdata}\{#MyAppName}\webrtc-everywhere-ie.dll"" /n"; WorkingDir: {tmp};

[UninstallRun]
Filename: "{sys}\regsvr32"; Parameters: "/s /u ""{userappdata}\{#MyAppName}\x64\webrtc-everywhere-ie.dll"" /n"; WorkingDir: {tmp}; Check: IsWin64; 
Filename: "{syswow64}\regsvr32"; Parameters: "/s /u ""{userappdata}\{#MyAppName}\webrtc-everywhere-ie.dll"" /n"; WorkingDir: {tmp}; 