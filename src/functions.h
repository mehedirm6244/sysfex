#define BOLD    "\033[1m"
#define UBOLD   "\033[0m"


// Config stuffs
struct Config
{
    struct Pair { string key, value; };

    // The number of modifiable configs
    #define CONFIG_SIZE 6
    struct Pair config_values[CONFIG_SIZE]
    {
        { "pregap", "6" },
        { "gap", "10"},
        { "icon_gap", "3" },
        { "ascii", "1" },
        { "ascii_dir", "/opt/sysfex/ascii/tux.txt" },
        { "icons", "0" }
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
}


// Print line break
void newline() { cout<<endl; }


// Printing stuffs
void print(string icon, string key, auto value)
{
    int key_size = 0;
    for(auto ch:key)
        key_size+=((ch & 0xc0)!=0x80);

    int gap = stoi(config.getvalue("gap")),
        pregap = stoi(config.getvalue("pregap")),
        remaining_space = std::max(1,gap-key_size),
        icon_gap = stoi(config.getvalue("icon_gap"));

    cout<<string(pregap, ' ')<<BOLD;
    if(config.getvalue("icons")!="0")
        cout<<icon<<string(icon_gap + (icon==""), ' ');
    cout<<key<<UBOLD<<string(remaining_space, ' ')<<value<<endl;
}


// The help message
void help()
{
    cout<<BOLD<<"Sysfex"<<UBOLD<<" - another fetch tool written in mostly C++"<<endl;
    cout<<endl;
    cout<<BOLD<<"Available commands:"<<UBOLD<<endl;
    print("", "sysfex --help", "Print this screen");
    print("", "sysfex --ascii <value>", "If value == 0, don't print the ascii art, else do");
    print("", "sysfex --ascii-dir <path-to-ascii>", "Specify the file which you want to be shown as ascii-art");
    print("", "sysfex --icons <value>", "If value == 0, don't print font-icons beside informations, else do");
    print("", "sysfex --config <path-to-config>", "Specify the file which you want to be used as the config file");
}


// Something which lets one to get the output of a command as a string
string exec(const char *input)
{
    std::unique_ptr<FILE, decltype(&pclose)> stream{popen(input, "r"), &pclose};
    string output;
    if(stream)
    {
        while(!feof(stream.get()))
        {
            auto offset = output.size();
            output.resize(output.size() + 256);

            if(fgets(output.data()+offset, output.size()-offset, stream.get())==NULL)
                break;

            if (ferror(stream.get()))
            {
                output.resize(offset);
                break;
            }

            output.resize(std::distance(output.begin(), std::find(output.begin() + offset, output.end(), '\0') - 1));
        }
    }

    if(output.back()=='\n')
        output.pop_back();

    return output;
}