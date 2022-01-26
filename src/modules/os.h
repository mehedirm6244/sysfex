string os()
{
    string  name = "",
            prettyName = "PRETTY_NAME=\"";

    std::ifstream infile;
    infile.open("/etc/os-release");
    if (!(infile.is_open()))
        return "";

    while (infile.good())
    {
        std::getline(infile, name);
        if (name.find(prettyName)!=string::npos)
            break;
    }
    infile.close();

    if(name=="")
        return "";

    // Remove "PRETTY_NAME" and stuffs from the string
    name = name.substr(
            prettyName.length(),
            name.length() - (prettyName.length()+1)
            );

    return name;
}