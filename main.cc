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
#include <stack>


// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  // your code starts here
  int i = 0;
  while (line[i] != ';') {
    formulaStr += line[i];
    i++;
  }
  std::cout << "here" << std::endl;
  // if(i==line.size()-1){
  //   std::cout<<"Error: invalid input";
  // }
  i++;
  while (line[i] != '\0') {
    assignmentStr += line[i];
    i++;
  }

  }
  


// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  
  
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
    // line = "1 * VAr ; VAr: 1";
    getline(std::cin,line);
    //std::cout<<line<<std::endl;
    parseLine(line, formulaStr, assignmentStr);
    if (line.find(';') == std::string::npos) {
  std::cout << "Error: invalid input";
  return 0;
}
// check if assign string is not empty, and missing colon
if(!assignmentStr.empty() && assignmentStr.find(':') == std::string::npos){
  std::cout<<"Error: invalid input";
  return 0;
 
}
 //Tokenizer tokenizer = Tokenizer(line);
// if(assignmentStr.empty()){
//   std::cout << "Error: incomplete assignment";
//   return 0;
// }

Tokenizer tokenizer = Tokenizer(formulaStr);
  if(assignmentStr.empty()){
    for (int i=0;i<tokenizer.tokens.size()-1;i++){
      if(tokenizer.tokens.at(i).type=="variable"){
        std::cout<<"error: incomplete assignment";
        return 0;
      }
  }
  }


// for (int i = 0; i < formulaStr.length(); i++) {
//   if (std::regex_match (formulaStr, std::regex("[A-Za-z]+[A-Za-z0-9]*"))){
//   }else{
//     std::cout<<"Error: invalid input";
//     return 0;
//   }
// }

//bracket check
int count1=0;
int count2=0;
for (int i = 0; (i = formulaStr.find('(', i)) != std::string::npos; i++) {
        count1++;
        //std::cout << count1<<std::endl;
}
for (int i = 0; (i = formulaStr.find(')', i)) != std::string::npos; i++) {
        count2++;
       // std::cout << count2<<std::endl;
      
    }
    //std::cout << count1<<std::endl;
    //std::cout << count2<<std::endl;
    if (count1!=count2){
      std::cout << "Error: invalid input";
      return 0;
    }

  


  
  //std::cout << "Line:  " << line << std::endl;
  // if(assignmentStr.empty()|| assignmentStr.find_first_not_of(' ') == std::string::npos){
  //   std::cout << "Error: incomplete assignment";
  //   return 0;
  // }
  

  
   

AssignmentParser aParser(assignmentStr);
  std::map<std::string, bool> assign=aParser.parseAssignment();
  // for(auto g:assign){
  //   std::cout<<g.first<< g.second<<std::endl;
  //   if(g.second>1){
  //     std::cout<<"duplicate";
  //   }
    
    // std::cout<<g.second<<"second"<<std::endl;

  //}
  // for (auto iter = assign.begin();iter != assign.end(); ++iter){
  //       std::cout << iter->first << " = " << iter->second << std::endl;
        
  // }
  
   //Tokenizer tokenizer = Tokenizer(line);
 FormulaParser fParser(formulaStr,assign);
 TreeNode * f=fParser.getTreeRoot();//put paranthesis over everything,1+a*b,print Lchild, ((1) + ((a)) * (b))
  //print the tree
  //f->print_chld();

  

  
  // std::cout << "------------------------------" << std::endl;
  bool bBres=f->evaluate(assign);//true
  std::cout<<bBres;
  
  
  
        
  // }
    break;
  }
}
