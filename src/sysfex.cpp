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
#include <filesystem>
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


void newline() { cout<<endl; }


int main(int argc, const char* argv[])
{
    // Read the configurations
    init_config();

    // The informations which will be displayed
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
        *(newline),
        *(ram),
        *(uptime),
        *(resolution),
        *(newline),
        *(cpu)
    };
    int current_func = 0;

    // Abort the process if utsname.h doesn't exist
    if(uname(&uname_info))
        throw std::runtime_error("Failed to access utsname.h :(");

    // Do this when an arguement for a flag is not provided
    #define _ARGUEMENT_NOT_PROVIDED_ \
    { \
        cout<<"You must provide an arguement!"<<endl; \
        return 1; \
    }

    // Flags
    for(int i=1; i<argc; i++)
    {
        if(!(strcmp(argv[i],"--help")))
        {
            help();
            return 0;
        }

        // They are self-explanatory, I guess
        
        else if(!(strcmp(argv[i],"--ascii")))
        {
            if(i!=argc-1)
                conf["ascii"] = argv[++i];
            else
                _ARGUEMENT_NOT_PROVIDED_
        }

        else if(!(strcmp(argv[i], "--ascii-dir")))
        {
            if(i!=argc-1)
                conf["ascii_dir"] = argv[++i];
            else
                _ARGUEMENT_NOT_PROVIDED_
        }

        else if(!(strcmp(argv[i], "--icons")))
        {
            if(i!=argc-1)
                conf["icons"] = argv[++i];
            else
                _ARGUEMENT_NOT_PROVIDED_
        }

        else
        {
            cout<<"Incorrect command"<<endl;
            return 1;
        }
    }

    cout<<endl;

    int max_line_len = 0;
    // The number of functions to be printed
    int func_size = sizeof(funcs)/sizeof(funcs[0]);

    if(conf["ascii"]!="0")
    {
        /*
            If the program is said to print both the ascii text and
            system informations, it'll do so.

            In the i-th line of output, it'll first print the i-th
            line of the ascii text (if there's any), then print necessary
            amount of whitespaces and then print the i-th system information
            defined in void(*funcs[])()) on the 34th line
        */

        /*
            The directory from where it'll print the ascii word from
            By default, there are 26 txt files, named from a-z (.txt)
            By default, sysfex will print the first character of the
            username.
            Example: it'll print c for cakemeow
        */

        string ascii_dir = conf["ascii_dir"];

        // Open the file
        std::ifstream infile;
        infile.open(ascii_dir);

        /*
            If the file is opened (which means the file exists), print
            whatever's inside. Else, show an error message
        */
        
        if(infile.is_open())
        {
            // The length of the biggest line of the file
            // I need a bit help here... 
            max_line_len = stoi(exec(("wc -L " + ascii_dir).c_str()));

            while(infile.good())
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

                /*
                    Print whitespaces after the line so that the texts
                    after it look aligned
                */
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
        else
            cout<<"ASCII file directory not found.\n\n";
    }

    // If reading the file is over but there are still infos to print
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
