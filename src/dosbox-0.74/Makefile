SRC_URL = http://sourceforge.net/projects/dosbox/files/dosbox/0.74/dosbox-0.74.tar.gz
SRC_PATCH = patch/ps2-dosbox-0.74.patch
SRC_ARCHIVE = $(notdir $(SRC_URL))
SRC_DIR = $(basename $(SRC_ARCHIVE))
SRC_DIR := $(basename $(SRC_DIR))

all: clean download-src extract-src apply-patch start-compile

download-src:
	@echo Downloading archive...
	@wget $(SRC_URL)

extract-src:
	@echo Extracting $(SRC_ARCHIVE)...
	@tar xvzf $(SRC_ARCHIVE)

apply-patch:
	@echo Applying $(SRC_PATCH)...
	@patch -p0 -i $(SRC_PATCH)

start-compile:
	@cp -r irx/ $(SRC_DIR)/src/ps2/
	@make -C $(SRC_DIR) -f Makefile.ps2

clean:
	@rm -fr $(SRC_DIR)
	@rm -f *.gz
