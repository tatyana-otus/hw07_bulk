#include "command.h"
#include <fstream>

struct WriteData : public Handler {

    WriteData(Command *cmd)
    {
        cmd->add_hanlder(this);
    }

    void get(const std::vector<std::string>& v, const time_t t = 0) override
    {
        std::string file_name = "bulk" + std::to_string(t) + ".log";

        std::ofstream of{file_name};

        stream_out(v, of);

        of.close();

    }    
};

struct PrintData : public Handler {

    PrintData(Command *cmd, std::ostream& os_ = std::cout):os(os_)
    {
        cmd->add_hanlder(this);
    }

    void get(const std::vector<std::string>& v, const time_t t = 0) override
    {
        stream_out(v, os);
        os << "\n";
    } 
    
private:
    std::ostream& os;
};