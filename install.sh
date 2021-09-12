#!/usr/bin/env bash

if [ ${UID} -eq 0 ]; then
    echo "Compiling sysfex..."
    g++ sysfex.cpp -o sysfex -lX11

    CONF="/opt/sysfex"
    DIR="/usr/bin"

    if [ -d "${CONF}" ]; then
        rm -r "${CONF}"
    fi

    mkdir "${CONF}"
    cp -r "ascii" "${CONF}/ascii"
    cp "config" "${CONF}"
    cp "sysfex" "${DIR}"

else
    echo "You need root privilage for installing sysfex"
fi