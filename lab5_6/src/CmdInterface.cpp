#include "CmdInterface.hpp"

#include <iostream>
#include <sstream>
#include <string>

CmdInterface::CmdInterface(){
  tree = new Tree;
}

CmdInterface::~CmdInterface(){
  delete tree;
}

void CmdInterface::commandHandler() {
  CmdStatus status;
  while (true) {
    std::cout << "> ";
    std::getline(std::cin, inputLine);
    divideLineIntoTokens();

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
    } 
    else {
      std::cout << "Invalid command" << std::endl;
    }
    if (status.status == WARNING){
      std::cout << "WARNING: "<< status.msg << std::endl;
    }
  }
}

void CmdInterface::divideLineIntoTokens(){
  tokens.clear();

  std::stringstream ss(inputLine);
  std::string token;

  if (ss >> token) {
    command = token;
  }

  while (ss >> token) {
    tokens.push_back(token);
  }
}

CmdStatus CmdInterface::enterHandler(){
  CmdStatus status;
  status = tree->createTree(&tokens);
  return status;
}

CmdStatus CmdInterface::varsHandler(){
  CmdStatus status;
  return status;
}

CmdStatus CmdInterface::printHandler(){
  CmdStatus status;
  std::cout << tree->toString() << std::endl;
  return status;
}

CmdStatus CmdInterface::compHandler(){
  CmdStatus status;
  std::cout << tree->compute() << std::endl;
  return status;
}

CmdStatus CmdInterface::joinHandler(){
  CmdStatus status;
  return status;
}

