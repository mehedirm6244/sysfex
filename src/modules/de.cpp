/*************************************************************/
/* This file is a part of Sysfex                             */
/* This function returns the name of the desktop environment */
/*************************************************************/

#include <modules/de.hpp>

std::string de() {
  const char *desktop_session;

  /*
    We'll check for some environment variables for guessing the
    desktop environment or desktop session. This works for most
    of the famous DEs, however this will not work for all

    God please forgive me
  */
  if ((desktop_session = std::getenv("XDG_CURRENT_DESKTOP")) or
      (desktop_session = std::getenv("DESKTOP_SESSION")) or
      (desktop_session = std::getenv("XDG_SESSION_DESKTOP")) or
      (desktop_session = std::getenv("CURRENT_DESKTOP")) or
      (desktop_session = std::getenv("SESSION_DESKTOP"))) {
    return std::string(desktop_session);
  }

  return "";
}