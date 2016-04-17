#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

std::string escape_quotes(const std::string& s)
{
    std::stringstream ss;
    for (const auto& ch : s) {
        if (ch == '\'' || ch == '"') {
            ss << '\\';
        }
        ss << ch;
    }

    return ss.str();
}

std::string replace_null(const std::string& s, char replace_with=' ')
{
    std::stringstream ss;
    size_t i = 0;

    for (const auto& ch : s) {
        if (ch == '\0') {
            if (i != s.size() - 1)
                ss << replace_with;
        } else {
            ss << ch;
        }

        ++i;
    }

    return ss.str();
}

std::string get_line_from_file(const std::string& filepath)
{
    std::ifstream ifs {filepath};
    if (ifs.fail()) {
        throw std::invalid_argument("unable to open " + filepath);
    }

    std::string line;

    try {
        std::getline(ifs, line);
    } catch (const std::exception& e) {
        throw std::runtime_error("could not read from file " + filepath);
    }

    return line;
}

std::string get_line_starting_with(const std::string& filepath, const std::string& term)
{
    std::ifstream ifs {filepath};
    if (ifs.fail()) {
        throw std::invalid_argument("unable to open " + filepath);
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (line.find(term) == 0) {
            return line;
        }
    }

    throw std::runtime_error("could not find term: " + term);
}
