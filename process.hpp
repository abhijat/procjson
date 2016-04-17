#pragma once
#include <string>

struct Process
{
    unsigned userid;
    unsigned processid;
    std::string cmdline;
    std::string wchan;
};

bool is_process_valid(const Process& process);
Process create_process_data(const std::string& path);
std::string get_process_json(const Process& process, bool prettyprint=false);
