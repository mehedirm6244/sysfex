#define BOLD    "\033[1m"
#define UBOLD   "\033[0m"


void print(string key, string value)
{
    int key_size = 0;
    for (auto ch:key)
        key_size+=((ch & 0xc0)!=0x80);

    int gap = stoi(config["gap"]),
        pregap = stoi(config["pregap"]),
        remaining_space = std::max(1, gap-key_size);

    if (
        config["ascii_beside_text"]!="0" and
        config["ascii"]!="0"
        )
        cout<<string(pregap, ' ');

    if (config["bold_text"]!="0")
        cout<<BOLD<<key<<UBOLD;
    else
        cout<<key;

    if (value!="")
    {
        if (key!="")
        {
            cout<<string(remaining_space, ' ')
                <<config["separator"]<<" ";
        }
        cout<<value;
    }

    cout<<endl;
}


void help()
{
    config_setvalue("pregap", "0");
    config_setvalue("gap", "0");

    cout<<BOLD<<"Sysfex"<<UBOLD
        <<" - another fetch tool written in C++\n"<<endl;

    cout<<BOLD<<"Flags:"<<UBOLD<<endl;
    print("--help", "Print this screen");
    print("--ascii <value>", "If value == 0, don't print the ascii art, else do");
    print("--ascii-path <path-to-ascii>", "Specify the directory from where the ascii will be printed");
    print("--ascii-beside-txt <value>", "Choose whether the ascii will be printed beside info or not");
    print("--config <path-to-config>", "Specify the file which you want to be used as the config file");
    print("--info <path-to-printables>", "Specify the file from which info will be printed");
}


// Something which lets one to get the output of a command as a string
// I forgot where I collected this code from :( thanks anon
string exec(const char *input)
{
    std::unique_ptr<FILE, decltype(&pclose)> stream{popen(input, "r"), &pclose};
    string output;
    if (stream)
    {
        while (!feof(stream.get()))
        {
            auto offset = output.size();
            output.resize(output.size() + 256);

            if (fgets(output.data()+offset, output.size()-offset, stream.get()) == NULL)
                break;

            if (ferror(stream.get()))
            {
                output.resize(offset);
                break;
            }

            output.resize(std::distance(output.begin(), std::find(output.begin() + offset, output.end(), '\0') - 1));
        }
    }

    if (output.back()=='\n')
        output.pop_back();

    return output;
}
