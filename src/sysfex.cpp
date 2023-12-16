/**********************************************************************/
/* Sysfex is just another system information fetching tool built for  */
/* linux based distributions, licenced under the GNU GPL-3.0 license  */
/* Github repository: https://github.com/mehedirm6244/sysfex          */
/**********************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <fstream>
#include <filesystem>
#include <algorithm>

/* Sysfex specific stuff */
#include "config.hpp"
#include "functions.hpp"
#include "shell_escape.hpp"
#include "info.hpp"

void importConfig();            /* Look for existing configs for sysfex */
void fetch();                   /* The heart of this program */


/************************************************/
/* Main function                                */
/* I don't think I need to write anything here  */
/************************************************/

int main(int argc, const char *argv[]) {
  /* Initialize user configuration before proceeding */
  importConfig();

  /*
    Check for user flags
    Flags are provided through the command line while running this program
  */
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--help")) {
      help();
      return 0;
    }

    if (i != argc - 1) {
      /*
        The following flags need values to work with sysfex --flag what_user_wants
        Hence the current flag MUST NOT be the last string of argv[]
      */

      if (!strcmp(argv[i], "--ascii")) {
        Config::the()->setValue("ascii", argv[++i]);
      } else if (!strcmp(argv[i], "--ascii-path")) {
        Config::the()->setValue("ascii_path", argv[++i]);
      } else if (!strcmp(argv[i], "--config")) {
        Config::the()->init(argv[++i]);
      } else if (!strcmp(argv[i], "--info")) {
        Info::the()->init(argv[++i]);
      } else if (!strcmp(argv[i], "--ascii-beside-txt")) {
        Config::the()->setValue("ascii_beside_text", argv[++i]);
      } else {
        std::cout << "No matching flag found called " << argv[i] << " !"
                  << "Run sysfex --help for listing all the available flags." << std::endl;
        return 1;
      }
    } else {
      std::cout << "Invalid command format!"
                << "Run sysfex --help for listing all the available flags.";
      return 1;
    }
  }

  fetch();
  return 0;
}


/**************************************************************/
/* This function looks for configuration files for sysfex     */
/* It will look into ${USER}/.config/sysfex first             */
/* If not found, then /opt/sysfex will be searched for        */
/* If still not found, then the hardcoded config will be used */
/**************************************************************/

void importConfig() {
  std::string user, localConfDir, fallbackDir;
  user = std::getenv("USER");                               /* User of current session
                                                               Needed for locating local config file */
  localConfDir = "/home/" + user + "/.config/sysfex/";      /* Path to be searched for local config file */
  fallbackDir = "/opt/sysfex/";                             /* To be searched for config if no local config exists */

  /*
    There are two types of config files for sysfex:
    config -> controls how stuffs will be shown i.e. gaps, bold text etc
    info -> controls what info to be shown i.e. OS Name, Screen resolution etc
  */

  /*
    If the directory for local config file itself doesn't exist,
    Then make that directory first. The fallback config will be
    copied to that directory before sysfex runs. Then the user can
    modify it according to their preference.

    This scenario is for when sysfex is ran for the first time, or
    your cat has messed up with your config files
  */
  if (!std::filesystem::exists(localConfDir)) {
    std::filesystem::create_directories(localConfDir);
  }

  /***************/
  /* CONFIG FILE */
  /***************/

  /* If a local config file exists, then use that */
  if (std::string localConf = localConfDir + "config"; std::filesystem::exists(localConf)) {
    Config::the()->init(localConf);
  } else if (std::filesystem::exists(fallbackDir + "config")) {   /* Else copy the fallback config file to the path of
                                                                     the local config file and use the local one (it exists now) */
    std::filesystem::copy_file(fallbackDir + "config", localConf);
    Config::the()->init(localConf);
  }
  /*
    NOTE THAT IF THE LOCAL CONFIG FILE AS WELL AS THE ONES STORED INSIDE
    /opt/sysfex IS MISSING, THEN IT'LL BE A TROUBLE. HOWEVER, THIS IS VERY
    UNLIKELY TO HAPPEN
  */

  /*************/
  /* INFO FILE */
  /*************/

  /* If a local info file exists, then use that */
  std::string localConf = localConfDir + "info";
  if (std::filesystem::exists(localConf)) {
    Info::the()->init(localConf);
  } else if (std::filesystem::exists(fallbackDir + "info")) {     /* Else copy the fallback info file to the path of
                                                                     the local info file and use the local one */
    std::filesystem::copy_file(fallbackDir + "info", localConf);
    Info::the()->init(localConf);
  }
  /*
    NOTE THAT IF NEITHER ~/.config/sysfex/info NOR /opt/sysfex/info
    EXISTS, THEN NO INFORMATION WILL BE PRINTED, ONLY ASCII WILL BE
    SHOWN. THIS IS UNLIKELY TO HAPPEN
  */
}


