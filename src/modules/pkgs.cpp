/*

This file is from Sysfex, another system info fetching tool

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "modules/pkgs.hpp"
#include "utils.hpp"

#include <sstream>
#include <filesystem>

std::string pkgs() {
  std::string output;

  /* dpkg (Debian/Ubuntu) */
  if (std::filesystem::exists("/bin/dpkg")
    or std::filesystem::exists("/usr/bin/dpkg")) {
    output += sfUtils::get_output_of("dpkg --get-selections | wc -l") + " (dpkg) ";
  }

  /* flatpak */
  if (std::filesystem::exists("/bin/flatpak")
    or std::filesystem::exists("/usr/bin/flatpak")) {
    output += sfUtils::get_output_of("flatpak list | wc -l") + " (flatpak) ";
  }

  /* nix (NixOS) */
  if (std::filesystem::exists("/nix")) {
    if (std::filesystem::exists("/etc/nix")) {
      output += sfUtils::get_output_of("nix-store --query --requisites /run/current-system | wc -l");
    } else {
      output += sfUtils::get_output_of("nix-env -q | wc -l");
    }
    output += " (nix) ";
  }

  /* pacman (Arch) */
  if (std::filesystem::exists("/bin/pacman")
    or std::filesystem::exists("/usr/bin/pacman")) {
    output += sfUtils::get_output_of("pacman -Qq | wc -l") + " (pacman) ";
  }

  /* portage (Gentoo) */
  if (std::filesystem::exists("/bin/emerge")
    or std::filesystem::exists("/usr/bin/emerge")) {
    output += sfUtils::get_output_of("echo -n $(cd /var/db/pkg && ls -d */* | wc -l") + " (emerge) ";
  }

  /* rpm (OpenSUSE) */
  if (std::filesystem::exists("/var/lib/rpm")) {
    output += sfUtils::get_output_of("rpm -qa | wc -l") + " (rpm) ";
  }

  /* Snap */
  if (std::filesystem::exists("/bin/snap")
    or std::filesystem::exists("/usr/bin/snap")) {
    int pkg_count = stoi(sfUtils::get_output_of("snap list | wc -l")) - 1; // Output includes a header row
    output += std::to_string(pkg_count) + " (snap) ";
  }

  /* XBPS (Void Linux) */
  if (std::filesystem::exists("/bin/xbps-install")
    or std::filesystem::exists("/usr/bin/xbps-install")) {
    output += sfUtils::get_output_of("xbps-query -l | wc -l") + " (xbps) ";
  }

  return output;
}
