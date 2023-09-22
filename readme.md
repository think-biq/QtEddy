# Eddy

Minimalistic cmake-based Qt Desktop build environment with github actions support.

![alt text](Raw/Linux/Eddy.png "Eddy")

## Overview

The main application code is located in *Qt*. Auxiliary files and assets are stored in *Raw*. Scripts and utilties are found in *Tools*. Additional cmake scripts are located in *CMake*.
You can read [this article](https://think-biq.com/blog) for details on the architecture.

## CMake structure

As far as cmake is concerned, there is the top-level project, which includes the application project. The top-level project is responsible for housing the application build and implementing platform dependend deploy mechanics. The application project is split into two modules. *Core* and *Editor*. You can configure the build to either use them as separate libraries (either statically or dynamically). A simple versioning scheme is in place, which exposes a symbolic constant called *EDITOR_VERSION* containing a semantic version number with the commit hash appended.

## Platforms

Current supported platforms are:
* [Windows](https://github.com/think-biq/QtEddy/actions/workflows/windows_release.yml) (10 and upwards)
* [Linux](https://github.com/think-biq/QtEddy/actions/workflows/linux_release.yml) (comparable to ubuntu 20.08)
* [MacOS](https://github.com/think-biq/QtEddy/actions/workflows/mac_release.yml) (locally 10.*, CI/CD 11 and upwards)