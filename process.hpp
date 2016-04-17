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
unsigned get_process_id_from_path(const std::string& path);
Process create_process_data(const std::string& path);
std::string get_process_json(const Process& process, bool prettyprint=false);
