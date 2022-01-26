string ram()
{
    int mem_free = 0,
        mem_total = 0;

    std::ifstream infile;
    infile.open("/proc/meminfo");
    if (!(infile.is_open()))
        return "";

    while (infile.good() and !(mem_free and mem_total))
    {
        string current_key;
        infile>>current_key;

        if (current_key == "MemTotal:")
            infile>>mem_total;

        if (current_key == "MemAvailable:")
            infile>>mem_free;
    }
    infile.close();

    string ram = std::to_string((mem_total - mem_free)/1024)
                 + "MiB /" + std::to_string(mem_total/1024) + "MiB";

    return ram;
}