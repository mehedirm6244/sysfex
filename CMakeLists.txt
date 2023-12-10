cmake_minimum_required(VERSION 3.7)

project(
        sysfex
        VERSION 0.1
        LANGUAGES CXX
)

find_package(ICU COMPONENTS uc REQUIRED)
find_package(X11 REQUIRED)

add_library(
        libsysfex
        src/config.cpp
        src/functions.cpp
        src/info.cpp
        src/modules/colors.cpp
        src/modules/cpu.cpp
        src/modules/de.cpp
        src/modules/host.cpp
        src/modules/kernel.cpp
        src/modules/model.cpp
        src/modules/os.cpp
        src/modules/pkgs.cpp
        src/modules/ram.cpp
        src/modules/resolution.cpp
        src/modules/shell.cpp
        src/modules/uptime.cpp
        src/modules/user.cpp
)

include_directories(${X11_INCLUDE_DIR})
add_executable(sysfex src/sysfex.cpp)

target_link_libraries(sysfex PRIVATE libsysfex ${X11_LIBRARIES} ICU::uc)