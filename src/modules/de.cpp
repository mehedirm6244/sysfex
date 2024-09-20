/*

This file is from Sysfex, another system info fetching tool

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "modules/de.hpp"

std::string de() {
  const char *desktop_session;

  if ((desktop_session = std::getenv("XDG_CURRENT_DESKTOP")) or
      (desktop_session = std::getenv("DESKTOP_SESSION")) or
      (desktop_session = std::getenv("XDG_SESSION_DESKTOP")) or
      (desktop_session = std::getenv("CURRENT_DESKTOP")) or
      (desktop_session = std::getenv("SESSION_DESKTOP"))) {
    return desktop_session;
  }

  return "Unknown";
}
