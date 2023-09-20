# Copy:   (c) 2023 blurryroots innovation qanat OÜ
# Author: sven freiberg

# .
cmake_minimum_required(VERSION 3.16)

# .
set(TARGET_NAME Eddy)
project(${TARGET_NAME})

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
endif()

# Add the application project.
add_subdirectory(Qt)

# Define the directory holding the refined build files.
set(RELEASE_TARGET_DIR "${PROJECT_SOURCE_DIR}/Release")
# Defined root directory based on qt cmake path.
set(QT_ROOT ${Qt5_DIR}/../../..)

# .
if(MSVC)
    set(EXE_NAME "${TARGET_NAME}.exe")
    set(LIB_EXT "dll")

    # Locate windeployqt, which should come with qt installtion.
    find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(WINDEPLOYQT_ARGS --pdb --debug --compiler-runtime)
    else()
        set(WINDEPLOYQT_ARGS --release --compiler-runtime)
    endif()
    # Deploy qt dependencies.
    add_custom_target(${TARGET_NAME}_Deploy_QT_Dependencies_WIN ALL
        DEPENDS "${EDDY_BUILD_PATH}/${EXE_NAME}"
        COMMAND ${WINDEPLOYQT} ${WINDEPLOYQT_ARGS} "${EDDY_BUILD_PATH}/${EXE_NAME}"
        VERBATIM
    )

    # Gather system dependencies.
    set(WINSYS32 "C:/Windows/System32")
    add_custom_target(${TARGET_NAME}_Deploy_Native_Dependencies_WIN ALL
        DEPENDS "${EDDY_BUILD_PATH}/${EXE_NAME}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${WINSYS32}/concrt140.dll" "${EDDY_BUILD_PATH}/concrt140.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${WINSYS32}/vccorlib140.dll" "${EDDY_BUILD_PATH}/vccorlib140.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${WINSYS32}/msvcp140.dll" "${EDDY_BUILD_PATH}/msvcp140.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${WINSYS32}/vcruntime140.dll" "${EDDY_BUILD_PATH}/vcruntime140.dll"
        VERBATIM
    )
else()
    set(EXE_NAME "${TARGET_NAME}")
    set(LIB_EXT "so")
endif()

# Fetch relevant build artefacts.
add_custom_target(${TARGET_NAME}_Deploy_Build ALL
    DEPENDS ${TARGET_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory  
        "${RELEASE_TARGET_DIR}"
    COMMAND ${CMAKE_COMMAND} 
        -DSRC_PATH=${EDDY_BUILD_PATH}
        -DDST_PATH=${RELEASE_TARGET_DIR} 
        -DPATTERN=${EXE_NAME}
        -P ${PROJECT_SOURCE_DIR}/CMake/CopyRecursiveCmd.cmake
    COMMAND ${CMAKE_COMMAND} 
        -DSRC_PATH=${EDDY_BUILD_PATH}
        -DDST_PATH=${RELEASE_TARGET_DIR} 
        -DPATTERN=*.${LIB_EXT}
        -P ${PROJECT_SOURCE_DIR}/CMake/CopyRecursiveCmd.cmake
    VERBATIM
)

if(LINUX)
    set(QT_DEPLOY_URL https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage)
    set(QT_DEPLOY ${PROJECT_SOURCE_DIR}/Tools/linuxdeployqt-continuous-x86_64.AppImage)

    message(STATUS "Downloading qt deploy for linux from: ${QT_DEPLOY_URL}")
    include(FetchContent)
    FetchContent_Declare(
      QT_DEPLOY_TOOL_FETCH
      URL      ${QT_DEPLOY_URL}
      URL_HASH MD5=d84f43f29c4f038f0cc2aefda2ee2c5c
      DOWNLOAD_NO_EXTRACT TRUE
      DOWNLOAD_DIR ${PROJECT_SOURCE_DIR}/Tools
    )
    FetchContent_MakeAvailable(QT_DEPLOY_TOOL_FETCH)
    message(STATUS "Available at: ${QT_DEPLOY}")

    # Use linuxdeployqt to generate appimage.
    add_custom_target(${TARGET_NAME}_Build_AppImage
        DEPENDS ${TARGET_NAME}_Deploy_Build
        COMMAND ${CMAKE_COMMAND} -E make_directory  
            ${RELEASE_TARGET_DIR}/Candidate
        COMMAND ${CMAKE_COMMAND} 
            -DSRC_PATH=${PROJECT_SOURCE_DIR}/Raw/Linux
            -DDST_PATH=${RELEASE_TARGET_DIR}
            -DPATTERN=*
            -P ${PROJECT_SOURCE_DIR}/CMake/CopyRecursiveCmd.cmake
        COMMAND ${PROJECT_SOURCE_DIR}/Tools/./build-appimage.sh
            ${QT_DEPLOY}
            ${RELEASE_TARGET_DIR}/Eddy.desktop
            ${QT_ROOT}
            ${RELEASE_TARGET_DIR}/Candidate/${TARGET_NAME}.AppImage
        COMMAND chmod +x
            ${RELEASE_TARGET_DIR}/Candidate/${TARGET_NAME}.AppImage
        COMMAND 
        VERBATIM
    )
endif()

# Convenice target for running (raw) build files directly.
add_custom_target(${TARGET_NAME}_Run
    DEPENDS ${TARGET_NAME}
    DEPENDS ${TARGET_NAME}_Deploy_Build
    COMMAND ${RELEASE_TARGET_DIR}/${TARGET_NAME}
    VERBATIM
)
