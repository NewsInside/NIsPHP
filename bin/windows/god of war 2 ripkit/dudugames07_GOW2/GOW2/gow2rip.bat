@echo -----------------------------------------------------
@echo Psychospacefish's GOD OF WAR II DVD9 to 2 DVD5 Ripkit.
@echo Please select disc1.iml in IML2ISO
@echo -----------------------------------------------------
move PART2.PAK PART2D2.PAK
move PART2D1.PAK PART2.PAK
copy GODOFWAR.TOC TOc.ORIG
ApplyPPF3 a GODOFWAR.TOC GOWTOCD1.PPF
gdvd4-iml2iso
cls
@echo ---------------------------------------------------------
@echo Please wait while PART1.PAK is ripped.
@echo ---------------------------------------------------------
splitoff x -s 0 -e 261246976 PART1.PAK OPART1A.PAK
splitoff x -s 4171608064 -e 4264382464 PART1.PAK OPART1B.PAK
del PART1.PAK
xdelta patch PART1A.XDT OPART1A.PAK PART1A.PAK
xdelta patch PART1B.XDT OPART1B.PAK PART1B.PAK
copy /b PART1A.PAK + PART1B.PAK PART1.PAK
del OPART1A.PAK
del OPART1B.PAK
del PART1A.PAK
del PART1B.PAK
del PART2.PAK
move PART2D2.PAK PART2.PAK
@echo ---------------------------
@echo Patching TOC for Disc 2.
@echo ---------------------------
del GODOFWAR.TOC
move TOc.ORIG GODOFWAR.TOC
ApplyPPF3 a GODOFWAR.TOC GOWTOCD2.PPF
cls 
@echo ----------------------------------------
@echo Building Disc 2.
@echo Please select disc2.iml when in IML2ISO.
@echo ----------------------------------------
gdvd4-iml2iso