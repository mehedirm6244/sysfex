## Sysfex
Another system information tool <b>for linux-based systems</b> mostly written in C++ (mostly because some bash functions are used inside the program).<br>
I've made this thing as a hobby project, and it's still in develpoment, so bugs are to be expected. Feel free to report a bug. Suggestions are highly appreciated.

![](https://raw.githubusercontent.com/mebesus/sysfex/main/ss.png)

## Installation
g++ is used in the installation script for compiling this program. To install this program, simply
```
git clone https://github.com/mebesus/sysfex
cd sysfex
sudo ./install.sh
```
You may see a warning or two, ignore them. You may wish to install ``ttf-font-awesome``, ``otf-font-awesome`` and ``noto-fonts-emoji`` package for displaying font-icons properly else they'll probably look like boxes

## Usage
* ``sysfex --help`` : Print available commands (still WIP)
* ``sysfex --noascii`` : Don't show the ascii image on output
* ``sysfex --ascii-dir <path_to_ascii>`` : Show another ascii image on output

A config file is automatically created by the installation script which is located at ``/opt/sysfex/config``. Find out what's inside and what you can do with it.

## Contribute?
Interested to be a part of this project? Maybe issue a bug or two, or request features. I'll be very happy to see your PR with description.

## Plans for the future
- [ ] Add GPU information
- [ ] Add support for Void Linux
- [ ] Let the user decide which information to show through a config file
- [ ] Add color support for ASCII outputs

And many more !

## Special thanks to
* [neofetch](https://github.com/dylanaraps/neofetch), [paleofetch](https://github.com/ss7m/paleofetch) and [yafetch](https://github.com/paranoidcat/yafetch) for inspiration
* [mdgaziur](https://github.com/mdgaziur) senpai
* You, for being interested in this project
