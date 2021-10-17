// Printables stuffs
namespace Printable
{
    struct pPair
    {
        string key;
        void(*func)();
    };

    // Available informations
    #define PRINTABLES_SIZE 14
    struct pPair printables[PRINTABLES_SIZE]
    {
        { "title" , *(title) },
        { "newline" , *(newline) },
        { "host" , *(host) },
        { "os" , *(os) },
        { "kernel" , *(kernel) },
        { "pkgs" , *(pkgs) },
        { "shell" , *(shell) },
        { "de" , *(de) },
        { "ram" , *(ram) },
        { "uptime" , *(uptime) },
        { "resolution" , *(resolution) },
        { "cpu" , *(cpu) },
        { "colors_1" , *(colors_1) },
        { "colors_2" , *(colors_2) }
    };

    int find(string name)
    {
        int idx = -1;
        for(int i=0; i<PRINTABLES_SIZE; i++)
            if(printables[i].key == name)
            {
                idx = i;
                break;
            }

        return idx;
    }

    auto show_info(string name)
    {
        int idx = find(name);
        return *(printables[idx].func);
    }
}

void(*funcs[64])();
int func_size = 0,
    current_func = 0;

void init_printables(string dir)
{
    // If the function is already used before (i.e. the func() already has something, override)
    if(func_size)
        func_size = 0;

    // Get what's inside /opt/sysfex/printables
    if(std::filesystem::exists(dir))
    {
        std::ifstream printables;
        printables.open(dir);

        while(printables.good())
        {
            string name;
            printables>>name;
            if(name[0]==';')
            {
                getline(printables, name);
                continue;
            }

            if(Printable::find(name)!=-1)
            {
                funcs[func_size] = Printable::show_info(name);
                func_size++;
            }

            if(func_size>=64)
                break;
        }
    }
}