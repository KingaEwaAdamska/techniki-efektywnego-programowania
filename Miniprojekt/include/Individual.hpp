#pragma once

struct Individual {
  int *vals;
  double eval_val;

  Individual(int dim) : vals(new int[dim]) {}
};
