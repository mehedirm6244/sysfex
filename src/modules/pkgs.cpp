/*************************************************/
/* This file is a part of Sysfex                 */
/* This function returns the number of installed */
/* packages using different package managers     */
/*************************************************/

#include <cstring>
#include <filesystem>
#include "../utils.hpp"
#include "pkgs.hpp"

std::string pkgs() {
  std::string output;

  /* Sorted alphabetically */
  /*
    Feel free to open a PR if you want to include another
    package manager not listed here
    I won't be adding anything by myself
  */
  /*
    Every package manager should have a CLI way to report how many
    (or which) packages are currently installed on the system through it.
    We'll be using that method if such exists
    For example:
      pacman -Q | wc -l     (Pacman Package Manager)
      rpm -Qa  | wc -l      (RPM Package Manager)
  */

  /************************/
  /* dpkg (Debian/Ubuntu) */
  /************************/
  if (std::filesystem::exists("/bin/dpkg")) {
    output = getOutputOf("dpkg --get-selections | wc -l") + " (dpkg) ";
  }

  /***********/
  /* flatpak */
  /***********/
  if (std::filesystem::exists("/bin/flatpak")) {
    output += getOutputOf("flatpak list | wc -l") + " (flatpak) ";
  }

  /***************/
  /* nix (NixOS) */
  /***************/
  if (std::filesystem::exists("/nix")) {
    if (std::filesystem::exists("/etc/nix")) {
      output += getOutputOf("nix-store --query --requisites /run/current-system | wc -l");
    } else {
      output += getOutputOf("nix-env -q | wc -l");
    }
    output += " (nix) ";
  }

  /*************************/
  /* pacman (Arch/Manjaro) */
  /*************************/
  if (std::filesystem::exists("/bin/pacman")) {
    output += getOutputOf("pacman -Qq | wc -l") + " (pacman) ";
  }

  /********************/
  /* portage (Gentoo) */
  /********************/
  if (std::filesystem::exists("/bin/emerge")) {
    output += getOutputOf("echo -n $(cd /var/db/pkg && ls -d */* | wc -l") + " (emerge) ";
  }

  /******************/
  /* rpm (OpenSUSE) */
  /******************/
  if (std::filesystem::exists("/var/lib/rpm")) {
    output += getOutputOf("rpm -qa | wc -l") + " (rpm) ";
  }

  /********/
  /* Snap */
  /********/
  if (std::filesystem::exists("/bin/snap")) {
    int cnt;
    cnt = stoi(getOutputOf("snap list | wc -l")) - 1;
    output += std::to_string(cnt) + " (snap) ";
  }

  /*********************/
  /* XBPS (Void Linux) */
  /*********************/
  if (std::filesystem::exists("/bin/xbps-install")) {
    output += getOutputOf("xbps-query -l | wc -l") + " (xbps) ";
  }

  return output;
}