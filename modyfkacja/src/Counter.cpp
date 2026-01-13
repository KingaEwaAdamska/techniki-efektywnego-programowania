#include "Counter.hpp"

Counter::Counter(){
  count = 1;
}

int Counter::add(){
  count++;
  return count;
}

int Counter::dec(){
  count--;
  return count;
}

int Counter::get(){
  return count;
}
