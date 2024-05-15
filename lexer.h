#ifndef LEXER_H
#define LEXER_H
enum token_type{
    TOKEN_END = 0,
    TOKEN_ILLEGAL,

    TOKEN_SPECIAL,      // '!', '(', ':', ... etc.
    TOKEN_NUMBER,       // '123', '420', '345'
    TOKEN_IDENTIFIER,   // 'hello!', 'foo', 'bar'
    TOKEN_KEYWORD,      // 'int', 'float', ... etc.

    TOKEN_COMMENT,
};

class Token{
    public:
        Token(token_type input_type) : type(input_type) {}
        Token(token_type input_type, const char* token_start, std::size_t length) : type(input_type), literal(token_start, length) {}

        std::string_view get_literal() const;
        token_type get_type() const;
        std::string_view get_type_name() const;
    private:
        token_type type;
        std::string_view literal;
};

class Lexer{
    public:
        Lexer(const char* input) : content(input) {}

        Token next_token();
    private:
        const char* content;

        inline void eat_whitespace();

        char read();
        char peek() const; 

        Token identifier();
        Token number();
        Token check_comment();

        void token_init();
        const char* token_start;
        std::size_t token_length;
};

bool is_keyword(Token token);

inline void Lexer::eat_whitespace() {
    while(std::isspace(peek()))
        read();
}

inline bool is_special(char c){
    if (!std::isalnum(c))   return true;
    if (!std::isdigit(c))   return true;
    return false;
}

inline bool is_identifier_start(char c) {
    if (std::isalpha(c))    return true;
    if (c == '_')           return true;
    return false;
}   

inline bool is_identifier(char c) { 
    if (std::isalnum(c))    return true;
    if (c == '_')           return true;
    return false;
}
#endif
