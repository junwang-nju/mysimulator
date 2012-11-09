
#include "basic/unique-64.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  Unique U;
  (float&)U=1;
  double a=1.902;
  (void*&)U=&a;
  cout<<(*((const double*)U))<<endl;
  cout<<(&a)<<endl;
  return 0;
}

