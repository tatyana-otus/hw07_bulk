#pragma once

#include <iostream>

void debug_info(std::ostream& d_out) { d_out << std::endl; }

template<typename Arg,  typename... Args>
void debug_info(std::ostream& d_out, const Arg& arg, const Args&... args)
{
    d_out << arg;
    debug_info(d_out, args...);
}

 
#ifdef DEBUG_INFO_ALL
    #define DEBUG_INFO
    #define DEBUG_INFO_PF
#endif

#ifdef DEBUG_INFO
    #define D_LOG debug_info
#else
    #define D_LOG(...)  
#endif

#ifdef DEBUG_INFO_PF
    #define D_PF_LOG()  debug_info(std::cout,  __PRETTY_FUNCTION__)
#else   
    #define D_PF_LOG(d_out) 
#endif