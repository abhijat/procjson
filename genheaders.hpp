#pragma once

void write_guards(std::ofstream& ofs);
void write_functions(std::ofstream& ofs, const std::vector<std::string>& funcs);
std::string get_header_name(const std::string& src);
void generate_header(const std::string& src);

