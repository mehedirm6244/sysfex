void title()
{
    string host, user;

    user = std::getenv("USER");

    std::ifstream infile;
    infile.open("/proc/sys/kernel/hostname");
    if (!(infile.is_open()))
        __ABORT__
    infile>>host;
    infile.close();

    if (config.getvalue("ascii_beside_text")!="0")
        cout<<string(stoi(config.getvalue("pregap")), ' ');

    cout<<BOLD;

    if (config.getvalue("icons")!="0")
        cout<<"  ";
    cout<<user<<UBOLD;

    cout<<" on ";
    
    if (config.getvalue("icons")!="0")
        cout<<"  ";
    
    cout<<BOLD<<host<<UBOLD<<endl;
}