cmake_minimum_required(VERSION 3.5)
project(madobe)

set(KF5_MIN_VERSION "5.68.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons GuiAddons ConfigWidgets WindowSystem)
find_package(Qt5 CONFIG REQUIRED COMPONENTS Dbus)

add_library(madobedecoration MODULE
)
