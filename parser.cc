#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

#include <iostream>
#include <map>

FormulaParser::FormulaParser(std::string ln, std::map<std::string, bool> assign): tknzr {new Tokenizer{ln}} {
  this->assign=assign;
  //std::cout << (tknzr->tokens).size() << std::endl;
  for (auto t: tknzr->tokens) {
   // std::cout << t.type << std::endl;
  }
}




TreeNode *FormulaParser::parseConjTerm() {
  //your code starts here
   //std::cout<<"check conjterm called"<<std::endl;
  TreeNode *resNode = nullptr;
   Token currentToken = (tknzr->tokens).at(position);
  TreeNode *t1=parseTerm();
  resNode=t1;
  if(position >= (tknzr->tokens).size()){
    return t1;
  }
  currentToken = (tknzr->tokens).at(position);
  if (currentToken.type!="operator"){
   // std::cout << currentToken.content << std::endl;
  }
  //std::cout << tknzr->tokens.at(position).content << std::endl;
  if (currentToken.content =="*" || currentToken.content=="+"){
      // std::cout<<"check current content is *"<<std::endl;
       position++;
       resNode=new OperatorNode(currentToken.content);
       TreeNode *t2=parseConjTerm();
       resNode->updateChildren(t1,t2);
   };
 return resNode;
}

TreeNode *FormulaParser::parseTerm() {
  TreeNode *resNode = nullptr;
  
  Token currentToken = (tknzr->tokens).at(position);
  position++;
   //std::cout<<"check parseterm called"<<std::endl;
  if (currentToken.type == "constant"){
    resNode = new ConstantNode(currentToken.content);
  }
  else if(currentToken.type=="variable"){
    // if(assign.find(currentToken.content)== assign.end()){
    //   std::cout<<"Error: contradicting assignment";
    //   return 0;
    // }
    resNode=new VariableNode(currentToken.content);
    // std::cout<<"check parse term type variable"<<std::endl;
  }
  else if(currentToken.content=="("){
    TreeNode *t1=parseFormula();
    resNode=t1;
   // std::cout<<currentToken.content;
  }
  else if(currentToken.content=="-"){
    TreeNode *t2=parseTerm();
    resNode=new OperatorNode(currentToken.content);
    resNode->updateLeftChild(t2);

  }
  return resNode;
}

TreeNode *FormulaParser::parseFormula() {
 
 // std::cout<<"check parseform called"<<std::endl;
    TreeNode *resNode = nullptr;
     Token currentToken = (tknzr->tokens).at(position);
     // std::cout<<"check "<<std::endl;
     
      TreeNode *t1=parseConjTerm();
      resNode=t1;
      //std::cout<<"check 44"<<std::endl;
      position++;
  //     while (true){
  //   if (currentToken.type!="operator"){
  //     break;
  //  }
     if (currentToken.content =="+"){ // would u add ++ to go the next one?
       TreeNode *t2=parseFormula();
       resNode=new OperatorNode(currentToken.content);
       resNode->updateChildren(t1,t2);
     }
//}
return resNode;
}

TreeNode * FormulaParser::getTreeRoot() {
  // your code starts here
  //std::cout<<"check gettreeroot"<<std::endl;
  return FormulaParser::parseFormula();
}

FormulaParser::~FormulaParser() {
  // your code starts here
}

AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
  std::map<std::string, bool> results;//bool previously
  // your code starts here
  // Ur : 1 ,  c : 1
  //                 i
  //access tokenizer vector to check if empty
  //std::cout<<"check1" << std::endl;
  
  //while (true){
    //std::cout << std::endl << "Position: " << position << ", Last valid index: " << (tknzr->tokens).size()-1 << std::endl;
  if (tknzr->tokens.empty()|| position == (tknzr->tokens).size()){
    return results;
    
  }
  Token currentToken=(tknzr->tokens).at(position);
  if (currentToken.type=="variable"){
    //std::cout<<"check2" << std::endl;
    std::string currentVar=currentToken.content;
    //std:: cout<<currentVar<<std::endl;
    position++;
    if(position < (tknzr->tokens).size()){
    currentToken=(tknzr->tokens).at(position);}
    if (currentToken.content!=":"){
    //std::cout<<"Error: incomplete assignment"<<std::endl;
    
    //position ++;
    
    
    currentToken=(tknzr->tokens).at(position);}
    if (currentToken.content==":"){
     // std::cout<<"check3" << std::endl;
      position++;
       if(position < (tknzr->tokens).size()){
      currentToken=(tknzr->tokens).at(position);
      }
       }

    if (currentToken.type=="constant"){
      //    std::cout<<results.count(currentVar)<<"count"<<std::endl;
      //     std::cout<<results[currentVar]<<"results at currentVar"<<std::endl;


      // if((results.count(currentVar)>=1 && results.at(currentVar)== true && currentToken.content=="0")
      //   || (results.count(currentVar)>=1 && results.at(currentVar)== false && currentToken.content=="1")){
           
      //   std::cout<<"Error: contradicting assignment";
      //   exit(1);
      // }

      if(currentToken.content=="1"){
      results.insert({currentVar,true});// 1 is true, 0 is false, func to transfer string to int or bool
      } if(currentToken.content=="0"){
        results.insert({currentVar,false});
      }
      

      //std::cout<<results.at(currentVar);
      //std::cout<<"check4" << std::endl;
      if(position < (tknzr->tokens).size()){
        position++;
        if(position != (tknzr->tokens).size())
        {
          currentToken=(tknzr->tokens).at(position);
        }
      }
      //std::cout << std::endl << "Position: " << position << ", Last valid index: " << (tknzr->tokens).size()-1 << std::endl;
      }
    
    if ((position < (tknzr->tokens).size()) && (tknzr->tokens).at(position).content==","){
        //std::cout<<"check5" << std::endl;
        position++;
        if(position < (tknzr->tokens).size()){
        currentToken=(tknzr->tokens).at(position);
        //std::cout << std::endl << "Position: " << position << ", Last valid index: " << (tknzr->tokens).size()-1 << std::endl;
        std::map<std::string, bool> results2 = parseAssignment();
        for(auto &g:results2){
          results.insert({g.first,g.second});
          
       
        }
      }
    }
    
  //}
    }
return results;


  
}

AssignmentParser::~AssignmentParser() {
  // your code starts here
}
