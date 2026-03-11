cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(USE_ZLIB OFF) # disable IXWebSock-et's usage of zlib

project(ArchipelagoGDAgain VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/ConnectPopup.cpp
    src/LevelSelectLayerHook.cpp
    src/PortalLogic.cpp
    src/APUtils.cpp
    src/AchievementBarHook.cpp
    src/LoadingLayerHook.cpp
    # Add any extra C++ source files here
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})

CPMAddPackage(
    NAME APCpp-gd
    GIT_REPOSITORY https://github.com/matorblal-byte/APCpp-gd
    GIT_TAG main
)

target_link_libraries(${PROJECT_NAME} APCpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${APCpp_SOURCE_DIR})