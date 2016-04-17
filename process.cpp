#include <sstream>

#include "process.hpp"
#include "utilities.hpp"

bool is_process_valid(const Process& process)
{
    return !process.cmdline.empty() && !process.wchan.empty()
        && (process.processid != 0);
}

Process create_process_data(const std::string& path)
{
    Process process;

    auto pid = path.substr(path.rfind('/') + 1);
    process.processid = std::atoi(pid.c_str());

    auto cmdline_file = path + "/cmdline";
    auto cmdline = get_line_from_file(cmdline_file);
    cmdline = replace_null(cmdline);

    process.cmdline = cmdline;
    process.wchan = get_line_from_file(path + "/wchan");

    auto uid_line = get_line_starting_with(path + "/status", "Uid:");
    std::stringstream ss {uid_line};
    
    std::string uid;
    ss >> uid >> uid;

    process.userid = std::atoi(uid.c_str());
    return process;
}

std::string get_process_json(const Process& process, bool prettyprint)
{
    std::stringstream ss;
    ss << "{";

    if (prettyprint) ss << "\n ";

    ss << "\"cmdline\":";
    ss << "\"" << escape_quotes(process.cmdline) << "\"";
    ss << ",";

    if (prettyprint) ss << "\n ";

    ss << "\"uid\":";
    ss << process.userid;
    ss << ",";

    if (prettyprint) ss << "\n ";

    ss << "\"pid\":";
    ss << process.processid;
    ss << ",";

    if (prettyprint) ss << "\n ";

    ss << "\"wchan\":";
    ss << "\"" << process.wchan << "\"";

    if (prettyprint)
        ss << "\n";

    ss << "}";

    return ss.str();
}
