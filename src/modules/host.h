string host()
{
	string host;
	std::ifstream infile;
    infile.open("/proc/sys/kernel/hostname");
    if (!(infile.is_open()))
        return "";

    infile>>host;
    infile.close();

    return host;
}