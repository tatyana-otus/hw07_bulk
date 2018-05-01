#include "command.h"


struct WriteData : public Handler {

    WriteData(Command *cmd)
    {
        cmd->add_hanlder(this);
    }

    void get(const std::vector<std::string>& data, const time_t t = 0) override
    {
        std::string file_name = "bulk" + std::to_string(t) + ".log";
        std::cout << file_name << " ";
        for(auto v : data) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }    
};

struct PrintData : public Handler {

    PrintData(Command *cmd, std::ostream& os_ = std::cout):os(os_)
    {
        cmd->add_hanlder(this);
    }

    void get(const std::vector<std::string>& v, const time_t t = 0) override
    {
        os << "bulk: " << *v.cbegin();
        for (auto it = std::next(v.cbegin()); it != std::cend(v); ++it)
            os << ", " << *it ;
        os << "\n";
    } 
    
private:
    std::ostream& os;
};