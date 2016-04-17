#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

const std::string src {"utilities.cpp"};
const std::regex function_signature {"^\\w+:*\\w*\\s+\\w+\\(.*\\)$"};
const std::regex mainfunc {"int main\\(.*"};

std::vector<std::string> read_lines(const std::string& src)
{
    std::string s;
    std::vector<std::string> lines;
    std::ifstream ifs {src};

    while (std::getline(ifs, s)) {
        lines.push_back(s);
    }

    return lines;
}

std::vector<std::string> find_functions(const std::vector<std::string>& lines)
{
    std::vector<std::string> functions;
    std::string previous_line;
    for (const auto& line : lines) {
        if (!line.empty() && line.at(0) == '{') {
            if (std::regex_match(previous_line, function_signature)
                    && !std::regex_match(previous_line, mainfunc)) {
                functions.push_back(previous_line + ';');
            }
        }
        previous_line = line;
    }

    return functions;
}

void write_guards(std::ofstream& ofs)
{
    ofs << "#pragma once\n\n";
}

void write_functions(std::ofstream& ofs, const std::vector<std::string>& funcs)
{
    for (const auto& func : funcs) {
        ofs << func << std::endl;
    }
    
    ofs << std::endl;
}

std::string get_header_name(const std::string& src)
{
    auto pos = src.rfind('.');
    std::string filename  = src.substr(0, pos);
    return filename + ".hpp";
}

void generate_header(const std::string& src)
{
    auto header = get_header_name(src);
    auto funcs = find_functions(read_lines(src));

    std::ofstream ofs {header};
    write_guards(ofs);
    write_functions(ofs, funcs);
}

int main(int argc, char**argv)
{
    if (argc != 2)
        return 1;

    std::string src {argv[1]};
    generate_header(src);
}
