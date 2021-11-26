void colors_dark()
{
    if (config.getvalue("ascii_beside_text")!="0")
        cout<<string(stoi(config.getvalue("pregap")), ' ');

    for (int i = 30; i < 38; i++)
        cout<<"\e["+std::to_string(i)+"m⬤\e[0m ";
    
    cout<<endl;
}

void colors_light()
{
    if (config.getvalue("ascii_beside_text")!="0")
        cout<<string(stoi(config.getvalue("pregap")), ' ');

    for (int i = 90; i < 98; i++)
        cout<<"\e["+std::to_string(i)+"m⬤\e[0m ";

    cout<<endl;
}