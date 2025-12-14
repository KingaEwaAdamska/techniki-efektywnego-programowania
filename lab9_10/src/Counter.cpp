#include "Counter.hpp"

Counter::Counter(){
  count = 1;
}

Counter::add(){
  count++;
}

Counter::dec(){
  count--;
}

Counter::get(){
  return count;
}
