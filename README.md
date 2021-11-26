## Sysfex
Another [neofetch](https://github.com/dylanaraps/neofetch)-like system information fetching tool <b>for linux-based systems</b> written in C++
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_1.png"></p>

## Installation
To install this program using the provided installer script:
```
git clone https://github.com/mebesus/sysfex
cd sysfex
./installer.sh
```
The installer script uses ``g++`` for compiling sysfex and ``sudo`` for elevated permissions. If you don't have ``g++`` installed already, install it before running the script. You may see a warning or two, ignore them.

## Usage
| Flag | Description |
| -----|-------------|
| ``--help`` | Print available commands
| ``--ascii <value>`` | If value = 0, the ascii art won't be shown (``sysfex --ascii 0``). Else it'll be shown (``sysfex --ascii 1``) |
| ``--ascii-dir <path-to-ascii>`` | Show an ascii image from anywhere of your computer on output |
| ``--ascii-beside-txt <value>`` | Choose whether ascii art will be printed beside infos or not ( ASCII will be printed first, then info) |
| ``--icons <value>`` | If value = 0, no font-icons will be shown, else they'll be |
| ``--config <path-to-file>`` | Specify the file which you want to be used as the config file |
| ``--printables <path-to-file>`` | Specify the file which you want to be used as the printables file |

## Configuration
Global config files can be found inside ``/opt/sysfex`` and local ones can be found in ``~/.config/sysfex``. Please note that global config files are used as fallback when local config files are absent, so modifying global config files are deprecated.

## Gallery
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_3.png"></p>
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_2.png"></p>
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_4.png"></p>

## FAQ

* ### I get the error ``<X11/Xlib.h> header file is not found``
Install ``libx11`` or ``libx11-dev`` (whichever name your package manager uses) if you see this error

* ### The font icons doesn't look okay / looks like boxes
You may wish to install the ``font-awesome`` and [``nerd-fonts``](https://github.com/ryanoasis/nerd-fonts) package for displaying font-icons properly

## Contribute?
Interested to be a part of this project? Maybe report a bug or two, or request features. I'm waiting to see your PR.

## Plans for the future
- [ ] Add color support for ASCII outputs
- [ ] Improve the config stuffs

## Special thanks to
* Some cool fetch tools spreaded all over Github for inspiration and ideas.
* The contributors, testers and those who gave me ideas as well as spread this project
* You, for being interested in this project
