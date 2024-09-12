#include <X11/Xlib.h> // TODO: Add support for Wayland
#include <sstream>

#include <modules/resolution.hpp>

std::string resolution() {
  Display *disp = XOpenDisplay(nullptr);
  Screen *scrn = DefaultScreenOfDisplay(disp);

  if (!disp) {
    XCloseDisplay(disp);
    return "";
  }

  int height = scrn->height;
  int width = scrn->width;

  XCloseDisplay(disp);

  std::ostringstream output;
  output << width << "x" << height;

  return output.str();
}
