#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <memory>

struct Handler
{
    virtual void on_bulk_resolved(const std::vector<std::string>&, const time_t t = 0) = 0;

    void stream_out(const std::vector<std::string>& v, std::ostream& os)
    {
        os << "bulk: " << *v.cbegin();
        for (auto it = std::next(v.cbegin()); it != std::cend(v); ++it)
            os << ", " << *it ;       
    }
};


struct Command {

    Command(size_t N_):N(N_), b_satic(true), cnt_braces(0)
    {
        data.reserve(N);
    }


    void add_hanlder(std::unique_ptr<Handler>&& h)
    {
        data_handler.push_back(std::move(h));
    }


    void on_bulk_created()
    {
        if(!data.empty()) {
            for (auto const& h : data_handler) {
                h->on_bulk_resolved(data, time);
            } 
        }       
    }

    
    enum class BulkState { end, save };

    void on_new_cmd(const std::string& d)
    {
        BulkState blk_state = BulkState::save;

        if(d == "{") {
            ++cnt_braces;
            if(b_satic == true){
                b_satic = false;
                blk_state = BulkState::end;
            }            
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
        }

        exec_state(blk_state);
    }


    void on_cmd_end()
    {
        if(b_satic == true) {
            exec_state(BulkState::end);
        }
    }


    void exec_state(BulkState state) {

        switch(state) {

            case BulkState::end:
                on_bulk_created();
                data.clear();
                break;

            case BulkState::save:
                if((b_satic == true) && (data.size() == N)){
                    exec_state(BulkState::end);
                }
                break;
        }
    }


    auto size()
    {
        return data.size();
    }

private:
    std::time_t time;
    std::vector<std::string> data;
    std::vector<std::unique_ptr<Handler>> data_handler;
    size_t N;
    bool b_satic;
    int cnt_braces;   
};