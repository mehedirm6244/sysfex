std::map<string, string> config =
{
    // config_values[i].first = key
    // config_values[i].second = value
    { "pregap", "6" },
    { "gap", "10" },
    { "ascii", "1" },
    { "ascii_path", "/opt/sysfex/ascii/tux.txt" },
    { "ascii_beside_text", "1" },
    { "color_block", "⬤" },
    { "separator", ":" },
    { "bold_ascii", "1" },
    { "bold_text", "1" }
};

void config_setvalue(string key, string value)
{
    if (config.find(key)!=config.end())
        config[key] = value;
}

// The function which does the work with the config file
void init_config(string dir)
{
    if (!std::filesystem::exists(dir))
        return;

    std::ifstream config_file;
    config_file.open(dir);
    if (!(config_file.is_open()))
        return;

    while (config_file.good())
    {
        string curr;
        getline(config_file, curr);
        // Remove unnecessary spaces
        curr.erase(std::remove_if(curr.begin(), curr.end(), isspace), curr.end());

        // Lines starting with '#' will be considered as comments
        // Ignore the comments and empty lines
        if(curr[0]=='#' or curr.empty())
            continue;

        int delimiter = curr.find("=");
        string  key = curr.substr(0, delimiter),
                value = curr.substr(delimiter + 1);

        config_setvalue(key, value);
    }
}