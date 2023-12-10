/***********************************************/
/* This file is a part of Sysfex               */
/* This function returns the screen resolution */
/* CURRENTLY THIS WORKS ON Xorg ONLY           */
/***********************************************/

#include <X11/Xlib.h> /* For getting display info on X11
                         Will add a workaround for wayland too */
#include "resolution.hpp"

std::string resolution() {
    Display *disp = XOpenDisplay(NULL);
    if (!disp) /* Return nothing if no display is detected
                to avoid possible segfaults */
        return "";

    Screen *scrn = DefaultScreenOfDisplay(disp);
    int height, width;
    height = scrn->height;
    width = scrn->width;

    std::string res = std::to_string(width) + "x" + std::to_string(height); /* 1366x768 */
    return res;
}