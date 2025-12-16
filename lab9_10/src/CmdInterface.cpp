#include "CmdInterface.hpp"
#include "Result.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

CmdInterface::CmdInterface() : currentTreeName("default") {
    trees[currentTreeName] = MySmartPtr<Tree>(new Tree());
}

CmdInterface::~CmdInterface() {}

bool CmdInterface::isValidTreeName(const std::string& name) {
  if (name.empty()) return false;
  if (std::isdigit(name[0])) return false;
  
  for (char c : name) {
    if (!std::isalnum(c) && c != '_') {
        return false;
    }
  }
  return true;
}

MySmartPtr<Tree> CmdInterface::getCurrentTree() {
  auto it = trees.find(currentTreeName);
  if (it != trees.end())
    return it->second;
  return MySmartPtr<Tree>(nullptr);
}

MySmartPtr<Tree> CmdInterface::getTreeByName(const std::string& name) {
  auto it = trees.find(name);
  if (it != trees.end())
    return it->second;
  return MySmartPtr<Tree>(nullptr);
}

void CmdInterface::commandHandler() {
  std::string inputLine;
  while (true) {
    std::cout << "[" << currentTreeName << "]> ";
    std::getline(std::cin, inputLine);
    tokens = StringHandler::divideLineIntoTokensAndCommand(inputLine, command);

    if (command == "exit") {
        return;
    } else if (command == "enter") {
        enterHandler();
    } else if (command == "vars") {
        varsHandler();
    } else if (command == "print") {
        printHandler();
    } else if (command == "comp") {
        compHandler();
    } else if (command == "join") {
        joinHandler();
    } else if (command == "help") {
        helpHandler();
    } else if (command == "countLeafs") {
        countLeafsHandler();
    } else if (command == "assign" || command == "=") {
        assignHandler();
    } else if (command == "list") {
        listTreesHandler();
    } else if (command == "use") {
        useHandler();
    } else {
        std::cout << "Invalid command" << std::endl;
    }
  }
}

void CmdInterface::enterHandler() {
  MySmartPtr<Tree> currentTree = getCurrentTree();
  if (!currentTree) {
    std::cout << "Current tree not found" << std::endl;
    return;
  }
  
  Result<Tree*, Error> result = currentTree->createTree(tokens);
  if (result.errorsExist()) {
    std::cout << result.errorsToString() << std::endl;
  }
}

void CmdInterface::varsHandler() {
  MySmartPtr<Tree> currentTree = getCurrentTree();
  if (!currentTree) {
    std::cout << "Current tree not found" << std::endl;
    return;
  }
  
  Result<std::string, Error> result = currentTree->getVarsString();
  if (result.isSuccess())
    std::cout << result.getValue() << std::endl;
  if (result.errorsExist()) {
    std::cout << std::endl;
  }
}

void CmdInterface::printHandler() {
  MySmartPtr<Tree> currentTree = getCurrentTree();
  if (!currentTree) {
    std::cout << "Current tree not found" << std::endl;
    return;
  }
  
  Result<std::string, Error> result = currentTree->toString();
  if (result.isSuccess())
    std::cout << result.getValue() << std::endl;
  if (result.errorsExist()) {
    std::cout << std::endl;
  }
}

void CmdInterface::compHandler() {
  MySmartPtr<Tree> currentTree = getCurrentTree();
  if (!currentTree) {
    std::cout << "Current tree not found" << std::endl;
    return;
  }
  
  Result<float, Error> result = currentTree->compute(tokens);
  if (result.isSuccess())
    std::cout << result.getValue() << std::endl;
  if (result.errorsExist()) {
    std::cout << result.errorsToString() << std::endl;
  }
}

void CmdInterface::joinHandler() {
  MySmartPtr<Tree> currentTree = getCurrentTree();
  if (!currentTree) {
    std::cout << "Current tree not found" << std::endl;
    return;
  }
  
  MySmartPtr newTree(new Tree());
  Result<Tree*, Error> result = newTree->createTree(tokens);
  
  if (result.errorsExist()) {
    std::cout << result.errorsToString() << std::endl;
    return;
  }
  
  Result<Tree*, Error> joinResult = currentTree->join(tokens);
  if (joinResult.errorsExist()) {
    std::cout << joinResult.errorsToString() << std::endl;
  }
}

void CmdInterface::countLeafsHandler() {
  MySmartPtr<Tree> currentTree = getCurrentTree();
  if (!currentTree) {
    std::cout << "Current tree not found" << std::endl;
    return;
  }
  
  Result<int, Error> result = currentTree->countLeafs();
  if (result.isSuccess())
    std::cout << result.getValue() << std::endl;
  if (result.errorsExist()) {
    std::cout << std::endl;
  }
}

void CmdInterface::assignHandler() {
    if (tokens->size() < 3) {
        std::cout << "Usage: <dest> = <source> | <dest> = <source1> + <source2>\n";
        return;
    }

    const std::string& dest = (*tokens)[0];
    if (!isValidTreeName(dest)) {
        std::cout << "Invalid destination name\n";
        return;
    }

    if ((*tokens)[1] != "=") {
        std::cout << "Expected '='\n";
        return;
    }

    if (tokens->size() >= 5 && (*tokens)[3] == "+") {
        auto it1 = trees.find((*tokens)[2]);
        auto it2 = trees.find((*tokens)[4]);

        if (it1 == trees.end() || it2 == trees.end()) {
            std::cout << "Source tree not found\n";
            return;
        }

        MySmartPtr<Tree> newTree(new Tree());
        *newTree = *it1->second + *it2->second;

        trees[dest] = std::move(newTree);
        // trees[dest] = newTree;

        std::cout << "Tree '" << dest << "' created\n";
        return;
    }

    auto it = trees.find((*tokens)[2]);
    if (it == trees.end()) {
        std::cout << "Source tree not found\n";
        return;
    }

    trees[dest] = it->second;
    std::cout << "Tree '" << dest << "' assigned\n";
}

void CmdInterface::listTreesHandler() {
  std::cout << "Available trees:" << std::endl;
  for (const auto& pair : trees) {
    std::cout << "  " << pair.first;
    if (pair.first == currentTreeName) {
      std::cout << " (current)";
    }
    std::cout << std::endl;
  }
  std::cout << "Total: " << trees.size() << " tree(s)" << std::endl;
}

void CmdInterface::useHandler() {
  if (tokens->empty()) {
    std::cout << "Usage: use <tree_name>" << std::endl;
    return;
  }
  
  std::string treeName = (*tokens)[0];
  if (trees.find(treeName) != trees.end()) {
    currentTreeName = treeName;
    std::cout << "Switched to tree '" << treeName << "'" << std::endl;
  } else {
    std::cout << "Tree '" << treeName << "' not found" << std::endl;
  }
}

void CmdInterface::helpHandler() {
  std::cout << "Available commands:\n";
  std::cout << "  help               - Show this help message\n";
  std::cout << "  exit               - Exit the program\n";
  std::cout << "  use <name>         - Switch to specified tree\n";
  std::cout << "  list               - List all available trees\n";
  std::cout << "  assign/=<dest> = <source> - Assign tree (with move semantics)\n";
  std::cout << "                    - <dest> = <source1> + <source2> - Create sum of trees\n";
  std::cout << "  enter              - Create or modify current tree structure\n";
  std::cout << "  vars               - Display current variables\n";
  std::cout << "  print              - Print the current tree structure\n";
  std::cout << "  comp               - Compute the result of the current tree\n";
  std::cout << "  join               - Join nodes or subtrees\n";
  std::cout << "  countLeafs         - Count leafs in current tree\n";
  std::cout << std::endl;
}
