
#include "ref-vector.h"
#include "var-vector.h"
#include <iostream>
using namespace std;

int main() {
  refVector<double> rdV;
  varVector<double> dV(10);
  rdV.refer(dV);
  dV=0;
  dV[2]=3;
  cout<<rdV<<endl;

  rdV.clear();
  cout<<rdV.IsAvailable()<<endl;
  cout<<dV<<endl;
  rdV.refer(dV);
  dV.clear();
  cout<<rdV.IsAvailable()<<endl;
  return 1;
}

