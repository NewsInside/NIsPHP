# Microsoft Developer Studio Project File - Name="gui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=gui - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gui.mak" CFG="gui - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gui - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "gui - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gui - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "GUI" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x816 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x816 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/ps2_yfix.exe"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "gui - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "GUI" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x816 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x816 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gui - Win32 Release"
# Name "gui - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "CD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cd\CDVDbin.c
# End Source File
# Begin Source File

SOURCE=.\cd\CDVDedit.cpp
# End Source File
# Begin Source File

SOURCE=.\cd\CDVDiso.c
# End Source File
# Begin Source File

SOURCE=.\cd\CDVDisodrv.c
# End Source File
# Begin Source File

SOURCE=.\cd\ecc.c
# End Source File
# Begin Source File

SOURCE=.\cd\edc.c
# End Source File
# Begin Source File

SOURCE=.\cd\Misc.c
# End Source File
# End Group
# Begin Group "Selector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\pnselector\loadelf.c
# End Source File
# Begin Source File

SOURCE=.\pnselector\pn_sel1.cpp
# End Source File
# Begin Source File

SOURCE=.\pnselector\sjcrunch_pack.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Elfheader.cpp
# End Source File
# Begin Source File

SOURCE=.\gui.cpp
# End Source File
# Begin Source File

SOURCE=.\gui.rc
# End Source File
# Begin Source File

SOURCE=.\guiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "CD Inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cd\CDVD.h
# End Source File
# Begin Source File

SOURCE=.\cd\CDVDbin.h
# End Source File
# Begin Source File

SOURCE=.\cd\CDVDiso.h
# End Source File
# Begin Source File

SOURCE=.\cd\CDVDisodrv.h
# End Source File
# Begin Source File

SOURCE=.\cd\Misc.h
# End Source File
# End Group
# Begin Group "Selector inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\pnselector\loadelf.h
# End Source File
# Begin Source File

SOURCE=.\pnselector\lzo1x.h
# End Source File
# Begin Source File

SOURCE=.\pnselector\lzoconf.h
# End Source File
# Begin Source File

SOURCE=.\pnselector\tamtypes.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\gui.h
# End Source File
# Begin Source File

SOURCE=.\guiDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\gui.ico
# End Source File
# Begin Source File

SOURCE=.\res\gui.rc2
# End Source File
# End Group
# Begin Group "Library Files"

# PROP Default_Filter "*.lib"
# Begin Source File

SOURCE=.\pnselector\libpack.lib
# End Source File
# End Group
# End Target
# End Project
