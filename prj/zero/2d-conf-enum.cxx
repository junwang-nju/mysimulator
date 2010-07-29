
#include "vector.h"
#include <iostream>
using namespace std;

int main() {
  unsigned int L=9;
  unsigned int L1=8;

  Vector<int> dirc;
  Vector<int> X,Y;
  unsigned int YTurnHead,runHead;

  allocate(dirc,L1);
  allocate(X,L);
  allocate(Y,L);
  X[0]=0;     Y[0]=0;
  X[1]=1;     Y[1]=0;
  for(unsigned int i=0;i<L1;++i)  dirc[i]=0;
  YTurnHead=L1;
  runHead=L1;
  
  
  return 0;
}

