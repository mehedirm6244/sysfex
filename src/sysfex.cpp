#include <iostream>
#include <cmath>
#include <string.h>
#include <map>
#include <fstream>
#include <filesystem>
#include <algorithm>
// For getting display info
#include <X11/Xlib.h>


using std::cin;
using std::cout;
using std::endl;
using std::string;


#include "config.h"
#include "functions.h"
#include "modules.h"
#include "info.h"


void fetch();


int main(int argc, const char* argv[])
{
    const string user = std::getenv("USER");

    if (
        string confdir = "/home/"+user+"/.config/sysfex";
        !(std::filesystem::exists(confdir))
        )
        system(("mkdir "+confdir).c_str());

    // Read configurations
    // If a local config file exists then use that
    if (
        string dir = "/home/"+user+"/.config/sysfex/config";
        std::filesystem::exists(dir)
        )
        init_config(dir);

    // Else use the global one
    else if (
            string fallback_dir = "/opt/sysfex/config";
            std::filesystem::exists(fallback_dir)
            )
        {
            // And copy it to local directory
            system(("cp "+fallback_dir+" "+dir).c_str());
            init_config(dir);
        }
    /*
        If /opt/sysfex/config doesn't exist,
        then the hardcoded configs will be used :)
    */

    // Read which infos will be printed
    // Same as config
    if (
        string dir = "/home/"+user+"/.config/sysfex/info";
        std::filesystem::exists(dir)
        )
        init_info(dir);
    else if (
        string fallback_dir = "/opt/sysfex/info";
        std::filesystem::exists(fallback_dir)
        )
        {
            system(("cp "+fallback_dir+" "+dir).c_str());
            init_info(dir);
        }
    /*
        Note that if there's neither ~/.config/sysfex/info
        nor /opt/sysfex/info , no information will be
        printed
    */

    // Do this when an arguement for a flag is not provided
    #define __ARGUEMENT_NOT_PROVIDED__ \
    { \
        cout<<"You must provide an arguement!"<<endl; \
        return 1; \
    }

    // Flags
    for (int i=1; i<argc; i++)
    {
        if (!(strcmp(argv[i], "--help")))
        {
            help();
            return 0;
        }

        else if (!(strcmp(argv[i], "--ascii")))
        {
            if (i!=argc-1)
                config_setvalue("ascii", argv[++i]);
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--ascii-path")))
        {
            if (i!=argc-1)
                config_setvalue("ascii_path", argv[++i]);
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--config")))
        {
            if (i!=argc-1)
                init_config(argv[++i]);
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--info")))
        {
            if (i!=argc-1)
                init_info(argv[++i]);
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--ascii-beside-txt")))
        {
            if (i!=argc-1)
                config_setvalue("ascii_beside_text", argv[++i]);
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else
        {
            cout<<"Invalid command"<<endl;
            help();
            return 1;
        }
    }

    fetch();
    return 0;
}


void fetch()
{
    // Length of the longest line of the ascii file
    int max_line_len = 0;

    if (config["ascii"]!="0")
    {
        // Path to the ascii file
        string ascii_path = config["ascii_path"];

        std::ifstream infile;
        infile.open(ascii_path);
        if (infile.is_open())
        {
            // The i-th line of the ascii will be stored at ascii_art[i].first
            // The length of the i-th line will be stored at ascii_art[i].second
            std::pair <string, int> ascii_art[64];

            // Current line count of the ascii
            int curr_line_idx = 0;

            while (infile.good() and curr_line_idx<64)
            {
                string curr_line;
                std::getline(infile, curr_line);

                // Don't use size() as there can be fullwidth characters
                // Need a bit help here about fullwidth chars
                int curr_line_len = 0;
                for (auto ch:curr_line)
                    curr_line_len+=((ch & 0xc0)!=0x80);

                if (config["bold_ascii"]!="0")
                    curr_line = BOLD + curr_line + UBOLD;

                max_line_len = std::max(max_line_len, curr_line_len);
                ascii_art[curr_line_idx] = { curr_line, curr_line_len };
                curr_line_idx++;

                // Print the ascii first if ascii_beside_text == 0
                if (config["ascii_beside_text"]=="0")
                {
                    cout<<curr_line<<endl;
                    continue;
                }
            }

            infile.close();

            // Print stuffs
            for (int i=0; i<curr_line_idx; i++)
            {
                string curr_line = ascii_art[i].first;
                int curr_line_len = ascii_art[i].second;

                //Don't print the ascii stuff if it has been already printed
                if (config["ascii_beside_text"]!="0")
                    cout<<curr_line
                        <<string(max_line_len-curr_line_len, ' ');

                // Print info as long as there's any
                if (curr_info<info_size)
                {
                    string  key = infos[curr_info].first,
                            info = infos[curr_info].second;
                    print(key, info);
                    curr_info++;
                }
                else
                    cout<<endl;
            }
        }
    }

    // If reading the file is over but there are still info to print
    for (int i=curr_info; i<info_size; i++)
    {
        if (
            config["ascii"]!="0" and
            config["ascii_beside_text"]!="0"
            )
            cout<<string(max_line_len, ' ');

        string  key = infos[i].first,
                info = infos[i].second;
        print(key, info);
    }
}