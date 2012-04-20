
#include "array/1d/allocate.h"
#include "array/2d/allocate.h"
#include "array/2d/release.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  unsigned int* sz;
  sz=allocate<unsigned int>(5);
  sz[0]=2;
  sz[1]=4;
  sz[2]=3;
  sz[3]=5;
  sz[4]=2;
  double** p=NULL;
  p=allocate<double>(sz);
  p[0][1]=1;
  p[1][2]=2;
  p[2][0]=3;
  p[3][4]=4;
  p[4][0]=5;
  for(unsigned int i=0;i<5;++i) {
    for(unsigned int j=0;j<sz[i];++j) cout<<p[i][j]<<"\t";
    cout<<endl;
  }
  cout<<size(p)<<endl;
  release(p);
  return 0;
}

