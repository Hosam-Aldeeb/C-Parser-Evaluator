#include "tokenizer.h"
#include <vector>
#include <string>
#include <sstream>
#include <regex>




Tokenizer::Tokenizer(std::string ln) {
  // complete the constructor
std::vector<Token>::iterator iter;

std::vector<Token> tokens;

  /** Pad special characters with string. **/
  std::string input = ln;
  //fix later
  for (int i = 0; i < input.size(); i++) {
    if (input[i] == '*' || input[i] == '+'
        || input[i] == '(' || input[i] == ')'
        || input[i] == ':' || input[i] == ','||input[i]=='-') {

        input.insert(i, " ");
        i += 2;
        input.insert(i, " ");
    }
  }
  //std::cout << "Padded input: " << input << std::endl;


  /** Split input string into list by space. **/
  std::vector<std::string> contents;
  std::stringstream stringStream(input);
  std::string line;
  while(std::getline(stringStream, line)) // do not take inputs from tokenizer
  {
      std::size_t prev = 0, pos;
      while ((pos = line.find_first_of(" ", prev)) != std::string::npos)
      {
          if (pos > prev)
              contents.push_back(line.substr(prev, pos-prev));
          prev = pos+1;
      }
      if (prev < line.length())
          contents.push_back(line.substr(prev, std::string::npos));
  }

  for (int i = 0; i < contents.size(); i++) {
      //std::cout << std::endl << "Token " << i+1 << ":  " << contents.at(i);
  }


  /** Initializing the tokens vector (and its type) using the contents vector above. **/
  for (int i = 0; i < contents.size(); i++) {
      std::string content=contents.at(i); 
      // content.push_back(ln[i]);
      std::string type = "";

      // setting the type
      if (content == "1" || content == "0") {
        type = "constant";
       // std::cout << type << std::endl;
      } else if (std::regex_match (content, std::regex("[A-Za-z]+[A-Za-z0-9]*")) && content.size() <= 10) {
        type = "variable";
      } else if (content == "*" || content == "+"||content=="-") {
        type = "operator";
      } else if (content == "(" || content == ")" || content == ":" || content == ",") {
        type = "symbol";
      }
      else{
        std::cout<<"Error: invalid input";
        exit(0);
      }
      

      // setting the vector
      Token token;
      token.content = content;
      token.type = type;
      this->tokens.push_back(token);
  }
  

  //just displaying the tokens
  //std::cout << std::endl << std::endl << "Tokens with Type";
  for (int i = 0; i <  this->tokens.size(); i++) {
   //std::cout << std::endl << "Token " << i+1 << ":  " <<  this->tokens.at(i).content << " (Type: " <<  this->tokens.at(i).type << ")";
  }

  // /** just pointing the iterator class variable to the beginning of the tokens vector so that
  //  * we can use it in the helper/class functions below **/
 
}

bool Tokenizer::advanceToken() {
  // your code starts here
  this->iter++;
  return (this->iter != this->tokens.end());
}

bool Tokenizer::hasToken() const {
  // your code starts here
  return (this->iter != this->tokens.end());
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  // your code starts there
  if (hasToken()) {
    return *this->iter;
  }
}
