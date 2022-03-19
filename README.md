## Sysfex
Another [neofetch](https://github.com/dylanaraps/neofetch)-like system information fetching tool for <b>linux-based systems</b> written in C++
<p align="center"><img src="https://github.com/mebesus/sysfex/blob/main/res/sysf_1.png"></p>

## Installation
Using the provided installer script:
```
git clone https://github.com/mehedirm6244/sysfex
cd sysfex
./installer.sh
```
The installer script uses ``g++`` for compiling sysfex and ``sudo`` for elevated permissions. If you don't have ``g++`` installed already, install it before running the script. You may see a warning or two, ignore them.

## Uninstallation
Run ``./installer.sh`` again. The script will first remove the existing Sysfex installation and then ask whether to reinstall this or not. Just say no
<p align="center"><img src="https://user-images.githubusercontent.com/86041547/151667328-ad0c0e4a-b468-4076-b91b-04aae9c2c9bd.png"></p>
Note that the local config files will remain untouched.

Or if you want to remove Sysfex manually:
```
sudo rm /usr/bin/sysfex
sudo rm -rf /opt/sysfex
# Remove local configuration
rm -rf ~/.config/sysfex
```

## Usage
| Flag | Description |
| -----|-------------|
| ``--help`` | Print the help message
| ``--ascii <value>`` | The ASCII art will or won't be shown depending on `<value>`. That is: `sysfex --ascii 0` will execute sysfex but without the ASCII art, whereas `sysfex --ascii 1` will execute sysfex with the ASCII art |
| ``--ascii-path <path-to-ascii>`` | Use a specified path for the ASCII art  |
| ``--ascii-beside-txt <value>`` | Choose whether ASCII art and system info will be printed side by side or not |
| ``--config <path-to-file>`` | Use a specified configuration file |
| ``--info <path-to-file>`` | Use a specified info file |

## Configuration
Global config files can be found inside ``/opt/sysfex`` and the local ones can be found in ``~/.config/sysfex``. Please note that the global config files are used as fallback when the local ones are absent, so modifying global config files are deprecated.

## Screenshots
![](https://github.com/avishekdutta531/sysfex/blob/main/res/sysf_2.png?raw=true)  |  ![](https://github.com/avishekdutta531/sysfex/blob/main/res/sysf_3.png?raw=true)
:-------------------------:|:-------------------------:
![](https://github.com/avishekdutta531/sysfex/blob/main/res/sysf_4.png?raw=true)  |  ![](https://github.com/avishekdutta531/sysfex/blob/main/res/sysf_5.png?raw=true)

## FAQ

* ### I get this error: ``<X11/Xlib.h> header file is not found``
Install ``libx11`` or ``libx11-dev`` or whichever name your package manager uses for this package

* ### Some font icons don't look as they're supposed to
Install any nerd-patched font (i.e. JetBrains Mono Nerd)

## Plans for the future
- [ ] Add support for colored outpu

## Special thanks to
* Some cool fetch tools spread all over Github for inspiration and ideas.
* The contributors, testers and those who gave me ideas as well as helped this project spread
* You, for being interested in this project
