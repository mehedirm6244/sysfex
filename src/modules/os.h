// The name of the linux distro

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