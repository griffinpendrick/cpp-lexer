#include <iostream>
#include <cstddef>
#include <cctype>
#include "lexer.h"

char Lexer::peek() const    {return *content;}
char Lexer::read()          {return *content++;}
void Lexer::token_init()    {token_start = content; token_length = 0;}

token_type Token::get_type() const              {return type;} 
std::string_view Token::get_literal() const     {return literal;}

std::string_view cpp_keywords[] = {
    "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", "case", 
    "catch", "char", "char16_t", "char32_t", "class", "compl", "const", "const_cast", 
    "constexpr", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", 
    "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", 
    "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", 
    "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", 
    "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert", 
    "static_cast", "struct", "switch", "template", "this", "throw", "true", "try", "typedef", 
    "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", 
    "while", "xor", "xor_eq"
};
#define KEYWORD_SIZE (sizeof(cpp_keywords) / sizeof(cpp_keywords[0]))

bool is_keyword(Token token){
    for (int i = 0; i < KEYWORD_SIZE; ++i){
        if (cpp_keywords[i] == token.get_literal())
            return true;
    }
    return false;
}

Token Lexer::identifier(){
    token_init();
    while(is_identifier(peek())){
        read();
        token_length++;
    } 
    if (is_keyword(Token(TOKEN_IDENTIFIER, token_start, token_length)))
        return Token(TOKEN_KEYWORD, token_start, token_length);

    return Token(TOKEN_IDENTIFIER, token_start, token_length);
}

Token Lexer::number(){
    token_init();
    while(std::isdigit(peek())){
        read();
        token_length++;
    }
    return Token(TOKEN_NUMBER, token_start, token_length);
}

Token Lexer::check_comment(){
    if (read() && peek() != '/') 
        return Token(TOKEN_SPECIAL, token_start, 1);
    
    read();
    token_init();
    while (peek() != '\0' && read() != '\n') token_length++;

    return Token(TOKEN_COMMENT, token_start, token_length);
}

std::string_view Token::get_type_name() const{
    switch(this->get_type()){
        case TOKEN_END:         return "TOKEN_END";
        case TOKEN_ILLEGAL:     return "TOKEN_ILLEGAL";
        case TOKEN_SPECIAL:     return "TOKEN_SPECIAL";
        case TOKEN_NUMBER:      return "TOKEN_NUMBER";
        case TOKEN_IDENTIFIER:  return "TOKEN_IDENTIFIER";
        case TOKEN_COMMENT:     return "TOKEN_COMMENT";
        case TOKEN_KEYWORD:     return "TOKEN_KEYWORD";
        default:                return NULL;
    }
}

Token Lexer::next_token(){
    eat_whitespace();
    char c = peek();

    if (is_identifier_start(c))               return identifier();
    if (std::isdigit(c))                      return number();
    if (c == '/')                             return check_comment();
    if (c == '\0')                            return Token(TOKEN_END, content, 1);
    if (is_special(c))                        return Token(TOKEN_SPECIAL, content++, 1);

    return Token(TOKEN_ILLEGAL);
}

#define TEST_INPUT "#include <iostream>\n" "int main(){\n" "return 0;\n" "}\0"

int main (){
    Lexer lexer(TEST_INPUT);

    for (Token token = lexer.next_token(); token.get_type() != TOKEN_END; token = lexer.next_token())
        std::cout << "{ " << token.get_type_name() << " : '" << token.get_literal() << "' }\n";
}

