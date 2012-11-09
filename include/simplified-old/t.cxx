
#include "array/interface.h"
//#include "array-2d/interface.h"
using namespace mysimulator;

#include <iostream>
#include <ctime>
using namespace std;

int main() {
  cout.precision(12);
  const unsigned int N=8;
  Array<Double>  A(N),B(N),C(N);
  for(unsigned int i=0;i<N;++i)  B[i]=i+5;
  clock_t t1=clock();
  for(unsigned int i=0;i<400000;++i)
    A+=Double(5.)/C;
  clock_t t2=clock();
  cout<<t2<<endl;
  cout<<((double)(t2-t1))/CLOCKS_PER_SEC<<endl;
  A+=((B*C)-Int(9))/B-C;
  return 0;
}

