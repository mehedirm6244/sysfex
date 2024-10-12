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

#include <array>
#include <cstdlib>

std::string de() {
  constexpr std::array<const char*, 5> env_vars = {
    "XDG_CURRENT_DESKTOP",
    "DESKTOP_SESSION",
    "XDG_SESSION_DESKTOP",
    "CURRENT_DESKTOP",
    "SESSION_DESKTOP"
  };

  for (const char* var : env_vars) {
    if (const char *desktop_session = std::getenv(var)) {
      return std::string(desktop_session);
    }
  }

  return "Unknown";
}
