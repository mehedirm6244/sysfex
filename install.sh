#!/usr/bin/env bash

if [ ${UID} -eq 0 ]; then
    echo "Compiling sysfex..."
    if g++ src/sysfex.cpp -o sysfex -lX11; then
        CONF="/opt/sysfex"
        DIR="/usr/bin"

        if [ -d "${CONF}" ]; then
            echo "Existing sysfex footprint found on /opt/sysfex. Remove or move it first"
            exit
        fi

        mkdir "${CONF}"
        cp -r "data/ascii" "${CONF}/ascii"
        cp "data/config" "${CONF}"
        mv "sysfex" "${DIR}"
        
        echo "Sysfex is successfully installed! Enjoy :D"
    fi

else
    echo "You need root privilage for installing sysfex"
fi