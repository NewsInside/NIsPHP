#SRC_URL = http://sourceforge.net/projects/bochs/files/bochs/2.4.6/bochs-2.4.6.tar.gz
SRC_URL = http://ps2dev.karashome.boo.pl/download.php/remote/bochs-2.4.6.tar.gz
SRC_ARCHIVE = $(notdir $(SRC_URL))
SRC_BASENAME := $(basename $(SRC_ARCHIVE))
SRC_BASENAME := $(basename $(SRC_BASENAME))

SRC_DIR_PATCH = ./patch
SRC_PATCH = $(SRC_DIR_PATCH)/ps2-$(SRC_BASENAME).patch
SRC_DIR = ./$(SRC_BASENAME)

all: clean download-src extract-src patch-src
	@echo Done!
	@echo Now you can type:
	@echo + make compile-ps2
	@echo + make compile-win32
	@echo if sdl library already configured!

download-src:
	@echo Downloading archive...
	@wget $(SRC_URL)

extract-src:
	@echo Extracting $(SRC_ARCHIVE)...
	@tar xvzf $(SRC_ARCHIVE)

patch-src:
	@echo Applying $(SRC_PATCH)...
	@patch -d $(SRC_DIR) -p2 -i .$(SRC_PATCH)
	@cp -r irx/ $(SRC_DIR)/ps2/

patch-make:
	@make -C $(SRC_DIR) -f Makefile.ps2 clean
	@make -C $(SRC_DIR) -f Makefile.win32 clean
	@mv $(SRC_DIR) $(SRC_DIR)-patched
	@tar xvzf $(SRC_ARCHIVE)
	@-diff -ruNwb $(SRC_DIR) $(SRC_DIR)-patched > $(SRC_PATCH:.patch=-new.patch)
	@patch -d $(SRC_DIR) -p2 -i .$(SRC_PATCH:.patch=-new.patch)
	@rm -fr $(SRC_DIR)-patched
	@echo Created new patch: $(SRC_PATCH:.patch=-new.patch)!
	
compile-ps2:
	@make -C $(SRC_DIR) -f Makefile.ps2 config all

compile-win32:
	@make -C $(SRC_DIR) -f Makefile.win32 config all

clean:
	@rm -fr $(SRC_DIR) $(SRC_DIR)-patched
	@rm -f *.gz
