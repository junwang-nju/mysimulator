
#include "vector-impl.h"
#include <iostream>
using namespace std;

int main() {

  double dV1[10],dV2[10];
  for(unsigned int i=0;i<10;++i)  dV1[i]=i+0.5;
  for(unsigned int i=0;i<10;++i)  dV2[i]=0;
  vector_assign(dV2,dV1,4,1,2,0,1);
  for(unsigned int i=0;i<10;++i) cout<<dV2[i]<<" ";
  cout<<endl;

  int *iV1=new int[10],*iV2=new int[10];
  for(unsigned int i=0;i<10;++i)  iV1[i]=i+2;
  for(unsigned int i=0;i<10;++i)  iV2[i]=0;
  vector_assign(iV2,iV1,4,1,2,0,1);
  for(unsigned int i=0;i<10;++i) cout<<iV2[i]<<" ";
  cout<<endl;

  return 1;
}

