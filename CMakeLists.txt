cmake_minimum_required(VERSION 3.7)

project(
        sysfex
        VERSION 0.1
        LANGUAGES CXX
)

find_package(ICU COMPONENTS uc REQUIRED)
find_package(X11 REQUIRED)

include_directories(${X11_INCLUDE_DIR})
include_directories(./include)
add_executable(sysfex
        src/sysfex.cpp
        src/config.cpp
        src/utils.cpp
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
        include/shell_escape.hpp
        include/modules.hpp
        include/info.hpp
        include/config.hpp
        include/modules/colors.hpp
        include/modules/cpu.hpp
        include/modules/de.hpp
        include/modules/host.hpp
        include/modules/kernel.hpp
        include/modules/model.hpp
        include/modules/os.hpp
        include/modules/pkgs.hpp
        include/modules/ram.hpp
        include/modules/resolution.hpp
        include/modules/shell.hpp
        include/modules/uptime.hpp
        include/modules/user.hpp
        include/utils.hpp
)

target_link_libraries(sysfex ${X11_LIBRARIES} ICU::uc)
