#!/usr/bin/env bash

readonly GCONF="/opt/sysfex" # Global config path
readonly DIR="/usr/bin"
readonly LCONF="/home/${USER}/.config/sysfex" # Local config path

function main()
{
    if [ -d "${GCONF}" ]; then

        while true; do

            read -r -p "An existing installation of Sysfex is found. Remove or override it? [Y/n] " yn
            case $yn in

                [Yy]* )
                    echo "Removing old sysfex installation"
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
                    echo "Rename or remove ${GCONF} before proceeding!"
                    exit 1;;

            esac
        done

    else
        sudo mkdir -p "${GCONF}"

    fi

    echo "Compiling sysfex..."

    if g++ src/sysfex.cpp -o sysfex -std=c++17 -lX11 -lstdc++fs; then

        echo "Compilation successful!"

        echo "Copying files"
        if sudo cp -r "data/." "${GCONF}"; then
            echo "Copied!"
        else
            echo "Something went wrong :("
            exit 1
        fi

        echo "Moving sysfex to ${DIR}"
        sudo mv "sysfex" "${DIR}"
        echo "chown ${USER} ${DIR}/sysfex"
        chown ${USER} "${DIR}/sysfex"

        if [ -d "${LCONF}" ]; then
            echo "${LCONF} exists"

        else
            echo "Creating local config files for ${USER}"
            mkdir -p "${LCONF}"
            cp -r "data/." "${LCONF}"
        fi

        
        echo "Sysfex is successfully installed! Enjoy :D"
        echo "sysfex --help for more information"

    else
        echo "An error occured. Failed to install sysfex"
        exit 1

    fi
}

main