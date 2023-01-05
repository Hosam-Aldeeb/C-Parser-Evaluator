#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <exception>
#include <regex>
#include <algorithm>
#include <cctype>
#include <vector>
//For token type, I used "constant", "variable", and "symbol". "(" and ")" 
//are symbol tokens but not operators. (It is just a recommendation)

struct Token

{
    std::string content;
    std::string type;
};

// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
  // your code starts here
 public:
    std::vector<Token>::iterator iter;
    std::vector<Token> tokens;
    Tokenizer(std::string ln);
    bool advanceToken(); // advance to the next token; return false if no more token exist
    bool hasToken() const; // check whether there is a current token
    Token getToken(); // returns the token being processed


};

#endif