/**************************************************/
/* This is the heart of this program              */
/* As we now have our configuration files ready,  */
/* we can now print them just like we want        */
/* This function does exactly that                */
/**************************************************/

void fetch() {
  size_t maxLineLength = 0; /* Length of the longest line of the ascii file */
  /* Print the ASCII text/image unless forbidden to do so */
  if (Config::the()->getValue("ascii") != "0") {
    std::string asciiPath = Config::the()->getValue("ascii_path");

    std::ifstream infile;
    infile.open(asciiPath);
    if (infile.is_open()) {
      std::pair<std::string, int> asciiArt[64]; /* asciiArt[i].first to store the i-th line of the ascii
                                                   asciiArt[i].second to store the length of the i-th line */

      int currentLineIndex = 0; /* Current line count of the ascii */

      while (infile.good() and currentLineIndex < 64) { /* No sane person is having an ascii over 64 lines*/
        std::string currentLine;
        std::getline(infile, currentLine);
        size_t currentLineLength = getLineWidth(currentLine);

        if (Config::the()->getValue("bold_ascii") != "0") { /* Use bold font for showing ASCII unless forbidden */
          currentLine = BOLD + currentLine + UBOLD;
        }

        maxLineLength = std::max(maxLineLength, currentLineLength);
        asciiArt[currentLineIndex] = {currentLine, currentLineLength};
        currentLineIndex++;

        if (Config::the()->getValue("ascii_beside_text") == "0") { /* Print the ascii first if ascii_beside_text not equals 0
                                                                      Thus ASCII will be printed first, then the info */
          std::cout << currentLine << std::endl;
          continue;
        }
      }

      infile.close();

      /****************/
      /* PRINT STUFFS */
      /****************/

      for (int i = 0; i < currentLineIndex; i++) {
        std::string currentLine = asciiArt[i].first;
        int currentLineLength = asciiArt[i].second;

        if (Config::the()->getValue("ascii_beside_text") != "0") { /* Do not print the ascii stuff if already done so */
          std::cout << currentLine << std::string(maxLineLength - currentLineLength, ' ');
        }

        /* Print info as long as there's any */
        if (Info::the()->getCurrentInfo() < Info::the()->getInfoSize()) {
          print(Info::the()->getInfos()[Info::the()->getCurrentInfo()].first, Info::the()->getInfos()[Info::the()->getCurrentInfo()].second); /* print(key, info) */
          Info::the()->setCurrentInfo(Info::the()->getCurrentInfo() + 1);
        } else {
          std::cout << std::endl;
        }
      }
    }
  }

  /* If reading the file is over but there are still info to print */
  for (int i = Info::the()->getCurrentInfo(); i < Info::the()->getInfoSize(); i++) {
    if (Config::the()->getValue("ascii") != "0" and Config::the()->getValue("ascii_beside_text") != "0") {
      std::cout << std::string(maxLineLength, ' ');
    }

    print(Info::the()->getInfos()[i].first, Info::the()->getInfos()[i].second); /* print(key, info) */
  }
}