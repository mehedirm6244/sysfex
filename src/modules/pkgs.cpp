#include <sstream>
#include <filesystem>

#include <utils.hpp>
#include <modules/pkgs.hpp>

std::string pkgs() {
  std::ostringstream output;

  /* Feel free to open a PR to include a package manager not listed here */

  /* dpkg (Debian/Ubuntu) */
  if (std::filesystem::exists("/bin/dpkg") or std::filesystem::exists("/usr/bin/dpkg")) {
    output << get_output_of("dpkg --get-selections | wc -l") << " (dpkg) ";
  }

  /* flatpak */
  if (std::filesystem::exists("/bin/flatpak") or std::filesystem::exists("/usr/bin/flatpak")) {
    output << get_output_of("flatpak list | wc -l") << " (flatpak) ";
  }

  /* nix (NixOS) */
  if (std::filesystem::exists("/nix")) {
    if (std::filesystem::exists("/etc/nix")) {
      output << get_output_of("nix-store --query --requisites /run/current-system | wc -l");
    } else {
      output << get_output_of("nix-env -q | wc -l");
    }
    output << " (nix) ";
  }

  /* pacman (Arch/Manjaro) */
  if (std::filesystem::exists("/bin/pacman") or std::filesystem::exists("/usr/bin/pacman")) {
    output << get_output_of("pacman -Qq | wc -l") + " (pacman) ";
  }

  /* portage (Gentoo) */
  if (std::filesystem::exists("/bin/emerge") or std::filesystem::exists("/usr/bin/emerge")) {
    output << get_output_of("echo -n $(cd /var/db/pkg && ls -d */* | wc -l") << " (emerge) ";
  }

  /* rpm (OpenSUSE) */
  if (std::filesystem::exists("/var/lib/rpm")) {
    output << get_output_of("rpm -qa | wc -l") << " (rpm) ";
  }

  /* Snap */
  if (std::filesystem::exists("/bin/snap") or std::filesystem::exists("/usr/bin/snap")) {
    int pkg_count = stoi(get_output_of("snap list | wc -l")) - 1; // Output includes a header row
    output << std::to_string(pkg_count) << " (snap) ";
  }

  /* XBPS (Void Linux) */
  if (std::filesystem::exists("/bin/xbps-install") or std::filesystem::exists("/usr/bin/xbps-install")) {
    output << get_output_of("xbps-query -l | wc -l") << " (xbps) ";
  }

  return output.str();
}
