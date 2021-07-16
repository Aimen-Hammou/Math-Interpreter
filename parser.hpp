#include "tokenizer.hpp"


/*
    Grammar:

        expr   : term ((PLUS | MINUS) term)*
        term   : factor ((MUL | DIV) factor)*
        factor : INTEGER | LPAREN expr RPAREN

*/

class Parser
{
    private:
        std::vector<Token> tokens;

        void get_next_token();

        Token *current_token = nullptr;

        int position;

        Token *expr();
        Token *term();
        Token *factor();

    public:

        Parser( ) = default;
        Parser(Parser &) = delete;
        Parser(Parser &&) = delete;


        Parser(std::string &input)
        {


            Tokenizer tokenizer(input);

            tokens = tokenizer.get_tokens();

            position = 0;

            current_token = &tokens[position];
        }


        Token *parse();


};


void Parser::get_next_token()
{

    if ( ( position + 1 ) < tokens.size())
    {
        position = position + 1;

        current_token = &tokens[position];
    }

    return;
}
Token *Parser::parse()
{
    return expr();
}


Token *Parser::factor()
{


    //NUMBER
    if(current_token->type == NUM)
    {
        Token *tmp = current_token; //we need to propagate so a tmp variable is created

        get_next_token();

        return tmp;
    }

    //LAPRENT EXPR RPARENT
    else if (current_token->type == LPAREN)
    {
        get_next_token();

        Token *inside_parenthesis_expression = expr();

        if (current_token->type != RPAREN)
        {
            std::cout << "ERROR: missing closing parenthesis\n";
            exit(-1);
        }

        return inside_parenthesis_expression; // we return the subtree of the expression to append to the main tree
    }
}


Token *Parser::term()
{
    Token *token = factor();
    Token *tmp = nullptr;

    while(current_token->type == MUL || current_token->type == DIV)
    {
        tmp = current_token; // operation token;

        get_next_token();

        tmp->left = token; // Number before operation;
        tmp->right = factor();

        token = tmp;

    }

    return token;

}

Token *Parser::expr()
{
    Token *token = term();
    Token *tmp = nullptr;

    while(current_token->type == ADD || current_token->type == SUB)
    {
        tmp = current_token; // operation token;

        get_next_token();

        tmp->left = token; // Number before operation;
        tmp->right = term();

        token = tmp;

    }

    return token;

}



