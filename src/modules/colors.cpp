/*************************************************/
/* This file is a part of Sysfex                 */
/* This function returns color blocks, that's it */
/*************************************************/

#include "../config.hpp"
#include "colors.hpp"


std::string colors_dark() {
  std::string blockCharacter = Config::the()->getValue("color_block");
  std::string colorBlock;
  for (int i = 30; i < 38; i++) {
    colorBlock += "\e[" + std::to_string(i) + "m" + blockCharacter + "\e[0m ";
  }
  return colorBlock;
}

std::string colors_light() {
  std::string blockCharacter = Config::the()->getValue("color_block");
  std::string colorBlock;
  for (int i = 90; i < 98; i++) {
    colorBlock += "\e[" + std::to_string(i) + "m" + blockCharacter + "\e[0m ";
  }
  return colorBlock;
}