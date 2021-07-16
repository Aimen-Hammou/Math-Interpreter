#include "parser.hpp"

//Visit the tree in a recursive way

double evaluate_tree(Token *node)
{
    //Numbers don't have left and right nodes so we return the value (see Parser::factor())
    if (node->type == NUM)
    {
        return node->value;
    }

    else if (node->type == ADD)
    {
        return evaluate_tree(node->left) + evaluate_tree(node->right);
    }

    else if (node->type == SUB)
    {
        return evaluate_tree(node->left) - evaluate_tree(node->right);
    }

    else if (node->type == MUL)
    {
        return evaluate_tree(node->left) * evaluate_tree(node->right);
    }

    else if (node->type == DIV)
    {
        if (node->right->type == NUM && node->right->value == 0 )
        {
            std::cout << "ERROR: Right value of division is 0\n";
            exit(-1);
        }

        return evaluate_tree(node->left) / evaluate_tree(node->right);
    }
}
