#include "bulk_handlers.h"


void get_data(unsigned long long N, std::istream& is, std::ostream& os, std::ostream& es)
{
    Command cmd {N};

    cmd.add_hanlder(std::make_shared<WriteData>(es));
    cmd.add_hanlder(std::make_shared<PrintData>(os));

    for(std::string line; std::getline(is, line);){ 
        cmd.on_new_cmd(line);
    }
    cmd.on_cmd_end();
}


void prosess(const char* cin_str, std::istream& is = std::cin, std::ostream& os = std::cout, std::ostream& es = std::cerr)
{
    std::string str = cin_str;
    if(!std::all_of(str.begin(), str.end(), ::isdigit))
        throw std::invalid_argument("Invalid syntax. Block size must contain only decimal digits.");

    unsigned long long N = std::stoull (str);

    if(N == 0 )
        throw std::invalid_argument("Invalid block size. Block size must be > 0.");

    get_data(N, is, os, es);
}