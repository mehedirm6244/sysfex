/*************************************************/
/* This file is a part of Sysfex                 */
/* This function returns the number of installed */
/* packages using different package managers     */
/*************************************************/

#include <cstring>
#include <filesystem>
#include "../functions.hpp"
#include "pkgs.hpp"

std::string pkgs() {
    std::string pkg;

    /* Sorted alphabetically */
    /*
      Feel free to open a PR if you want to include a package manager
      which you're using. I myself won't be adding anything here.
    */

    /************************/
    /* dpkg (Debian/Ubuntu) */
    /************************/
    if (std::filesystem::exists("/bin/dpkg")) {
        pkg = exec("dpkg --get-selections | wc -l") + " (dpkg) ";
    }

    /***********/
    /* flatpak */
    /***********/
    if (std::filesystem::exists("/bin/flatpak")) {
        pkg = pkg + exec("flatpak list | wc -l") + " (flatpak) ";
    }

    /***************/
    /* nix (NixOS) */
    /***************/
    if (std::filesystem::exists("/nix")) {
        if (std::filesystem::exists("/etc/nix")) {
            pkg = pkg + exec("nix-store --query --requisites /run/current-system | wc -l");
        } else {
            pkg = pkg + exec("nix-env -q | wc -l");
        }
        pkg = pkg + " (nix) ";
    }

    /*************************/
    /* pacman (Arch/Manjaro) */
    /*************************/
    if (std::filesystem::exists("/bin/pacman")) {
        pkg = pkg + exec("pacman -Qq | wc -l") + " (pacman) ";
    }

    /********************/
    /* portage (Gentoo) */
    /********************/
    if (std::filesystem::exists("/bin/emerge")) {
        pkg = pkg + exec("echo -n $(cd /var/db/pkg && ls -d */* | wc -l") + " (emerge) ";
    }

    /******************/
    /* rpm (OpenSUSE) */
    /******************/
    if (std::filesystem::exists("/var/lib/rpm")) {
        pkg = pkg + exec("rpm -qa | wc -l") + " (rpm) ";
    }

    /********/
    /* Snap */
    /********/
    if (std::filesystem::exists("/bin/snap")) {
        int cnt;
        cnt = stoi(exec("snap list | wc -l")) - 1;
        pkg = pkg + std::to_string(cnt) + " (snap) ";
    }

    /*********************/
    /* XBPS (Void Linux) */
    /*********************/
    if (std::filesystem::exists("/bin/xbps-install")) {
        pkg = pkg + exec("xbps-query -l | wc -l") + " (xbps) ";
    }

    return pkg;
}