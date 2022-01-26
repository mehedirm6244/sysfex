string colors_dark()
{
    string  s,
            color_block = config["color_block"];

    for (int i = 30; i < 38; i++)
        s+="\e["+std::to_string(i)+"m"+color_block+"\e[0m ";
    
    return s;
}

string colors_light()
{
    string  s,
            color_block = config["color_block"];

    for (int i = 90; i < 98; i++)
        s+="\e["+std::to_string(i)+"m"+color_block+"\e[0m ";

    return s;
}