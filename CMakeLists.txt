cmake_minimum_required(VERSION 3.7)

project(
  sysfex
  VERSION 0.1
  LANGUAGES CXX
)

find_package(ICU COMPONENTS uc REQUIRED)

include_directories(./includes)
include_directories(./lib)
add_executable(sysfex
  src/sysfex.cpp
  src/config.cpp
  src/utils.cpp
  src/info.cpp
  src/image.cpp
  src/main.cpp
  src/modules/cpu.cpp
  src/modules/cpu_temp.cpp
  src/modules/de.cpp
  src/modules/distro.cpp
  src/modules/gpu.cpp
  src/modules/host.cpp
  src/modules/kernel.cpp
  src/modules/model.cpp
  src/modules/os.cpp
  src/modules/pkgs.cpp
  src/modules/ram.cpp
  src/modules/resolution.cpp
  src/modules/shell.cpp
  src/modules/swap.cpp
  src/modules/uptime.cpp
  src/modules/user.cpp
  includes/modules.hpp
  includes/info.hpp
  includes/config.hpp
  includes/modules/cpu.hpp
  includes/modules/cpu_temp.hpp
  includes/modules/de.hpp
  includes/modules/distro.hpp
  includes/modules/gpu.hpp
  includes/modules/host.hpp
  includes/modules/kernel.hpp
  includes/modules/model.hpp
  includes/modules/os.hpp
  includes/modules/pkgs.hpp
  includes/modules/ram.hpp
  includes/modules/resolution.hpp
  includes/modules/shell.hpp
  includes/modules/swap.hpp
  includes/modules/uptime.hpp
  includes/modules/user.hpp
  includes/utils.hpp
  includes/image.hpp
  includes/sysfex.hpp
)

target_link_libraries(sysfex ICU::uc)
