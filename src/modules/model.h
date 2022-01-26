string model()
{
    string name, version;
    std::ifstream infile;

    infile.open("/sys/devices/virtual/dmi/id/product_name");
    if (!(infile.is_open()))
        return "";
    getline(infile, name);
    infile.close();

    infile.open("/sys/devices/virtual/dmi/id/product_version");
    if (!(infile.is_open()))
        return "";
    getline(infile, version);
    infile.close();

    string s = name+" "+version;
    return s;
}