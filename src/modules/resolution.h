void resolution()
{
    Display* disp = XOpenDisplay(NULL);
    if (!disp)
        __ABORT__

    Screen* scrn = DefaultScreenOfDisplay(disp);
    int height = scrn->height,
        width  = scrn->width;

    string res = std::to_string(width)+ "x" + std::to_string(height);
    print("", "Res", res);
}