#include <iostream>
#include <algorithm>
#include "debug_log.h"
#include <ctime>
#include <vector>


struct Handler
{
    virtual void get(const std::vector<std::string>&, const time_t t = 0) = 0;

    void stream_out(const std::vector<std::string>& v, std::ostream& os)
    {
        os << "bulk: " << *v.cbegin();
        for (auto it = std::next(v.cbegin()); it != std::cend(v); ++it)
            os << ", " << *it ;       
    }
};

struct Command {
    enum class Status { start, work };

    Command(size_t N_):N(N_), b_satic(true), cnt_braces(0) { data.reserve(N); };

    void add_hanlder(Handler* h)
    {
        data_handler.push_back(h);
    }

    void handel_bulk()
    {
        if(!data.empty()) {
            for (auto h : data_handler) {
                h->get(data, time);
            } 
        }       
    }

    
    enum class BulkState {end, save, idle};

    void check_state(const std::string& d)
    {
        BulkState blk_state = BulkState::idle;

        if(d == "{") {
            if(b_satic == true){
                b_satic = false;
                blk_state = BulkState::end;
            } 
            ++cnt_braces;
        }
        else if (d == "}"){
            --cnt_braces;
            if(cnt_braces == 0) {
                b_satic = true;
                blk_state = BulkState::end;
            }
            else if(cnt_braces < 0){
                throw std::invalid_argument("wrong command stream");
            }    
        }
        else {
            if(data.empty())
                time = std::time(nullptr);
            data.push_back(d);
            blk_state = BulkState::save;
        }

        exec_state(blk_state);
    }


    void finish()
    {
        if(b_satic == true) {
            exec_state(BulkState::end);
        }
    }


    void exec_state(BulkState state) {

        switch(state) {

            case BulkState::end:
                handel_bulk();
                data.clear();
                break;

            case BulkState::save:                                
                if((b_satic == true) && (data.size() == N)){
                    exec_state(BulkState::end);
                }
                break;  

            case BulkState::idle:
                break;    
        }
    }

private:
    std::time_t time;
    std::vector<std::string> data;
    std::vector<Handler*> data_handler;
    size_t N;
    bool b_satic;
    int cnt_braces;
    
};