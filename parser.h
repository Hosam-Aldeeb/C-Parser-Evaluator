#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <iostream>

#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
    Tokenizer *tknzr;
    int position= 0;
     std::map<std::string, bool> assign;
    TreeNode *parseFormula(); // parse non-terminal Formula in the grammar
    TreeNode *parseConjTerm(); // parse non-terminal ConjTerm in the grammar
    TreeNode *parseTerm(); // parse non-terminal Term in the grammar
  public:
    FormulaParser(std::string ln, std::map<std::string, bool> assign);
    TreeNode *getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
    ~FormulaParser();
};

// Parser for the Assignment
class AssignmentParser {
    Tokenizer *tknzr;
    int position= 0;
  public:
    AssignmentParser(std::string ln);
    std::map<std::string, bool> parseAssignment();
    ~AssignmentParser();
};

#endif