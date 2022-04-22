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
    src/button.h
    src/button.cpp
    src/theme.h
    src/theme.cpp
    src/theme-json.h
    src/theme-json.cpp
    src/conf.h
    src/conf.cpp
    src/logger.h
    src/logger.cpp
)

# pkg-config
find_package(PkgConfig REQUIRED)

pkg_search_module(LIBRSVG librsvg-2.0)

target_include_directories(madobedecoration PUBLIC ${LIBRSVG_INCLUDE_DIRS})
target_compile_options(madobedecoration PUBLIC ${LIBRSVG_CFLAGS_OTHER})


target_link_libraries(madobedecoration
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::DBus
    PRIVATE
        KDecoration2::KDecoration
        KF5::CoreAddons
        KF5::GuiAddons
    ${LIBRSVG_LIBRARIES}
)
