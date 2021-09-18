#!/usr/bin/env bash

if [ ${UID} -eq 0 ]; then
    echo "Compiling sysfex..."
    if g++ src/sysfex.cpp -o sysfex -std=c++17 -lX11 -lstdc++fs; then
        CONF="/opt/sysfex"
        DIR="/usr/bin"

        if [ -d "${CONF}" ]; then
            echo "${CONF} already exists. Remove it?"
            select yn in "Yes" "No"; do
                case $yn in
                    Yes ) rm -rf ${CONF}; break;;
                    No ) echo "Move/rename ${CONF} before proceeding!"; exit 1;;
                esac
            done
        fi

        mkdir "${CONF}"
        cp -r "data/ascii" "${CONF}/ascii"
        cp "data/config" "${CONF}"
        mv "sysfex" "${DIR}"
        
        echo "Sysfex is successfully installed! Enjoy :D \n"
        echo "sysfex --help for more informations"

    else
        echo "An error occured. Failed to install sysfex"
        exit 1

    fi

else
    echo "You need root privilege for installing sysfex"

fi
