#include "ebnf_parser.hpp"

int main(int number_of_arguments, char *arguments[])
{
    if (number_of_arguments == 1)
        return 1;

    ebnf_parser parser{ std::string{ arguments[1] } };
    return 0;
}
