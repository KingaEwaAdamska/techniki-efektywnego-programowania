#include "CmdInterface.hpp"
#include "Result.hpp"

#include <iostream>
#include <string>

CmdInterface::CmdInterface(){
  tree = new Tree;
  logger = new Logger(LOG_FILE);
}

CmdInterface::~CmdInterface(){
  delete tree;
}

void CmdInterface::commandHandler() {
  std::string inputLine;
  while (true) {
    std::cout << "> ";
    std::getline(std::cin, inputLine);
    tokens = StringHandler::divideLineIntoTokensAndCommand(inputLine, command);

    if (command == "exit") {
       return;
    } else if (command == "enter") {
      enterHandler();
    } 
    else if (command == "vars") {
      varsHandler();
    } 
    else if (command == "print") {
      printHandler();
    } 
    else if (command == "comp") {
      compHandler();
    } 
    else if (command == "join") {
      joinHandler();
    } else if (command == "help") {
      helpHandler();
    } else if (command == "countLeafs") {
      countLeafsHandler();
    } else {
      std::cout << "Invalid command" << std::endl;
    }
  }
}

void CmdInterface::enterHandler(){
  Result<Tree*, Error> result = tree->createTree(tokens);
  if (result.errorsExist()){
    std::cout << result.errorsToString() << std::endl;
    logger->logResult(result);
  }
}

void CmdInterface::varsHandler(){
  Result<std::string, Error> result = tree->getVarsString();
  if (result.isSuccess())
    std::cout << result.getValue() << std::endl;
  if (result.errorsExist()){
    std::cout << std::endl;
    logger->logResult(result);
  }
}

void CmdInterface::printHandler(){
  Result<std::string, Error> result = tree->toString();
  if (result.isSuccess())
    std::cout << result.getValue() << std::endl;
  if (result.errorsExist()){
    std::cout << std::endl;
    logger->logResult(result);
  }
}

void CmdInterface::compHandler(){
  Result<float, Error> result = tree->compute(tokens);
  if (result.isSuccess())
    std::cout << result.getValue() << std::endl;
  if (result.errorsExist()){
    std::cout << std::endl;
    logger->logResult(result);
  }
}

void CmdInterface::joinHandler(){
  Result<Tree*, Error> result = tree->join(tokens);
  if (result.errorsExist()){
    std::cout << result.errorsToString() << std::endl;
    logger->logResult(result);
  }
}

void CmdInterface::countLeafsHandler() {
  Result<int, Error> result = tree->countLeafs();
  if (result.isSuccess())
    std::cout << result.getValue() << std::endl;
  if (result.errorsExist()){
    std::cout << std::endl;
    logger->logResult(result);
  }
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

