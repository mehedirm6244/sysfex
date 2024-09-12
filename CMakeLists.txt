cmake_minimum_required(VERSION 3.7)

project(
  sysfex
  VERSION 0.1
  LANGUAGES CXX
)

find_package(ICU COMPONENTS uc REQUIRED)
find_package(X11 REQUIRED)

include_directories(${X11_INCLUDE_DIR})
include_directories(./includes)
include_directories(./lib)
add_executable(sysfex
  src/sysfex.cpp
  src/config.cpp
  src/utils.cpp
  src/info.cpp
  src/image.cpp
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
  includes/shell_escape.hpp
  includes/modules.hpp
  includes/info.hpp
  includes/config.hpp
  includes/modules/cpu.hpp
  includes/modules/de.hpp
  includes/modules/host.hpp
  includes/modules/kernel.hpp
  includes/modules/model.hpp
  includes/modules/os.hpp
  includes/modules/pkgs.hpp
  includes/modules/ram.hpp
  includes/modules/resolution.hpp
  includes/modules/shell.hpp
  includes/modules/uptime.hpp
  includes/modules/user.hpp
  includes/utils.hpp
  includes/image.hpp
)

target_link_libraries(sysfex ${X11_LIBRARIES} ICU::uc)
