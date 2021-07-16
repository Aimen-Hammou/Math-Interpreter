#include <vector> // std::vector<tokens>
#include <cctype>  // isdigit
#include <stdexcept> //runtime_error

enum token_type
{
    NUM = 0,

    ADD,
    SUB,
    MUL,
    DIV,

    LPAREN,
    RPAREN,
};


struct Token
{
    token_type type;
    int value;

    Token *left;
    Token *right;
};

class Tokenizer
{
    private:

        const std::string input_to_tokenize;
        char current_char;
        int current_position;

        std::vector<Token> tokens;

        void advance();

        Token init_token(token_type type, int value, Token *left, Token *right);

        void tokenize();

    public:


        Tokenizer( ) = default;
        Tokenizer(const std::string &_input): input_to_tokenize(_input),
                                             current_position(0),
                                             current_char(input_to_tokenize[current_position])
                                             { ; };

        //Move construct
        Tokenizer(Tokenizer &&other)
        {
            tokens = other.tokens;

            other.tokens.clear();
        }


        //getter
        std::vector<Token> get_tokens() noexcept
        {

            tokenize();

            return tokens;
        }


        void print_tokens() const noexcept
        {
            for(auto token: tokens)
            {
                printf("Type: %d and Value: %d\n", token.type, token.value);
            }
        }
};


void Tokenizer::tokenize()
{

    size_t len_of_input = input_to_tokenize.length();

    while(current_position < len_of_input)
    {
        switch(current_char)
        {
            case '+':
                tokens.push_back(init_token(ADD, 0, nullptr, nullptr));
                advance();
                break;

                    case '-':
                        tokens.push_back(init_token(SUB, 0, nullptr, nullptr));
                        advance();
                        break;

                    case '*':
                        tokens.push_back(init_token(MUL, 0, nullptr, nullptr));
                        advance();
                        break;

                    case '/':
                        tokens.push_back(init_token(DIV, 0, nullptr, nullptr));
                        advance();
                        break;

                    case '(':
                        tokens.push_back(init_token(LPAREN, 0, nullptr, nullptr));
                        advance();
                        break;

                    case ')':
                        tokens.push_back(init_token(RPAREN, 0, nullptr, nullptr));
                        advance();
                        break;

                    case ' ':

                        while(current_char == ' ')
                            advance();
                        break;

                    default:


                        if(isdigit(current_char))
                        {
                            std::string integer_value = "";

                            while(isdigit(current_char))
                            {

                                integer_value += current_char;

                                advance();
                            }

                            tokens.push_back(init_token(NUM, std::atoi(integer_value.c_str()), nullptr, nullptr));
                            break;
                        }

                        //throw std::runtime_error("ERRORE: carattere  non valido");

                        std::cout << "ERRORE: carattere " + std::string(1, current_char) + " non valido.\n";
                        exit(-1);

                }

            }
}


void Tokenizer::advance()
{
    current_position = current_position + 1;
    current_char = input_to_tokenize[current_position];

    return;
}

Token Tokenizer::init_token(token_type type, int value, Token *left, Token *right)
{

    Token token;

    token.type = type;
    token.value = value;
    token.left  = left;
    token.right = right;

    return token;

}
