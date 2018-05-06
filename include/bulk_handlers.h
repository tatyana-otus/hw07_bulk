#include "command.h"
#include <fstream>


struct WriteData : public Handler
{
    WriteData(std::ostream& es_ = std::cout):es(es_) {}
   

    void on_bulk_resolved(const std::vector<std::string>& v, const time_t t = 0) override
    {
        std::string file_name = "bulk" + std::to_string(t) + ".log";

        if(!is_file_exist(file_name)){

            std::ofstream of{file_name};        

            stream_out(v, of);

            of.close();
        }
        else {
            es << "log file already exists" << std::endl;
        }    
    } 

    private:

    std::ostream& es;    
    
    bool is_file_exist(std::string file_name) 
    {
        std::ifstream file;
        file.open(file_name, std::fstream::in);
        if(file) {
            file.close();
            return true;
        }
        return false;
    }     
};


struct PrintData : public Handler
{
    PrintData(std::ostream& os_ = std::cout):os(os_) {}
   

    void on_bulk_resolved(const std::vector<std::string>& v, const time_t t = 0) override
    {
        stream_out(v, os);
        os << std::endl;
    } 
    
private:
    std::ostream& os;
};