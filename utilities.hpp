#pragma once

std::string escape_quotes(const std::string& s);
std::string replace_null(const std::string& s, char replace_with=' ');
std::string get_line_from_file(const std::string& filepath);
std::string get_line_starting_with(const std::string& filepath, const std::string& term);

