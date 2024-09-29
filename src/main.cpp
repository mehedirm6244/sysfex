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
#include <getopt.h>

int main(int argc, char *argv[]) {
  bool init_config = true;
  bool init_info = true;

  int opt = 0;
  int option_index = 0;
  const char *optstring = "-bha:C:i:";
  static const struct option opts[] = {
    {"about",  no_argument,       0, 'b'},
    {"help",   no_argument,       0, 'h'},
    {"ascii",  required_argument, 0, 'a'},
    {"config", required_argument, 0, 'C'},
    {"info",   required_argument, 0, 'i'},
    {0,0,0,0}
  };

  while ((opt = getopt_long(argc, argv, optstring, opts, &option_index)) != -1) {
    switch (opt) {
      case 0:
        break;
      case '?':
        std::cout << sfUtils::parse_string("\\f_redInvalid format\n\\reset", false);
        Sysfex::help();
        return 1;

      case 'b':
        Sysfex::about();
        return 0;

      case 'h':
        Sysfex::help();
        return 0;

      case 'a':
        Config::the()->set_property("ascii", optarg);
        break;

      case 'i':
        Info::the()->init(optarg);
        init_info = false;
        break;

      case 'C':
        Config::the()->init(optarg);
        init_config = false;
        break;
    }
  }

  Sysfex::import_config(init_config, init_info);
  Sysfex::run();
  return 0;
}
