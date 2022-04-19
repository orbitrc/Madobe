cmake_minimum_required(VERSION 3.5)
project(madobe)

set(KF5_MIN_VERSION "5.68.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons GuiAddons ConfigWidgets WindowSystem)
find_package(Qt5 CONFIG REQUIRED COMPONENTS DBus)

include(KDEInstallDirs)
include(KDECMakeSettings)

find_package(KDecoration2 REQUIRED)

add_library(madobedecoration MODULE
    src/madobedecoration.h
    src/madobedecoration.cpp
    src/logger.h
    src/logger.cpp
)

target_link_libraries(madobedecoration
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::DBus
    PRIVATE
        KDecoration2::KDecoration
        KF5::CoreAddons
        KF5::GuiAddons
)
