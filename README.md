## Sysfex
Another [neofetch](https://github.com/dylanaraps/neofetch)-like system information fetching tool <b>for linux-based systems</b> written in C++. This is a hobby project, so bugs are to be expected. If you find one, please report it. Suggestions are highly appreciated. Your contribution will help Sysfex become better

<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_1.png"></p>

## Installation
To install this program, simply
```
git clone https://github.com/mebesus/sysfex
cd sysfex
sudo ./install.sh
```
The installation script uses ``g++`` for compiling sysfex. If you don't have ``g++`` installed already, install it before running the script. You may see a warning or two, ignore them. Install ``libx11`` or ``libx11-dev`` (whichever name your package manager uses) if you see this error: ``<X11/Xlib.h> header file is not found``.<br>
You may wish to install the ``font-awesome`` and [``nerd-fonts``](https://github.com/ryanoasis/nerd-fonts) package for displaying font-icons properly else they'll probably look like boxes

## Usage
* ``sysfex --help`` : Print available commands
* ``sysfex --ascii <value>`` : If value = 0, the ascii art won't be shown (``sysfex --ascii 0``). Else it'll be shown (``sysfex --ascii 1``)
* ``sysfex --ascii-dir <path-to-ascii>`` : Show an ascii image from anywhere of your computer on output
* ``sysfex --ascii-beside-txt <value>`` : Choose whether ascii art will be printed beside infos or not ( ASCII will be printed first, then infos)
* ``sysfex --icons <value>`` : If value = 0, no font-icons will be shown, else they'll be.
* ``sysfex --config <path-to-file>`` : Specify the file which you want to be used as the config file
* ``sysfex --printables <path-to-file>`` : Specify the file which you want to be used as the printables file

## Configuration
A config file is automatically created by the installation script which is located at ``/opt/sysfex/config``. Find out what's inside and what you can do with it.<br>
Wait, that's not all. You can also decide which informations to be printed through a file which is located at ``opt/sysfex/printables``.

## Gallery
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_2.png"></p>
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_3.png"></p>
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_4.png"></p>

## Contribute?
Interested to be a part of this project? Maybe issue a bug or two, or request features. I'll be very happy to see your PR with description.

## Plans for the future
- [ ] Add color support for ASCII outputs

## Special thanks to
* Some cool fetch programs spreaded all over Github for inspiration and ideas.
* The contributors, testers and those who gave me ideas as well as spread this project
* You, for being interested in this project
