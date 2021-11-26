void pkgs()
{
    string pkg;

    // dpkg
    if (std::filesystem::exists("/bin/dpkg"))
        pkg = pkg + exec("dpkg --get-selections | wc -l") + " (dpkg) ";

    // nix
    if (std::filesystem::exists("/nix"))
    {
        if(std::filesystem::exists("/etc/nix"))
            pkg = pkg + exec("nix-store --query --requisites /run/current-system | wc -l");
        else
            pkg = pkg + exec("nix-env -q | wc -l");

        pkg = pkg + " (nix) ";
    }

    // pacman
    if (std::filesystem::exists("/bin/pacman"))
        pkg = pkg + exec("pacman -Qq | wc -l") + " (pacman) ";

    // portage
    if (std::filesystem::exists("/bin/emerge"))
        pkg = pkg + exec("echo -n $(cd /var/db/pkg && ls -d */* | wc -l") + " (emerge) ";

    // rpm
    if (std::filesystem::exists("/var/lib/rpm"))
        pkg = pkg + exec("rpm -qa | wc -l") + " (rpm) ";
    
    // XBPS
    if (std::filesystem::exists("/bin/xbps-install"))
        pkg = pkg + exec("xbps-query -l | wc -l") + " (xbps) ";


    // Snap
    if (std::filesystem::exists("/bin/snap"))
    {
        int cnt = stoi(exec("snap list | wc -l")) - 1;
        pkg = pkg + std::to_string(cnt) + " (snap) ";
    }

    // flatpak
    if (std::filesystem::exists("/bin/flatpak"))
        pkg = pkg + exec("flatpak list | wc -l") + " (flatpak) ";

    print("", "Pkgs", pkg);
}