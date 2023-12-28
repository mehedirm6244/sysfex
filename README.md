# Sysfex
Sysfex is just another system information fetching tool for <b>linux-based systems</b>, written in C++
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/screenshots/ss.gif?raw=true"></p>

## Key Features
- Print ASCII and information side by side, or top to bottom
- Print output with custom formatting (colors, font formating etc) through escape sequences
- Render image (.bmp, .jpg, .png, .webp) in place of ASCII using [viu](https://github.com/atanunq/viu) if requested
- Customize output format without recompiling through dedicated configuration files

## Installation

Required for installing Sysfex:
- ANSI Escape Sequence supported terminal emulator
- `CMake` : for compiling
- `libx11` (or `libx11-dev`) : for getting screen resolution on Xorg
- `viu` : backend for rendering image


### Cloning and compiling

Clone Sysfex from it's GitHub repository using Git:
```
git clone https://github.com/mehedirm6244/sysfex
cd sysfex
```

Compile Sysfex:
```
mkdir build && cd build
cmake ..
cmake --build . -j 4
```

### Installing Sysfex to system

Make sure that the present working directory is `sysfex`
```
cd ..
```
Copy files to proper directories:
```
sudo cp -r presets/. /opt/sysfex
sudo chmod -R 755 /opt/sysfex
sudo cp build/sysfex /usr/bin
sudo chown ${USER} /usr/bin/sysfex
```
Make local configuration file which can be modified further
```
mkdir -p ${HOME}/.config/sysfex
cp -r presets/. ${HOME}/.config/sysfex
```

## Uninstallation

Remove Sysfex from system:
```
sudo rm /usr/bin/sysfex
sudo rm -rf /opt/sysfex
```

Remove local config:
```
rm -rf ${HOME}/.config/sysfex
```

## Usage

Use `sysfex --help` for listing all available flags

## Configuration

Sysfex supports global (for all user) as well as local configurations (for current user). Sysfex will initialize configurations from `${HOME}/.config/sysfex` if the directory exists, or from `/opt/sysfex` otherwise.

The configuration for Sysfex is split into two files
| File name | Description |
| ----------|-------------|
| ``config`` | Stores instructions on how to print stuffs, such as: gaps, character used in color blocks, separator character, which ascii to print etc
| ``info`` | Stores instructions on what to be printed, such as: model name, screen resolution, kernel version etc |

## To Do
- [x] Add support for images
- [x] Add support for colored output
- [ ] Rewrite configuration file handling method
- [ ] Use simpler and human method in source code where possible
- [ ] Write documentation

## Special thanks to

* Some cool fetch tools spread all over Github for inspiration and ideas.
* [nothings/stb](https://github.com/nothings/stb) for a nice image processing library
* The contributors, testers and those who gave me ideas as well as helped this project spread
* You, for being interested in this project
