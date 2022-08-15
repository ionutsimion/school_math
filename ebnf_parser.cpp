//
// Created by ionut on 15.08.2022.
//

#include <algorithm>
#include <fstream>
#include <iostream>

#include "ebnf_parser.hpp"

namespace
{
    auto is_comment(std::string const &) -> bool;
} // anonymous

ebnf_parser::ebnf_parser(std::string const &file_path)
{
    std::ifstream is{ file_path, std::ios_base::in };
    if (!is.is_open())
        std::clog << "File not found: " << file_path << std::endl;

    for (std::string line{}, ebnf_expression{}; std::getline(is, line); )
    {
        if (line.empty() || is_comment(line))
            continue;

        ebnf_expression += line;

        if (ebnf_expression.back() == ';')
        {
            parse_line(ebnf_expression);
            ebnf_expression.clear();
        }
    }

    for (auto const &[name, definitions] : rules_)
    {
        std::clog << name << " <- [";
        if (definitions.empty())
            std::clog << "Error: no definition!";
        else
            std::clog << *definitions.begin();
        for (auto definition = std::next(definitions.cbegin()); definition != definitions.cend(); ++definition)
            std::clog << ", " << *definition;
        std::clog << ']' << std::endl;
    }
}

void ebnf_parser::parse_line(std::string line)
{
    line.erase(std::remove_if(line.begin(), line.end(), [](char const c){ return std::isspace(c); }), line.end());

    auto const equal_position = line.find('=');
    auto rule_name = line.substr(0, equal_position);
    auto const end_of_expression_marker = line.find(';');
    auto rule_definition = line.substr(equal_position + 1ull, end_of_expression_marker - equal_position - 1ull);

    std::set<std::string> definitions{};
    size_t from = 0ull;
    size_t to = rule_definition.find('|');
    do
    {
        definitions.emplace(rule_definition.substr(from, to - from));
        from = to + 1ull;
        to = rule_definition.find('|', from);
    }
    while (to != std::string::npos);

    rules_.emplace(std::move(rule_name), std::move(definitions));
}

namespace
{
    auto is_comment(std::string const &line) -> bool
    {
        return line.find("(*") == 0ull && line.find("*)") == line.size() - 2ull;
    }
} // anonymous
