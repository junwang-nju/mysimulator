
#include "array/2d/allocate.h"
#include "array/2d/release.h"
#include "array/common/refer.h"
#include "array/2d/size.h"
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
  cout<<size(sz)<<endl;
  cout<<"============"<<endl;
  p=allocate<double>(sz);
  cout<<"============"<<endl;
  p[0][1]=1;
  p[1][2]=2;
  p[2][0]=3;
  p[3][4]=4;
  p[4][0]=5;
  double** q=NULL;
  refer(q,p);
  for(unsigned int i=0;i<5;++i) {
    for(unsigned int j=0;j<sz[i];++j) cout<<q[i][j]<<"\t";
    cout<<endl;
  }
  cout<<size(p)<<endl;
  release(p);
  for(unsigned int i=0;i<5;++i) {
    for(unsigned int j=0;j<sz[i];++j) cout<<q[i][j]<<"\t";
    cout<<endl;
  }
  cout<<endl;
  for(unsigned int i=0;i<5;++i)
    cout<<linesize(q,i)<<endl;
  return 0;
}

