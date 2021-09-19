#include <sys/utsname.h>
#include <iostream>
#include <pwd.h>
#include <cmath>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
// For config stuffs
#include <map>
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
    init_config();

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

    // Abort the process if utsname.h doesn't exist
    if(uname(&uname_info))
        throw std::runtime_error("Failed to access utsname.h :(");

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
                conf["ascii"] = argv[++i];
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if(!(strcmp(argv[i], "--ascii-dir")))
        {
            if(i!=argc-1)
                conf["ascii_dir"] = argv[++i];
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else if(!(strcmp(argv[i], "--icons")))
        {
            if(i!=argc-1)
                conf["icons"] = argv[++i];
            else
                __ARGUEMENT_NOT_PROVIDED__
        }

        else
        {
            cout<<"Incorrect command"<<endl;
            help();
            return 1;
        }
    }

    cout<<endl;

    // The number of functions to be printed
    int func_size = sizeof(funcs)/sizeof(funcs[0]);
    // The length of the longest line of the ascii art
    int max_line_len = 0;

    if(conf["ascii"]!="0")
    {
        // The file from where it'll print the ascii word from
        string ascii_dir = conf["ascii_dir"];

        // Open the file
        std::ifstream infile;
        infile.open(ascii_dir);
        if(infile.is_open())
        {
            // We'll store the ascii file inside a string[], line by line
            int string_idx = 0;
            // Who'd use an ascii file with more than 64lines right?
            string ascii_art[64];
            // The length of each lines of the string
            int ascii_line_len[64];

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
                ascii_art[string_idx] = curr_line;
                ascii_line_len[string_idx] = curr_line_len;
                string_idx++;
            }

            infile.close();

            /*
                Now that we have the ascii art stored inside a string[]
                variable, let's print it
            */
            for(int i=0; i<string_idx; i++)
            {
                int curr_line_len = ascii_line_len[i];
                string curr_line = ascii_art[i];
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
    if(current_func<func_size)
        for(int i=current_func; i<func_size; i++)
        {
            if(conf["ascii"]=="1")
                cout<<string(3, ' ')<<string(max_line_len, ' ');

            funcs[i]();
        }

    cout<<endl;
    return 0;

    // And we're done :)
}
