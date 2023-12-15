#!/usr/bin/env bash

readonly GCONF="/opt/sysfex" # Global config path
readonly DIR="/usr/bin"
readonly LCONF="/home/${USER}/.config/sysfex" # Local config path

RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m'

function main()
{
    if [ -d "${GCONF}" ]; then

        while true; do

            read -r -p "An existing installation of Sysfex is found. Remove or override it? [Y/n] " yn
            case $yn in

                [Yy]* )
                    printf "Removing old sysfex installation\n"
                    sudo rm -rf ${GCONF};
                    sudo rm "${DIR}/sysfex"

                    while true; do
                        read -r -p "Install Sysfex? [Y/n] " yn
                        case $yn in
                            [Yy]* ) break;;
                            [Nn]* ) exit 1;
                        esac
                    done

                    break;;

                [Nn]* )
                    printf "${RED}Rename or remove ${GCONF} before proceeding!${NC}\n"
                    exit 1;;

            esac
        done

    else
        sudo mkdir -p "${GCONF}"

    fi

    printf "Compiling sysfex...\n"

    rm -rf build
    mkdir build
    cd build
    cmake ..
    if cmake --build . -j 4; then
        cd ..
        printf "${GREEN}Compilation successful!${NC}\n"

        printf "Copying files... "
        if sudo cp -r "data/." "${GCONF}" && sudo chmod -R 755 "${GCONF}"; then
            printf "Copied!\n"
        else
            printf "${RED}Something went wrong :(${NC}"
            exit 1
        fi

        printf "Moving sysfex to ${DIR}\n"
        sudo mv "build/sysfex" "${DIR}"
        printf "chown ${USER} ${DIR}/sysfex\n"
        chown ${USER} "${DIR}/sysfex"

        if [ -d "${LCONF}" ]; then
            printf "${LCONF} exists!\n"

        else
            printf "Creating local config files for ${USER}\n"
            mkdir -p "${LCONF}"
            cp -r "data/." "${LCONF}"
        fi

        
        printf "${GREEN}Sysfex is successfully installed!${NC}\n"
        printf "sysfex --help for more information\n"

    else
        cd ..
        printf "${RED}An error occured. Failed to install sysfex${NC}\n"
        exit 1

    fi
}

main