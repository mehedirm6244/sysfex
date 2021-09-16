#define BOLD    "\033[1m"
#define UBOLD   "\033[0m"


// Map to store the configs
std::map<string, string> conf;


// Print line break
void newline() { cout<<endl; }


// Printing stuffs
void print(string icon, string key, auto value)
{
    int key_size = 0;
    for(auto ch:key)
        key_size+=((ch & 0xc0)!=0x80);

    int gap = stoi(conf["gap"]),
        pregap = stoi(conf["pregap"]),
        remaining_space = std::max(1,gap-key_size),
        icon_gap = stoi(conf["icon_gap"]);

    cout<<string(pregap, ' ')<<BOLD;
    if(conf["icons"]!="0")
        cout<<icon<<string(icon_gap + (icon==""), ' ');
    cout<<key<<UBOLD<<string(remaining_space, ' ')<<value<<endl;
}


// The function which does the work with the config file
void init_config()
{
    // First initialize the default values of stuffs

    conf["pregap"] = "6";
    conf["gap"] = "13";
    conf["icon_gap"] = "3";
    conf["ascii"] = "1";
    conf["ascii_dir"] = "/opt/sysfex/ascii/tux.txt";
    conf["icons"] = "0";


    // If there's a config file on /opt/sysfex/config, then use that
    if(std::filesystem::exists("/opt/sysfex/config"))
    {
        std::ifstream config;
        config.open("/opt/sysfex/config");
        if(!(config.is_open())) return;

        while(config.good())
        {
            string curr;
            getline(config, curr);
            curr.erase(std::remove_if(curr.begin(), curr.end(), isspace), curr.end());

            // Lines starting with ';' will be considered as comments
            // Ignore the comments and empty lines
            if(curr[0]==';' or curr.empty())
                continue;

            int delimiter = curr.find("=");
            string  name = curr.substr(0, delimiter),
                    value = curr.substr(delimiter + 1);

            conf[name] = value;
        }
    }
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