#include <iostream>
#include <sstream>

#include "process.hpp"
#include "utilities.hpp"

bool is_process_valid(const Process& process)
{
    return !process.cmdline.empty() && !process.wchan.empty()
        && (process.processid != 0);
}

unsigned get_process_id_from_path(const std::string& path)
{
    if (path.empty()) {
        throw std::invalid_argument("empty path");
    }

    auto last_slash = path.rfind('/');
    if (last_slash == std::string::npos) {
        throw std::invalid_argument("argument not a path");
    }

    if (last_slash == path.size() - 1) {
        last_slash = path.rfind('/', last_slash - 1);
        if (last_slash == std::string::npos) {
            throw std::invalid_argument("argument does not have pid");
        } else {
            std::string pidstr = path.substr(last_slash + 1, path.size() - last_slash);
            return std::atoi(pidstr.c_str());
        }
    }

    std::string pid_string = path.substr(last_slash + 1);
    return std::atoi(pid_string.c_str());
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
