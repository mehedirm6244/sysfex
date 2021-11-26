#include <sys/utsname.h>
#include <iostream>
#include <cmath>
#include <string.h>
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
#include "printables.h"


void fetch();


int main(int argc, const char* argv[])
{
    const string user = std::getenv("USER");

    if (string confdir = "/home/"+user+"/.config/sysfex"; !(std::filesystem::exists(confdir)))
        system(("mkdir "+confdir).c_str());

    // Read configurations
    // If a local config file exists then use that
    if (string dir = "/home/"+user+"/.config/sysfex/config"; std::filesystem::exists(dir))
        init_config(dir);
    // Else use the global one
    else
        if (string fallback_dir = "/opt/sysfex/config"; std::filesystem::exists(fallback_dir))
        {
            // And copy it to local directory
            system(("cp "+fallback_dir+" "+dir).c_str());
            init_config(dir);
        }
    /*
        If the fallback directory (/opt/sysfex/config) doesn't exist,
        then the hardcoded configs will be used :)
    */

    // Read which infos will be printed
    // Same as config
    if (string dir = "/home/"+user+"/.config/sysfex/printables"; std::filesystem::exists(dir))
        init_printables(dir);
    else
        if (string fallback_dir = "/opt/sysfex/printables"; std::filesystem::exists(fallback_dir))
        {
            system(("cp "+fallback_dir+" "+dir).c_str());
            init_printables(dir);
        }

    // Abort the process if utsname.h doesn't exist
    if (uname(&uname_info))
        throw std::runtime_error("utsname.h not found. Aborting... :(");

    // Do this when an arguement for a flag is not provided
    #define __ARGUEMENT_NOT_PROVIDED__ \
    { \
        cout<<"You must provide an arguement!"<<endl; \
        return 1; \
    }

    // Flags
    for (int i=1; i<argc; i++)
    {
        if (!(strcmp(argv[i],"--help")))
        {
            help();
            return 0;
        }

        else if (!(strcmp(argv[i],"--ascii")))
        {
            if (i!=argc-1) config.setvalue("ascii", argv[++i]);
            else __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--ascii-dir")))
        {
            if (i!=argc-1) config.setvalue("ascii_dir", argv[++i]);
            else __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--icons")))
        {
            if (i!=argc-1) config.setvalue("icons", argv[++i]);
            else __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--config")))
        {
            if (i!=argc-1) init_config(argv[++i]);
            else __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--printables")))
        {
            if (i!=argc-1) init_printables(argv[++i]);
            else __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--printables")))
        {
            if (i!=argc-1) init_printables(argv[++i]);
            else __ARGUEMENT_NOT_PROVIDED__
        }

        else if (!(strcmp(argv[i], "--ascii-beside-txt")))
        {
            if (i!=argc-1) config.setvalue("ascii_beside_text", argv[++i]);
            else __ARGUEMENT_NOT_PROVIDED__
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
    cout<<endl;

    // The length of the longest line of the ascii art
    int max_line_len = 0;

    if (config.getvalue("ascii")!="0")
    {
        // The file from where it'll print the ascii word from
        string ascii_dir = config.getvalue("ascii_dir");

        std::ifstream infile;
        infile.open(ascii_dir);
        if (infile.is_open())
        {
            // Store the ascii file inside a struct[], line by line
            struct Ascii_art
            {
                string curr_line; // The current line
                int curr_line_len; // The length of the current line, will be needed later
            };

            // Who'd want to use an ascii-art which has over 64 lines?
            struct Ascii_art ascii_art[64];

            // The current line of the ascii art file
            int string_idx = 0;

            while (infile.good() and string_idx<64)
            {
                string curr_line;
                std::getline(infile, curr_line);

                // Print the ascii art first if ascii_beside_text == 0
                if (config.getvalue("ascii_beside_text")=="0")
                {
                    cout<<BOLD<<curr_line<<UBOLD<<endl;
                    continue;
                }

                // Get the length of the current line
                // Don't use size() as there can be unicode characters                
                int curr_line_len = 0;
                for (auto ch:curr_line)
                    curr_line_len+=((ch & 0xc0)!=0x80);

                max_line_len = std::max(max_line_len, curr_line_len);
                ascii_art[string_idx].curr_line = curr_line;
                ascii_art[string_idx].curr_line_len = curr_line_len;
                string_idx++;
            }

            infile.close();

            // Print stuffs
            for (int i=0; i<string_idx; i++)
            {
                string curr_line = ascii_art[i].curr_line;
                int curr_line_len = ascii_art[i].curr_line_len;

                //Don't print the ascii stuff if it has been already printed
                if (config.getvalue("ascii_beside_text")!="0")
                {
                    cout<<string(3, ' ');
                    cout<<BOLD<<curr_line<<UBOLD;
                    cout<<string(max_line_len-curr_line_len, ' ');
                }

                // Print info as long as there's any
                if (current_func<func_size)
                {
                    funcs[current_func]();
                    current_func++;
                }
                else
                    cout<<endl;
            }
        }
    }

    // If reading the file is over but there are still info to print
    for (int i=current_func; i<func_size; i++)
    {
        if (config.getvalue("ascii")!="0")
            cout<<string(3, ' ')<<string(max_line_len, ' ');

        funcs[i]();
    }

    cout<<endl;

}