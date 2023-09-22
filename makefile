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
stage: linux-stage

# linux
linux-stage:
	cmake -B Staging \
		-DCMAKE_BUILD_TYPE=Release \
		-DQt5_DIR=$(Qt5_DIR_NIX) \
		-DBUILD_ID=$(BUILD_ID)\
		-DBUILD_SHARED_LIBS=ON -DBUILD_MODULES=ON
linux-stage-debug:
	cmake -B Staging \
		-DCMAKE_BUILD_TYPE=Debug \
		-DQt5_DIR=$(Qt5_DIR_NIX) \
		-DBUILD_ID=$(BUILD_ID)\
		-DBUILD_SHARED_LIBS=ON -DBUILD_MODULES=ON
linux-build:
	cmake --build Staging
linux-compile-release-candidate:
	cmake --build Staging --target Eddy_Compile_Release_Candidate
.PHONY: linux
linux: linux-stage linux-build linux-compile-release-candidate
.PHONY: linux-debug
linux-debug: linux-stage linux-build linux-compile-release-candidate

# mac
mac-stage:
	cmake -B Staging \
		-DCMAKE_BUILD_TYPE=Release \
		-DQt5_DIR=$(Qt5_DIR_NIX) \
		-DBUILD_ID=$(BUILD_ID)\
		-DBUILD_SHARED_LIBS=ON -DBUILD_MODULES=ON
mac-stage-debug:
	cmake -B Staging \
		-DCMAKE_BUILD_TYPE=Debug \
		-DQt5_DIR=$(Qt5_DIR_NIX) \
		-DBUILD_ID=$(BUILD_ID)\
		-DBUILD_SHARED_LIBS=ON -DBUILD_MODULES=ON
mac-build:
	cmake --build Staging
mac-compile-release-candidate:
	cmake --build Staging --target Eddy_Compile_Release_Candidate
.PHONY: mac
mac: mac-stage mac-build mac-compile-release-candidate
.PHONY: mac-debug
mac-debug: mac-stage mac-build mac-compile-release-candidate


debug-nix:
	sudo lldb Release/./${PROJECT}

debug-mac:
	leaks --atExit -- Release/./${PROJECT}

deploy-linux:
	cmake --build Staging --target Eddy_Build_AppImage