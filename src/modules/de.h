// Desktop environment / Window manager /  Whatever

void de()
{
    const char* desktop_session;
    if((desktop_session = std::getenv("XDG_CURRENT_DESKTOP")) or (desktop_session = std::getenv("DESKTOP_SESSION")))
        print("", "DE/WM", desktop_session);
    else
        cout<<endl;
}