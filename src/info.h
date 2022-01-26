const std::map <string, string(*)()> printables =
{
    { "host" , *(host) },
    { "os" , *(os) },
    { "kernel" , *(kernel) },
    { "pkgs" , *(pkgs) },
    { "shell" , *(shell) },
    { "model", *(model) },
    { "user", *(user) },
    { "de" , *(de) },
    { "ram" , *(ram) },
    { "uptime" , *(uptime) },
    { "resolution" , *(resolution) },
    { "cpu" , *(cpu) },
    { "colors_dark" , *(colors_dark) },
    { "colors_light" , *(colors_light) }
};

std::pair <string, string> infos[64];
int info_size, curr_info;

void init_info(string dir)
{
    curr_info = 0,
    info_size = 0;

    if (!(std::filesystem::exists(dir)))
        return;

    std::ifstream infile;
    infile.open(dir);

    while (infile.good())
    {
        string type, curr_line;
        infile>>type;
        getline(infile, curr_line);

        // Comment
        if (type[0]=='#')
            continue;

        int l = curr_line.find('"'),
            r = curr_line.find_last_of('"');

        if (
            l == string::npos or
            l == r
            )
            continue;


        if (type=="info")
        {
            string  key = curr_line.substr(l+1, r-(l+1)),
                    info = curr_line.substr(r+1, curr_line.back());

            // Erase extra spaces
            info.erase(
                std::remove_if(info.begin(), info.end(), isspace),
                info.end()
                );

            if (printables.find(info)==printables.end())
                continue;

            infos[info_size] = { key, (*printables[info])() };
            info_size++;
        }

        else if (type=="print")
        {
            curr_line = curr_line.substr(l+1, r-(l+1));
            infos[info_size] = { curr_line, "" };
            info_size++;
        }

        if(info_size>=64)
            break;
    }
}