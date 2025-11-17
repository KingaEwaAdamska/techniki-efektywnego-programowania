#include "CmdInterface.hpp"

#include <iostream>
#include <string>

CmdInterface::CmdInterface(){
  tree = new Tree;
}

CmdInterface::~CmdInterface(){
  delete tree;
}

void CmdInterface::commandHandler() {
  CmdStatus status;
  std::string inputLine;
  while (true) {
    std::cout << "> ";
    std::getline(std::cin, inputLine);
    tokens = StringHandler::divideLineIntoTokensAndCommand(inputLine, command);
    status.msg = "";
    status.status = SUCCESS;

    if (command == "exit") {
       return;
    } else if (command == "enter") {
      status = enterHandler();
    } 
    else if (command == "vars") {
      status = varsHandler();
    } 
    else if (command == "print") {
      status = printHandler();
    } 
    else if (command == "comp") {
      status = compHandler();
    } 
    else if (command == "join") {
      status = joinHandler();
    } else if (command == "help") {
      helpHandler();
    }
    else {
      std::cout << "Invalid command" << std::endl;
    }
    if (status.status == WARNING) {
      showWarning(status.msg);
    } else if (status.status == ERROR) {
      showError(status.msg);
    }
     
  }
}

CmdStatus CmdInterface::enterHandler(){
  CmdStatus status;
  status = tree->createTree(tokens);
  return status;
}

CmdStatus CmdInterface::varsHandler(){
  CmdStatus status;
  status.status = SUCCESS;
  status.msg = "";
  std::cout << tree->getVarsString() << std::endl;
  return status;
}

CmdStatus CmdInterface::printHandler(){
  CmdStatus status;
  status.status = SUCCESS;
  status.msg = "";
  std::string result = tree->toString(status);
  if (status.status != ERROR){
    std::cout << result << std::endl;
  }
  return status;
}

CmdStatus CmdInterface::compHandler(){
  CmdStatus status;
  float result = tree->compute(tokens, status);
  if (status.status != ERROR){
    std::cout << result << std::endl;
  }
  return status;
}

CmdStatus CmdInterface::joinHandler(){
  CmdStatus status;
  status.status = SUCCESS;
  status.msg = "";
  tree->join(tokens, status);
  return status;
}

void CmdInterface::helpHandler() {
    std::cout << "Available commands:\n";
    std::cout << "  help      - Show this help message\n";
    std::cout << "  exit      - Exit the program\n";
    std::cout << "  enter     - Create or modify a tree structure\n";
    std::cout << "              Usage: enter <node1> <node2> ...\n";
    std::cout << "  vars      - Display current variables\n";
    std::cout << "  print     - Print the current tree structure\n";
    std::cout << "  comp      - Compute the result of the current tree\n";
    std::cout << "  join      - Join nodes or subtrees\n";
    std::cout << std::endl;
}


void CmdInterface::showWarning(const std::string &msg){
  std::cout << "WARNING: " << msg << std::endl;
}

void CmdInterface::showError(const std::string &msg){
  std::cout << "ERROR: " << msg << std::endl;
}
