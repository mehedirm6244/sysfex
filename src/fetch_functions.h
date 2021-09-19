#define __ABORT__   { cout<<endl; return; }


struct utsname uname_info;


// The username and the host name
void title()
{
    string host, user;
    user = getlogin();

    std::ifstream infile;
    infile.open("/proc/sys/kernel/hostname");
    if(!(infile.is_open())) __ABORT__
    infile>>host;
    infile.close();

    cout<<string(stoi(conf["pregap"]), ' ');
    cout<<BOLD;
    if(conf["icons"]!="0") cout<<"  ";
    cout<<user<<UBOLD;
    cout<<" on ";
    if(conf["icons"]!="0") cout<<"  ";
    cout<<BOLD<<host<<UBOLD<<endl;
}



// The name of the OS
void os()
{
    string name, prettyName = "PRETTY_NAME=\"";

    std::ifstream infile;
    infile.open("/etc/os-release");
    if(!(infile.is_open())) __ABORT__
    while(infile.good())
    {
        std::getline(infile, name);
        if(name.find(prettyName)!=string::npos)
            break;
    }
    infile.close();

    name = name.substr(prettyName.length(), name.length()-(prettyName.length()+1));
    print("", "OS", name+" "+uname_info.machine);
}


// The host
void host()
{
    string name, version;
    std::ifstream infile;

    infile.open("/sys/devices/virtual/dmi/id/product_name");
    if(!(infile.is_open())) __ABORT__
    getline(infile, name);
    infile.close();

    infile.open("/sys/devices/virtual/dmi/id/product_version");
    if(!(infile.is_open())) __ABORT__
    getline(infile, version);
    infile.close();

    print("", "Host", name+" "+version);
}


// Kernel
void kernel() { print("", "Kernel", uname_info.release); }


// The shell name (bash, zsh, fish etc etc)
void shell() { print("", "Shell", getpwuid(geteuid())->pw_shell); }


// Available RAM
void ram()
{
    int mem_free = 0, mem_total = 0;

    std::ifstream infile;
    infile.open("/proc/meminfo");
    if(!(infile.is_open())) __ABORT__

    while(infile.good() and !(mem_free and mem_total))
    {
        string current_key;
        infile>>current_key;

        if(current_key == "MemTotal:")
            infile>>mem_total;

        if(current_key == "MemAvailable:")
            infile>>mem_free;
    }
    infile.close();

    string ram = std::to_string((mem_total - mem_free)/1024)
                 + "MiB /" + std::to_string(mem_total/1024) + "MiB";

    print("", "Mem", ram);
}


// Uptime
void uptime()
{
    string time;
    double uptime;

    std::ifstream infile;
    infile.open("/proc/uptime");
    if(!(infile.is_open())) __ABORT__
    infile>>uptime;
    infile.close();

    int days = floor(uptime/86400),
        hours = floor((uptime - days*86400)/3600),
        mins = floor((uptime - days*86400 - hours*3600)/60),
        secs = uptime - days*86400 - hours*3600 - mins*60;

    if(days)
    {
        if(days<=9) time+="0";
        time = time+std::to_string(days)+"d";
        if(days>1) time+="ays";
        time+=" ";
    }

    if(hours)
    {
        if(hours<=9) time+="0";
        time = time+std::to_string(hours)+"h";
        if(hours>1) time+="rs";
        time+=" ";
    }

    if(mins)
    {
        if(mins<=9) time+="0";
        time = time+std::to_string(mins)+"min";
        if(mins>1) time+="s";
        time+=" ";
    }

    if(secs)
    { 
        if(secs<=9) time+="0";
        time = time+std::to_string(secs)+"sec";
        if(secs>1) time+="s";
    }

    print("", "Uptime", time);
}


// Desktop environment / Window manager /  Whatever
void de()
{
    const char* desktop_session;
    if((desktop_session = std::getenv("XDG_CURRENT_DESKTOP")) or (desktop_session = std::getenv("DESKTOP_SESSION")))
        print("", "DE/WM", desktop_session);
    else
        cout<<endl;
}


// The number of packages installed in this sustem
void pkgs()
{
    string pkg;

    // dpkg
    if(std::filesystem::exists("/bin/dpkg"))
        pkg = pkg + exec("dpkg --get-selections | wc -l") + " (dpkg) ";

    // nix
    if(std::filesystem::exists("/nix"))
    {
        if(std::filesystem::exists("/etc/nix"))
            pkg = pkg + exec("nix-store --query --requisites /run/current-system | wc -l");
        else
            pkg = pkg + exec("nix-env -q | wc -l");

        pkg = pkg + " (nix) ";
    }

    // pacman
    if(std::filesystem::exists("/bin/pacman"))
        pkg = pkg + exec("pacman -Qq | wc -l") + " (pacman) ";

    // portage
    if(std::filesystem::exists("/bin/emerge"))
        pkg = pkg + exec("echo -n $(cd /var/db/pkg && ls -d */* | wc -l") + " (emerge) ";

    // rpm
    if(std::filesystem::exists("/var/lib/rpm"))
        pkg = pkg + exec("rpm -qa | wc -l") + " (rpm) ";
    
    // XBPS
    if(std::filesystem::exists("/bin/xbps-install"))
        pkg = pkg + exec("xbps-query -l | wc -l") + " (xbps) ";

    print("", "Pkgs", pkg);
}



// The screen resolution
void resolution()
{
    Display* disp = XOpenDisplay(NULL);
    if(!disp)
        __ABORT__

    Screen*  scrn = DefaultScreenOfDisplay(disp);
    int height = scrn->height;
    int width  = scrn->width;

    print("", "Res", std::to_string(width)+ "x" + std::to_string(height));
}



// CPU
void cpu()
{
    std::ifstream infile;
    infile.open("/proc/cpuinfo");
    string  modelname = "model name",
            cpu = "";

    if(!(infile.is_open())) __ABORT__

    while(infile.good() and cpu == "")
    {
        string curr_line;
        std::getline(infile,curr_line);
        
        if(curr_line.find(modelname)!=string::npos)
            cpu = curr_line;
    }

    infile.close();

    // Erase extra spaces
    cpu.erase(std::remove_if(cpu.begin(), cpu.end(), isspace), cpu.end());
    // Erase the "model name" string before the line
    cpu = cpu.substr(modelname.length(), cpu.length()-(modelname.length()));

    print("", "CPU", cpu);
}



// Print color bars
void colors_1()
{
    string s;

    for(int i = 30; i < 38; i++)
        s = s+"\e["+std::to_string(i)+"m⬤\e[0m ";

    cout<<string(stoi(conf["pregap"]), ' ')<<s<<endl;
}

void colors_2()
{
    string s;

    for(int i = 90; i < 98; i++)
        s = s+"\e["+std::to_string(i)+"m⬤\e[0m ";

    cout<<string(stoi(conf["pregap"]), ' ')<<s<<endl;
}
