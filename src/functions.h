#define BOLD    "\033[1m"
#define UBOLD   "\033[0m"


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


    if(config.getvalue("ascii_beside_text")!="0")
        cout<<string(pregap, ' ');

    cout<<BOLD;

    if(config.getvalue("icons")!="0")
        cout<<icon<<string(icon_gap + (icon==""), ' ');

    cout<<key<<UBOLD;
    cout<<string(remaining_space, ' ');
    cout<<value;
    cout<<endl;
}


void help()
{
    config.setvalue("pregap", "0");
    config.setvalue("gap", "0");
    cout<<BOLD<<"Sysfex"<<UBOLD<<" - another fetch tool written in mostly C++"<<endl;
    cout<<endl;
    cout<<BOLD<<"Flags:"<<UBOLD<<endl;
    print("", "--help", "Print this screen");
    print("", "--ascii <value>", "If value == 0, don't print the ascii art, else do");
    print("", "--ascii-dir <path-to-ascii>", "Specify the file which you want to be shown as ascii-art");
    print("", "--ascii-beside-txt <value>", "Choose whether ascii art will be printed beside infos or not");
    print("", "--icons <value>", "If value == 0, don't print font-icons beside informations, else do");
    print("", "--config <path-to-config>", "Specify the file which you want to be used as the config file");
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
