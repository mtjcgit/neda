; neda.nsi
;
; This script will generate an installer that installs neda.
;

;--------------------------------

; The name of the installer
Name "neda"
Caption "Neda Dictionary"
Icon "neda.ico"

; The file to write
OutFile "../../neda-1.0.0.exe"

; The default installation directory
InstallDir $PROGRAMFILES\neda

; Request application privileges for Windows Vista
RequestExecutionLevel user

;--------------------------------

; Pages

Page directory
Page instfiles

;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File /r "../lib" "../share"
  
SectionEnd ; end the section
