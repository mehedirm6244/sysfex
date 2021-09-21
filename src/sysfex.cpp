#include <sys/utsname.h>
#include <iostream>
#include <cmath>
#include <string.h>
#include <fstream>
#include <filesystem>
#include <algorithm>
// For screen information
#include <X11/Xlib.h>


using std::cin;
using std::cout;
using std::endl;
using std::string;


// All those functions and shits for this fetch
#include "functions.h"
#include "fetch_functions.h"


int main(int argc, const char* argv[])
{
    // Read the configurations
    /*
        By default, sysfex will look into /opt/sysfex/config for configurations
        You can specify a config file by using "sysfex --config <path_to_config>"

        And if you want that to be permanent, use your config path instead of
        "/opt/sysfex/config" as arguement in init_config()
    */
    init_config("/opt/sysfex/config");

    // Abort the process if utsname.h doesn't exist
    if(uname(&uname_info))
        throw std::runtime_error("utsname.h not found. Aborting... :(");

    // Do this when an arguement for a flag is not provided
    #define __ARGUEMENT_NOT_PROVIDED__ \
    { \
        cout<<"You must provide an arguement!"<<endl; \
        return 1; \
    }

    // Flags
    for(int i=1; i<argc; i++)
    {
        // They are self-explanatory, I guess

        if(!(strcmp(argv[i],"--help")))
        {
            help();
            return 0;
        }
        
        else if(!(strcmp(argv[i],"--ascii")))
        {
            if(i!=argc-1)
                config.setvalue("ascii", argv[++i]);
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if(!(strcmp(argv[i], "--ascii-dir")))
        {
            if(i!=argc-1)
                config.setvalue("ascii_dir", argv[++i]);
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if(!(strcmp(argv[i], "--icons")))
        {
            if(i!=argc-1)
                config.setvalue("icons", argv[++i]);
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if(!(strcmp(argv[i], "--config")))
        {
            if(i!=argc-1)
                init_config(argv[++i]);
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

    cout<<endl;

    // The informations which will be displayed
    // If you don't want any of these to be printed, simply comment it
    void(*funcs[])() =
    {
        *(title),
        *(newline),
        *(host),
        *(os),
        *(kernel),
        *(newline),
        *(pkgs),
        *(shell),
        *(de),
        *(newline),
        *(ram),
        *(uptime),
        *(resolution),
        *(newline),
        *(cpu),
        *(newline),
        *(colors_1),
        *(colors_2)
    };
    int current_func = 0;
    // The number of functions to be printed
    int func_size = sizeof(funcs)/sizeof(funcs[0]);

    // The length of the longest line of the ascii art
    int max_line_len = 0;

    if(config.getvalue("ascii")!="0")
    {
        // The file from where it'll print the ascii word from
        string ascii_dir = config.getvalue("ascii_dir");

        // Open the file
        std::ifstream infile;
        infile.open(ascii_dir);
        if(infile.is_open())
        {
            struct Ascii_art
            {
                string curr_line;
                int curr_line_len;
            };

            // Who'd use an ascii file with more than 64lines right
            // We'll store the ascii file inside a struct[], line by line
            struct Ascii_art ascii_art[64];
            int string_idx = 0;

            /*
                string_idx<64 is given because you may be naughty enough
                to print a whole essay instead of an ascii art
            */
            while(infile.good() and string_idx<64)
            {
                // Read the current line
                string curr_line;
                std::getline(infile, curr_line);

                // Get the length of the current line
                // Don't use curr_line.size() for the sake of humanity
                // As there can be unicode characters in the line too
                int curr_line_len = 0;
                for(auto ch:curr_line)
                    curr_line_len+=((ch & 0xc0)!=0x80);

                max_line_len = std::max(max_line_len, curr_line_len);
                ascii_art[string_idx].curr_line = curr_line;
                ascii_art[string_idx].curr_line_len = curr_line_len;
                string_idx++;
            }
            infile.close();

            /*
                Now that we have the ascii art stored inside a string[]
                variable, let's print it
            */
            for(int i=0; i<string_idx; i++)
            {
                int curr_line_len = ascii_art[i].curr_line_len;
                string curr_line = ascii_art[i].curr_line;
                cout<<string(3, ' ')<<BOLD<<curr_line<<UBOLD<<string(max_line_len-curr_line_len, ' ');

                // Print an information
                if(current_func<func_size)
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
    if(current_func<func_size-1)
        for(int i=current_func; i<func_size; i++)
        {
            if(config.getvalue("ascii")!="0")
                cout<<string(3, ' ')<<string(max_line_len, ' ');

            funcs[i]();
        }

    cout<<endl;
    return 0;

    // And we're done :)
}
