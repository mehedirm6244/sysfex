void cpu()
{
    std::ifstream infile;
    infile.open("/proc/cpuinfo");
    string  modelname = "model name",
            cpu = "";

    if (!(infile.is_open()))
        __ABORT__

    while (infile.good() and cpu == "")
    {
        string curr_line;
        std::getline(infile,curr_line);
        
        if(curr_line.find(modelname)!=string::npos)
            cpu = curr_line;
    }

    infile.close();

    if(cpu=="")
        __ABORT__

    // Erase extra spaces
    cpu.erase(std::remove_if(cpu.begin(), cpu.end(), isspace), cpu.end());
    // Erase the "model name" string before the line
    cpu = cpu.substr(modelname.length(), cpu.length()-(modelname.length()));

    print("", "CPU", cpu);
}