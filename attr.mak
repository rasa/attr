# Microsoft Developer Studio Generated NMAKE File, Based on attr.dsp
!IF "$(CFG)" == ""
CFG=attr - Win32 Debug
!MESSAGE No configuration specified. Defaulting to attr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "attr - Win32 Release" && "$(CFG)" != "attr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "attr.mak" CFG="attr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "attr - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "attr - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "attr - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\attr.exe"


CLEAN :
	-@erase "$(INTDIR)\attr.obj"
	-@erase "$(INTDIR)\attr.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\attr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\shared" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\attr.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\attr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\attr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=shared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\attr.pdb" /machine:I386 /out:"$(OUTDIR)\attr.exe" /libpath:"..\shared" 
LINK32_OBJS= \
	"$(INTDIR)\attr.obj" \
	"$(INTDIR)\attr.res"

"$(OUTDIR)\attr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "attr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\attr.exe" "$(OUTDIR)\attr.bsc"


CLEAN :
	-@erase "$(INTDIR)\attr.obj"
	-@erase "$(INTDIR)\attr.res"
	-@erase "$(INTDIR)\attr.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\attr.bsc"
	-@erase "$(OUTDIR)\attr.exe"
	-@erase "$(OUTDIR)\attr.ilk"
	-@erase "$(OUTDIR)\attr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\shared" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\attr.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\attr.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\attr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\attr.sbr"

"$(OUTDIR)\attr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=sharedd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\attr.pdb" /debug /machine:I386 /out:"$(OUTDIR)\attr.exe" /pdbtype:sept /libpath:"..\shared" 
LINK32_OBJS= \
	"$(INTDIR)\attr.obj" \
	"$(INTDIR)\attr.res"

"$(OUTDIR)\attr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("attr.dep")
!INCLUDE "attr.dep"
!ELSE 
!MESSAGE Warning: cannot find "attr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "attr - Win32 Release" || "$(CFG)" == "attr - Win32 Debug"
SOURCE=.\attr.cpp

!IF  "$(CFG)" == "attr - Win32 Release"


"$(INTDIR)\attr.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "attr - Win32 Debug"


"$(INTDIR)\attr.obj"	"$(INTDIR)\attr.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\attr.rc

"$(INTDIR)\attr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

