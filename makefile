# Copy:   (c) 2023 blurryroots innovation qanat OÜ
# Author: sven freiberg

PROJECT := Eddy
BUILD_ID := "$(shell git rev-parse HEAD)"

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	Qt5_DIR_NIX := "/opt/qt/5.14.2/gcc_64/lib/cmake/Qt5"
endif
ifeq ($(UNAME_S),Darwin)
    Qt5_DIR_MAC := "$(shell brew --prefix qt@5)/lib/cmake/Qt5"
endif


.PHONY: all
all: stage run

clean:
	rm -rf Staging CMakeFiles Release CMakeCache.txt

.PHONY: stage
stage: stage-nix

stage-nix: stage-nix-debug
	cmake -B Staging \
		-DCMAKE_BUILD_TYPE=Release \
		-DQt5_DIR=$(Qt5_DIR_NIX) \
		-DBUILD_ID=$(BUILD_ID)\
		-DBUILD_SHARED_LIBS=OFF -DBUILD_MODULES=OFF
stage-nix-debug:
	cmake -B Staging \
		-DCMAKE_BUILD_TYPE=Debug \
		-DQt5_DIR=$(Qt5_DIR_NIX) \
		-DBUILD_ID=$(BUILD_ID)\
		-DBUILD_SHARED_LIBS=ON -DBUILD_MODULES=ON

stage-mac:
	echo "$(shell brew --prefix qt@5)/lib/cmake/Qt5"
	cmake -B Staging \
		-DCMAKE_BUILD_TYPE=Release \
		-DQt5_DIR=$(Qt5_DIR_MAC) \
		-DBUILD_ID=$(BUILD_ID) \
		-DBUILD_SHARED_LIBS=ON -DBUILD_MODULES=ON \
		-DGENERATE_DMG=TRUE
stage-mac-debug:
	echo "$(shell brew --prefix qt@5)/lib/cmake/Qt5"
	cmake -B Staging \
		-DCMAKE_BUILD_TYPE=Debug \
		-DQt5_DIR=$(Qt5_DIR_MAC) \
		-DBUILD_ID=$(BUILD_ID) \
		-DBUILD_SHARED_LIBS=ON -DBUILD_MODULES=ON \
		-DGENERATE_DMG=FALSE

build:
	cmake --build Staging

run:
	cmake --build Staging --target Eddy_Run

debug: debug-nix

debug-nix:
	sudo lldb Release/./${PROJECT}

debug-mac:
	leaks --atExit -- Release/./${PROJECT}

deploy-linux:
	QT_ROOT="$(Qt5_DIR_NIX/../../..)"; Tools/./deploy-appimage.sh