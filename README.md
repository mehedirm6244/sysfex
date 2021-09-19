## Sysfex
Another [neofetch](https://github.com/dylanaraps/neofetch)-like system information fetching tool <b>for linux-based systems</b> mostly written in C++ (mostly because some bash functions are used inside the program). I've made this thing as a hobby project, and it's still in develpoment, so bugs are to be expected. If you find one, please report it. Suggestions are highly appreciated. Your contribution will help this project become stronger

![](https://raw.githubusercontent.com/mebesus/sysfex/main/ss.png)

Font-icons are disabled by default from [this commit](https://github.com/mebesus/sysfex/commit/17655c2b724344be16fd31e28c40595b054bef88). If you wish to use this feature, edit the config file for sysfex on ``/opt/sysfex/config`` or use ``sysfex --icons 1`` command.

## Installation
``g++`` is used in the installation script for compiling this program. To install this program, simply
```
git clone https://github.com/mebesus/sysfex
cd sysfex
sudo ./install.sh
```
You may see a warning or two, ignore them. Install ``libx11`` or ``libx11-dev`` (whatever name your package manager uses) if you see this error: ``<X11/Xlib.h> header file is not found``.<br>
You may wish to install the ``font-awesome`` and [``nerd-fonts``](https://github.com/ryanoasis/nerd-fonts) package for displaying font-icons properly else they'll probably look like boxes

## Usage
* ``sysfex --help`` : Print available commands
* ``sysfex --ascii <value>`` : If value = 0, the ascii art won't be shown (``sysfex --ascii 0``). Else it'll be shown (``sysfex --ascii 1``)
* ``sysfex --ascii-dir <path_to_ascii>`` : Show an ascii image from anywhere of your computer on output
* ``sysfex --icons <value>`` : If value = 0, no font-icons will be shown, else they'll be.

A config file is automatically created by the installation script which is located at ``/opt/sysfex/config``. Find out what's inside and what you can do with it.

## Contribute?
Interested to be a part of this project? Maybe issue a bug or two, or request features. I'll be very happy to see your PR with description.

## Plans for the future
- [ ] Let the user decide which informations are to be shown through the config file
- [ ] Add color support for ASCII outputs

And many more !

## Special thanks to
* Some cool fetch programs spreaded all over Github for inspiration and ideas.
* The contributors, testers and those who gave me ideas / suggestions
* You, for being interested in this project