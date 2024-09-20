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

#include "sysfex.hpp"

int main(int argc, const char *argv[]) {
  Sysfex::import_config();

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--about") == 0) {
      Sysfex::about();
      return 0;
    }
    if (strcmp(argv[i], "--help") == 0) {
      Sysfex::help();
      return 0;
    }

    /* Flags requiring values should not be the last argument */
    if (i != argc - 1) {
      if (strcmp(argv[i], "--ascii") == 0) {
        Config::the()->set_property("ascii", argv[++i]);
      } else if (strcmp(argv[i], "--config") == 0) {
        Config::the()->init(argv[++i]);
      } else if (strcmp(argv[i], "--info") == 0) {
        Info::the()->init(argv[++i]);
      } else {
        std::cerr << sfUtils::parse_string(
          std::string("\\f_redInvalid flag: `") + argv[i] + "`\\reset\n",
          false
        );
        return 1;
      }
    } else {
      std::cout << sfUtils::parse_string("\\f_redInvalid format\n\\reset", false);
      Sysfex::help();
      return 1;
    }
  }

  Sysfex::run();
  return 0;
}