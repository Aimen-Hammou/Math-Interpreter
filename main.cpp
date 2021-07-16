#include <iostream>
#include "visitor.hpp"

int main()
{

    std::string input;

    while (true)
    {
        std::cout << "-> ";

        getline(std::cin, input);

        if (input == "exit" || input == "EXIT")
            break;

        Parser parser(input);


        std::cout << "= " + std::to_string( evaluate_tree( parser.parse() ) ) << std::endl;
    }


    return 0;
}
