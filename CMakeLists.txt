cmake_minimum_required(VERSION 3.7)

project(
        sysfex
        VERSION 0.1
        LANGUAGES CXX
)

find_package(ICU COMPONENTS uc REQUIRED)
find_package(X11 REQUIRED)

include_directories(${X11_INCLUDE_DIR})
add_executable(sysfex
        src/sysfex.cpp
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
        src/shell_escape.cpp
        src/shell_escape.hpp
        src/modules.hpp
        src/info.hpp
        src/functions.hpp
        src/config.hpp
        src/modules/colors.hpp
        src/modules/cpu.hpp
        src/modules/de.hpp
        src/modules/host.hpp
        src/modules/kernel.hpp
        src/modules/model.hpp
        src/modules/os.hpp
        src/modules/pkgs.hpp
        src/modules/ram.hpp
        src/modules/resolution.hpp
        src/modules/shell.hpp
        src/modules/uptime.hpp
        src/modules/user.hpp
)

target_link_libraries(sysfex ${X11_LIBRARIES} ICU::uc)