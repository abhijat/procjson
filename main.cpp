#include <iostream>
#include <string>
#include <regex>
#include <vector>

#include <boost/filesystem.hpp>

#include "process.hpp"
#include "utilities.hpp"

const std::regex process_dir {"^/proc/\\d+$"};

bool path_is_process_dir(const std::string& p)
{
    return std::regex_match(p, process_dir);
}

template <typename FilterFunction>
std::vector<std::string> get_filtered_paths(const std::string& path,
        FilterFunction function)
{
    boost::filesystem::path p {path};
    auto beg = boost::filesystem::directory_iterator {p};
    auto end = boost::filesystem::directory_iterator {};

    std::vector<std::string> paths;
    for (auto i = beg; i != end; ++i) {
        
        auto tmp = i->path();
        if (function(tmp.string())) {
            paths.push_back(tmp.string());
        }
    }

    return paths;
}

int main()
{
    auto matcher = [] (const std::string& s) {return std::regex_match(s, process_dir);};
    auto filtered = get_filtered_paths("/proc", matcher);

    for (const auto& p : filtered) {
        auto process = create_process_data(p);

        if (!is_process_valid(process))
            continue;

        auto json = get_process_json(process);
        std::cout << json << std::endl;
    }

}
