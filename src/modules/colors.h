// Print color bars

void colors_1()
{
    string s;

    for(int i = 30; i < 38; i++)
        s = s+"\e["+std::to_string(i)+"m⬤\e[0m ";

    if(config.getvalue("ascii_beside_text")!="0")
        cout<<string(stoi(config.getvalue("pregap")), ' ');
    cout<<s<<endl;
}

void colors_2()
{
    string s;

    for(int i = 90; i < 98; i++)
        s = s+"\e["+std::to_string(i)+"m⬤\e[0m ";

    if(config.getvalue("ascii_beside_text")!="0")
        cout<<string(stoi(config.getvalue("pregap")), ' ');
    cout<<s<<endl;
}