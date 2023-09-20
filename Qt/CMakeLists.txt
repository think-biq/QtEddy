# Copy:   (c) 2023 blurryroots innovation qanat OÜ
# Author: sven freiberg

cmake_minimum_required(VERSION 3.16)

option(CMAKE_BUILD_TYPE "Build mode." "Debug")
if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "No build type sppecified. Opting for 'Release'.")
    set(CMAKE_BUILD_TYPE "Release" CACHE PATH "" FORCE)
else()
    message(WARNING "Generating build setup for '${CMAKE_BUILD_TYPE}'.")
endif()

option(EDITOR_VERSION "Editor version number." "1.6.18")
if (NOT EDITOR_VERSION)
    set(EDITOR_VERSION "1.6.18")
else()
    message(WARNING "Setting version number to: '${EDITOR_VERSION}'.")
endif()

option(BUILD_ID "Build id (usually git head)." "None")
if (NOT BUILD_ID)
    set(BUILD_ID "None")
else()
    message(WARNING "Build id at: '${BUILD_ID}'.")
endif()

set(VERSION_STRING "${EDITOR_VERSION}@${BUILD_ID}")
message(WARNING "Complete version string: ${VERSION_STRING}")
add_definitions(-DEDITOR_VERSION="${VERSION_STRING}")

option(VERY_VERBOSE_OUTPUT "Very verbose debug output." 0)
if (NOT VERY_VERBOSE_OUTPUT)
    message(WARNING "VERY_VERBOSE_OUTPUT not set. Calming down verbosity.")
else()
    add_compile_definitions(VERY_VERBOSE)
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
if (NOT BUILD_SHARED_LIBS)
    message(WARNING "BUILD_SHARED_LIBS not set. Building static.")
    set(BUILD_SHARED_LIBS OFF)
else()
    message(WARNING "Building libraries as dynamic: ${BUILD_SHARED_LIBS}")
endif()

if(BUILD_SHARED_LIBS)
add_definitions(-DSHARED_LIBRARIES)
endif()

option(BUILD_MODULES "Build source modules as libraries." OFF)
if (NOT BUILD_MODULES)
    message(WARNING "BUILD_MODULES not set. Setting monolithic build.")
    set(BUILD_MODULES OFF)
else()
    message(WARNING "Building modules: ${BUILD_MODULES}")
endif()

string(
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    IS_STANDALON_PROJECT
)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed. Please specify build directory so that it's nested in project's root directory (like path_to_project/build")
endif()

set(CMAKE_SUPPRESS_REGENERATION true)
if(MSVC)
    set(CPP_STANDARD 20)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
else()
    set(CPP_STANDARD 17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

set(PROJECT_SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(PROJECT_HEADER_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Include")

# .
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
# Backwards compatibiltiy.
if(NOT Qt5_DIR)
    if(QT_ROOT_DIR)
        set(Qt5_DIR "${QT_ROOT_DIR}/lib/cmake")
    else()
        message(WARNING "QT environment variables missing.")
    endif()
endif()

# Core library
set(PROJECT_NAME_LIB_CORE "${TARGET_NAME}_Core")
file(GLOB HEADERS_CORE
    ${PROJECT_HEADER_ROOT}/Core/*.h
)
file(GLOB SOURCES_CORE
    ${PROJECT_SOURCE_ROOT}/Core/*.cpp
)
if(BUILD_MODULES)
add_library(${PROJECT_NAME_LIB_CORE}
    ${SOURCES_CORE} ${HEADERS_CORE} # needs headers for MOC generation
)
set_target_properties(${PROJECT_NAME_LIB_CORE} PROPERTIES
    AUTOMOC ON
    CPP_STANDARD ${CPP_STANDARD}
)
target_include_directories(${PROJECT_NAME_LIB_CORE}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)
target_compile_definitions(${PROJECT_NAME_LIB_CORE} PUBLIC WITH_QT)
target_link_libraries(${PROJECT_NAME_LIB_CORE}
    Qt5::Core Qt5::Widgets Qt5::Gui
)
endif()

# Editor library
set(PROJECT_NAME_LIB_EDITOR "${TARGET_NAME}_Editor")
file(GLOB HEADERS_EDITOR
    ${PROJECT_HEADER_ROOT}/Editor/*.h
)
file(GLOB SOURCES_EDITOR
    ${PROJECT_SOURCE_ROOT}/Editor/*.cpp
)
if(BUILD_MODULES)
set(SOURCES_TARGET_LIBRARY_EDITOR
    ${SOURCES_EDITOR} ${HEADERS_EDITOR}
)
else()
set(SOURCES_TARGET_LIBRARY_EDITOR
    ${SOURCES_CORE} ${HEADERS_CORE}
    ${SOURCES_EDITOR} ${HEADERS_EDITOR} 
)
endif()
add_library(${PROJECT_NAME_LIB_EDITOR}
    ${SOURCES_TARGET_LIBRARY_EDITOR} # needs headers for MOC generation
)
set_target_properties(${PROJECT_NAME_LIB_EDITOR} PROPERTIES
    AUTOMOC ON
    CPP_STANDARD ${CPP_STANDARD}
)
target_include_directories(${PROJECT_NAME_LIB_EDITOR}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)
target_compile_definitions(${PROJECT_NAME_LIB_EDITOR} PUBLIC WITH_QT)
set(QT_LIBS Qt5::Core Qt5::Widgets Qt5::Gui)
if(BUILD_MODULES)
target_link_libraries(${PROJECT_NAME_LIB_EDITOR}
    ${QT_LIBS}
    ${PROJECT_NAME_LIB_CORE}
)
else()
target_link_libraries(${PROJECT_NAME_LIB_EDITOR}
    ${QT_LIBS}
)
endif()

#.
add_executable(${TARGET_NAME} 
    ${PROJECT_SOURCE_ROOT}/main.cpp
)
set_target_properties(${TARGET_NAME} PROPERTIES
    AUTOMOC ON
    CPP_STANDARD ${CPP_STANDARD}
)
target_include_directories(${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)
if(BUILD_MODULES)
target_link_libraries(${TARGET_NAME}
    ${QT_LIBS}
    ${PROJECT_NAME_LIB_CORE}
    ${PROJECT_NAME_LIB_EDITOR}
)
else()
target_link_libraries(${TARGET_NAME}
    ${QT_LIBS}
    ${PROJECT_NAME_LIB_EDITOR}
)
endif()

# Make sure parent knows where build has been put.
if(MSVC)
    set(EDDY_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}" PARENT_SCOPE)
else()
    set(EDDY_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)
endif()