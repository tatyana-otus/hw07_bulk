#include <iostream>
#include <algorithm>
#include "debug_log.h"
#include <ctime>
#include <vector>


struct Handler
{
    virtual void get(const std::vector<std::string>&, const time_t t = 0) = 0;
};

struct Command {
    enum class Status { start, work };

    Command(size_t N_):N(N_){ data.reserve(N); };

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

    
    enum class BulkState {end, save, idle, drop};
    enum class CmdState {work, wait_for_sync};

    void check_state(const std::string& d)
    {
        BulkState blk_state = BulkState::idle;

        switch (cmd_state) {
            case CmdState::work:
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
                        cmd_state = CmdState::wait_for_sync;
                        blk_state = BulkState::drop;
                    }    
                }
                else if (d == "") {
                    if((cnt_braces != 0) && (b_satic == false))
                        blk_state = BulkState::drop;
                    else
                        blk_state = BulkState::end; 
                    cnt_braces = 0;
                    b_satic = true;
                }
                else {
                    if(data.empty())
                        time = std::time(nullptr);
                    blk_state = BulkState::save;
                }
                break;
            case CmdState::wait_for_sync:
                if (d == "") {
                    cnt_braces = 0;
                    b_satic = true;
                    cmd_state = CmdState::work;
                } 
                break;   
        }
        exec_state(blk_state, d);
    }


    void exec_state(BulkState state, const std::string& d) {

        switch(state) {

            case BulkState::end:
                handel_bulk();
                data.clear();
                break;

            case BulkState::save:                
                data.push_back(d);
                if((b_satic == true) && (data.size() == N)){
                    exec_state(BulkState::end, d);
                }
                break;  

            case BulkState::drop:
                data.clear();
                break; 

            case BulkState::idle:
                break;    
        }
    }

private:
    std::time_t time;
    std::vector<std::string> data;
    std::vector<Handler*> data_handler;
    bool b_satic = true;
    CmdState cmd_state = CmdState::work;

    int cnt_braces = 0;
    size_t N;
};