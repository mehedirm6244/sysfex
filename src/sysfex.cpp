/**********************************************************************/
/* Sysfex is just another system information fetching tool built for  */
/* linux based distributions, licenced under the GNU GPL-3.0 license  */
/* GitHub repository: https://github.com/mehedirm6244/Sysfex          */
/**********************************************************************/

#include <iostream>
#include <cstring>
#include <map>
#include <fstream>
#include <filesystem>
#include <algorithm>

/* Sysfex specific stuff */
#include "config.hpp"
#include "utils.hpp"
#include "shell_escape.hpp"
#include "info.hpp"

void importConfig();            /* Look for existing configs for Sysfex */
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
    which are provided through the command line while running this program
  */
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--help")) {
      help();
      return 0;
    }

    /*
      The following flags need values to work with
      Example: `sysfex --flag <value>`
      Hence these flags MUST NOT be the last string of argv[]
    */
    if (i != argc - 1) {
      if (!strcmp(argv[i], "--ascii-path")) {
        Config::the()->setValue("ascii_path", argv[++i]);
      } else if (!strcmp(argv[i], "--config")) {
        Config::the()->init(argv[++i]);
      } else if (!strcmp(argv[i], "--info")) {
        Info::the()->init(argv[++i]);
      } else {
        std::cout << RED << "No flag named " << argv[i] << " is available!" << RESET << '\n'
                  << "Run `sysfex --help` for listing all the available flags." << '\n';
        return 1;
      }
    } else {
      std::cout << RED << "Invalid command format!" << RESET << '\n'
                << "Run `sysfex --help` for listing all the available flags.";
      return 1;
    }
  }

  fetch();
  return 0;
}


/**************************************************************/
/* This function looks for configuration files for Sysfex     */
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
    There are two types of config files for Sysfex:
    config -> controls how stuffs will be shown i.e. gaps, separator etc.
    info -> controls what info to be shown i.e. OS Name, Screen resolution etc
  */

  /*
    If the directory for local config file itself doesn't exist,
    Then make that directory first. The fallback config will be
    copied to that directory before Sysfex runs. Then the user can
    modify it according to their preference.

    This scenario is for when Sysfex is run for the first time,
    or your cat has messed up with your config files
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
  size_t maxLineLength = 0, /* Length of the longest line of the ascii file */
         lineCount = 0,
         startingLine = 0,
         startingColumn = 0;

  if (Config::the()->getValue("clear_screen") != "0") {
    std::cout << "\033[2J";       /* Clear terminal window */
    try {
      startingLine = std::stoi(Config::the()->getValue("starting_line"));
      startingColumn = std::stoi(Config::the()->getValue("starting_column"));
    } catch(std::exception &e) {
      /* Do nothing */
    }
    std::cout << "\033[" << startingLine << ";H";       /* Move cursor to starting line */
  }

  /********************************/
  /* PRINT ASCII IF NOT FORBIDDEN */
  /********************************/
  if (Config::the()->getValue("ascii") != "0") {
    std::string asciiPath = Config::the()->getValue("ascii_path");

    std::ifstream infile;
    infile.open(asciiPath);
    if (infile.is_open()) {
      while (infile.good()) {
        std::string currentLine;
        std::getline(infile, currentLine);
        size_t currentLineLength = getLineWidth(currentLine);

        maxLineLength = std::max(maxLineLength, currentLineLength);
        std::cout << "\033[" << startingColumn << "C";        /* Bring cursor to starting column each time
                                                                 before printing a line of the ASCII */
        std::cout << process_escape(currentLine, false) << '\n';
        lineCount++;
      }

      infile.close();
    }
  } else {
    Config::the()->setValue("text_beside_ascii", "0");        /* Useless to keep "text_beside_ascii" = 1
                                                                 when "ascii" = 0 */
    Config::the()->setValue("pregap", "0");                   /* Same for "pregap" */
  }

  /****************/
  /* PRINT STUFFS */
  /****************/

  /*
    Move cursor to the first line if text_beside_ascii = 1
    The cursor will later be moved in such a way that the following
    outputs will be printed beside the ASCII without overlapping it
  */
  if (Config::the()->getValue("text_beside_ascii") == "1") {
    std::cout << "\033[" << lineCount << "A";
  }
  
  for (int i = 0; i < Info::the()->getInfoSize(); i++) {
    /*
      Move cursor in such a way such that
      the following outputs don't overlap the ASCII
    */
    if (Config::the()->getValue("text_beside_ascii") == "1") {
      int offset = maxLineLength + startingColumn +
                   stoi(Config::the()->getValue("pregap"));       /* Initial cursor position while printing
                                                                     information */
      if (Config::the()->getValue("ascii") != "0") {
        offset++;
      }
      std::cout << "\033[" << offset << "C";
    }

    /*
      There can be two types of output according to the info file
        info "key" "value"
        print "string"

      `print "string"` is equivalent to `info "key" ""`
    */

    /*
      Info::the()->getInfos()[i].first = "key"
      Info::the()->getInfos()[i].second = "value"
    */

    std::cout << process_escape(Info::the()->getInfos()[i].first, false);

    if (!Info::the()->getInfos()[i].second.empty()) {
      if (!Info::the()->getInfos()[i].first.empty()) {
        std::cout << std::string(stoi(Config::the()->getValue("gap")), ' ');
      }
      std::cout << process_escape(Info::the()->getInfos()[i].second, false);
    }

    std::cout << '\n';
  }

  /*
    If the ASCII contains more lines than what have already
    been printed, then the ASCII will get cut off because of the
    position of the cursor. To prevent that, shift the cursor
    to a few cell bottom
  */
  if (lineCount > Info::the()->getInfoSize() and
      Config::the()->getValue("text_beside_ascii") == "1") {
    std::cout << "\033[" << lineCount - Info::the()->getInfoSize() - 1 << "B";
  }
}