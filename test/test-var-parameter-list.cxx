
#include "var-parameter-list.h"
#include <iostream>
using namespace std;

int main() {
  varParameterList vPL;
  vPL.allocate(5);
  varVector<unsigned int> kS(7);
  fixVector<unsigned int,9> vS;
  kS=4;
  vS=6;
  vPL.allocate(kS,vS);
  return 1;
}