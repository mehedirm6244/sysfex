// Config stuffs
struct Config
{
    struct Pair { string key, value; };

    // The number of modifiable configs
    #define CONFIG_SIZE 7
    struct Pair config_values[CONFIG_SIZE]
    {
        { "pregap", "6" },
        { "gap", "10"},
        { "icon_gap", "3" },
        { "ascii", "1" },
        { "ascii_dir", "/opt/sysfex/ascii/tux.txt" },
        { "icons", "0" },
        { "ascii_beside_text", "1" }
    };

    int find(string key);
    void setvalue(string key, string value);
    string getvalue(string key);
};

int Config::find(string key)
{
    for(int i=0; i<CONFIG_SIZE; i++)
        if(config_values[i].key == key)
            return i;

    return -1;
}

void Config::setvalue(string key, string value)
{
    int idx = find(key);
    if(idx==-1)
        return;

    config_values[idx].value = value;
}

string Config::getvalue(string key)
{
    int idx = find(key);
    if(idx==-1)
        return "0";

    return config_values[idx].value;
}

struct Config config;

// The function which does the work with the config file
void init_config(string dir)
{
    // If there's a config file on the given dir, then use that
    if(std::filesystem::exists(dir))
    {
        std::ifstream config_file;
        config_file.open(dir);
        if(!(config_file.is_open()))
            return;

        while(config_file.good())
        {
            string curr;
            getline(config_file, curr);
            // Remove unnecessary spaces
            curr.erase(std::remove_if(curr.begin(), curr.end(), isspace), curr.end());

            // Lines starting with ';' will be considered as comments
            // Ignore the comments and empty lines
            if(curr[0]==';' or curr.empty())
                continue;

            int delimiter = curr.find("=");
            string  key = curr.substr(0, delimiter),
                    value = curr.substr(delimiter + 1);

            config.setvalue(key, value);
        }
    }
    // Else what, the default config will be used
}