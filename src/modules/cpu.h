string cpu()
{
    std::ifstream infile;
    infile.open("/proc/cpuinfo");
    string  modelname = "model name",
            cpu = "";

    if (!(infile.is_open()))
        return "";

    while (infile.good() and cpu == "")
    {
        string curr_line;
        std::getline(infile,curr_line);
        
        if(curr_line.find(modelname)!=string::npos)
            cpu = curr_line;
    }

    infile.close();

    if(cpu=="")
        return "";

    // Erase extra spaces
    cpu.erase(std::remove_if(cpu.begin(), cpu.end(), isspace), cpu.end());
    // Erase the "model name" string before the line
    cpu = cpu.substr(modelname.length(), cpu.length()-(modelname.length()));
    // Remove clock speed
    if (
        size_t pos = cpu.find('@');
        pos != string::npos
        )
        cpu = cpu.substr(0, pos);

    return cpu;
}