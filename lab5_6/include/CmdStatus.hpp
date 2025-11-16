#ifndef CMDSTATUS_HPP
#define CMDSTATUS_HPP

#include <string>

enum Status {
  SUCCESS,
  WARNING,
  ERROR
};

struct CmdStatus {
  Status status;
  std::string msg;
};

#endif
