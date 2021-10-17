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