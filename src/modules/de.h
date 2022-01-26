string de()
{
    const char* desktop_session;

    if (
        (desktop_session = std::getenv("XDG_CURRENT_DESKTOP")) or
        (desktop_session = std::getenv("DESKTOP_SESSION")) or
        (desktop_session = std::getenv("XDG_SESSION_DESKTOP")) or
        (desktop_session = std::getenv("CURRENT_DESKTOP")) or
        (desktop_session = std::getenv("SESSION_DESKTOP"))
    )
        return string(desktop_session);

    return "";
}