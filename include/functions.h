#include "bulk_handlers.h"


void get_data(unsigned long long N, std::istream& is, std::ostream& os)
{
    Command cmd {N};

    WriteData write_handler {&cmd};
    PrintData print_handler {&cmd, os};

    for(std::string line; std::getline(is, line);){ 
        cmd.check_state(line);
    }
}

void prosess(const char* cin_str, std::istream& is = std::cin, std::ostream& os = std::cout)
{
    std::string str = cin_str;
    if(!std::all_of(str.begin(), str.end(), ::isdigit))
        throw std::invalid_argument("Invalid syntax. Block size must contain only decimal digits.");

    unsigned long long N = std::stoull (str);

    if(N == 0 )
        throw std::invalid_argument("Invalid block size. Block size must be > 0.");

    get_data(N, is, os);

}