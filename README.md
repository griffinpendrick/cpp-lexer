# C++ Lexer
This is a brief C++ [*Lexical Analyzer*](https://en.wikipedia.org/wiki/Lexical_analysis) written in C++!

Only written in ~200 lines of code, this Lexer can take an input of C++ code and tokenize it into:
* Keywords
* Identifiers
* Numbers
* Special Characters **('!', '?', '*', etc.)**
* Comments
## Sample Input:

**int x = 10;**

## Sample Output:

{ TOKEN_KEYWORD : 'int' }\
{ TOKEN_IDENTIFIER : 'x' }\
{ TOKEN_SPECIAL : '=' }\
{ TOKEN_NUMBER : '10' }\
{ TOKEN_SPECIAL : ';' }
