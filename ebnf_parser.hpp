//
// Created by ionut on 15.08.2022.
//

#ifndef SCHOOL_MATH_EBNF_PARSER_HPP
#define SCHOOL_MATH_EBNF_PARSER_HPP

#include <map>
#include <set>
#include <string>

class ebnf_parser
{
public:
    explicit ebnf_parser(std::string const &file_path);

private:
    [[noreturn]] void parse_line(std::string line);

    std::map<std::string, std::set<std::string>> rules_{};
};

#endif //SCHOOL_MATH_EBNF_PARSER_HPP
