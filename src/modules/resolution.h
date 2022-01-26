string resolution()
{
    Display* disp = XOpenDisplay(NULL);
    if (!disp)
        return "";

    Screen* scrn = DefaultScreenOfDisplay(disp);
    int height = scrn->height,
        width  = scrn->width;

    string res = std::to_string(width)+ "x" + std::to_string(height);
    return res;
}