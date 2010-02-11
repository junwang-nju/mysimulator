
#include "vector-impl.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"test -- vector_assign<double>"<<endl;
  double dV1[10],dV2[10];
  for(unsigned int i=0;i<10;++i)  dV1[i]=i+0.5;
  for(unsigned int i=0;i<10;++i)  dV2[i]=0;
  vector_assign(dV2,dV1,4,1,2,0,1);
  for(unsigned int i=0;i<10;++i) cout<<dV2[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Test -- vector_assign<int>"<<endl;
  int *iV1=new int[10],*iV2=new int[10];
  for(unsigned int i=0;i<10;++i)  iV1[i]=i+2;
  for(unsigned int i=0;i<10;++i)  iV2[i]=0;
  vector_assign(iV2,iV1,4,1,2,0,1);
  for(unsigned int i=0;i<10;++i) cout<<iV2[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Test -- vector_scale<double> of value"<<endl;
  vector_scale(dV2,2.5,7,0,1);
  for(unsigned int i=0;i<10;++i) cout<<dV2[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Test -- vector_scale<double> of array"<<endl;
  vector_scale(dV2,dV1,7,0,1,0,1);
  for(unsigned int i=0;i<10;++i) cout<<dV2[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Test -- vector_shift<double>"<<endl;
  vector_shift(dV2,2.,dV1,5,0,1,0,1);
  for(unsigned int i=0;i<10;++i) cout<<dV2[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Test -- vector_scaleshift<double>"<<endl;
  double dV3[10];
  for(unsigned int i=0;i<10;++i)  dV3[i]=9-i;
  vector_scaleshift(dV2,-1.,2.,dV3,dV1,7,1,1,2,1,0,1);
  for(unsigned int i=0;i<10;++i) cout<<dV2[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Test -- vector_exchange<double>"<<endl;
  vector_exchange(dV1,dV3,4,2,1,1,2);
  for(unsigned int i=0;i<10;++i) cout<<dV1[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Test -- vector_exchange<int>"<<endl;
  vector_exchange(iV1,iV2,4,2,1,1,2);
  for(unsigned int i=0;i<10;++i) cout<<iV1[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Test -- vector_dot<double>"<<endl;
  cout<<vector_dot(dV1,dV3,4,2,1,1,2)<<endl;
  cout<<endl;

  cout<<"Test -- vector_norm<double>"<<endl;
  cout<<vector_norm(dV1,5,2,1)<<endl;
  cout<<endl;

  cout<<"Test -- vector_asum<double>"<<endl;
  cout<<vector_asum(dV1,5,2,1)<<endl;
  cout<<endl;

  return 1;
}

