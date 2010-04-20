
#include "vector.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- allocation"<<endl;
  int *pInt=NULL;
  unsigned int *pUInt=NULL;
  double *pDBL=NULL;
  float *pFLT=NULL;
  Vector<int> vInt;
  Vector<unsigned int> vUInt;
  Vector<double> vDBL;
  Vector<float> vFLT;
  allocate(pInt,10);
  allocate(pUInt,10);
  allocate(pDBL,10);
  allocate(pFLT,10);
  allocate(vInt,10);
  allocate(vUInt,10);
  allocate(vDBL,10);
  allocate(vFLT,10);
  cout<<endl;

  cout<<"Test -- availability test"<<endl;
  long* pLong=NULL;
  Vector<long> vLong;
  cout<<IsPointerAvailable(pLong)<<endl;
  cout<<IsPointerAvailable(pInt)<<endl;
  cout<<IsVectorAvailable(vLong)<<endl;
  cout<<IsVectorAvailable(vDBL)<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(pLong);
  cout<<pLong<<endl;
  release(pUInt);
  cout<<pUInt<<endl;
  release(vInt);
  cout<<vInt.data<<"\t"<<vInt.size<<"\t"<<vInt.state<<endl;
  release(vLong);
  cout<<vLong.data<<"\t"<<vLong.size<<"\t"<<vLong.state<<endl;
  cout<<endl;

  cout<<"Test -- assign pointer and vector with pointer and constant"<<endl;
  int* pInt2=NULL;
  double* pDBL2=NULL;
  allocate(pInt,10);
  allocate(pInt2,10);
  allocate(pDBL,10);
  allocate(pDBL2,10);
  assign(pInt,-1,9);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  assign(pInt2,pInt,5);
  for(unsigned int i=0;i<10;++i)  cout<<pInt2[i]<<" "; cout<<endl;
  assign(pDBL,-1.3,9);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  assign(pDBL2,pDBL,6);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL2[i]<<" "; cout<<endl;
  Vector<int> vInt2;
  allocate(vInt,10);
  allocate(vInt2,10);
  assign(vInt,2);
  cout<<vInt<<endl;
  assign(vInt2,vInt);
  cout<<vInt2<<endl;
  Vector<double> vDBL2;
  allocate(vDBL,10);
  allocate(vDBL2,10);
  assign(vDBL,1.5);
  cout<<vDBL<<endl;
  assign(vDBL2,vDBL);
  cout<<vDBL2<<endl;
  cout<<endl;

  cout<<"Test -- scale pointer and vector"<<endl;
  scale(pInt,2,5,0,2);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  scale(vInt,3);
  cout<<vInt<<endl;
  scale(pDBL,2,3,0,2);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  scale(vDBL,1.2);
  cout<<vDBL<<endl;
  scale(pInt,pInt2,5);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  scale(vInt,vInt2);
  cout<<vInt<<endl;
  scale(pDBL,pDBL2,3,1,3);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  scale(vDBL,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with constant and vector"<<endl;
  shift(pInt,-2,pInt2,4);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  shift(pDBL,2.5,pDBL2,5,1,1,2,1);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,-2,vInt2);
  cout<<vInt<<endl;
  shift(vDBL,2.5,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with vector only"<<endl;
  shift(pInt,pInt2,4,1,1,2,1);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  shift(pDBL,pDBL2,4,2,1,1,1);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,vInt2);
  cout<<vInt<<endl;
  shift(vDBL,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with constant only"<<endl;
  shift(pInt,3,4,2,1);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  shift(pDBL,3.5,2,2,3);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,7);
  cout<<vInt<<endl;
  shift(vDBL,-2.4);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with components with different order only"<<endl;
  shift(vInt,vInt2,-2);
  cout<<vInt<<endl;
  shift(vDBL,vDBL2,-3.5);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- scale-shift operation with all components"<<endl;
  int* pInt3=NULL;
  allocate(pInt3,10);
  assign(pInt3,pInt,5,1,1);
  scaleshift(pInt,-4,2,pInt3,pInt2,7);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  double* pDBL3=NULL;
  allocate(pDBL3,10);
  assign(pDBL3,pDBL2,2,4);
  scaleshift(pDBL,-1.4,2.1,pDBL3,pDBL2,7,1);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  Vector<int> vInt3;
  allocate(vInt3,10);
  assign(vInt3,vInt);
  scaleshift(vInt,4,-3,vInt3,vInt2);
  cout<<vInt<<endl;
  Vector<double> vDBL3;
  allocate(vDBL3,11);
  assign(vDBL3,-3.5);
  scaleshift(vDBL,1.4,-2.1,vDBL3,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- scale-shift operation with simplified components"<<endl;
  scaleshift(pInt,2,-5,pInt2,6,1);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  scaleshift(pDBL,2.3,-8.9,pDBL2,4,1,2);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  scaleshift(vInt,-5,2,vInt2);
  cout<<vInt<<endl;
  scaleshift(vDBL,-2.1,1.4,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with a constant and two vectors"<<endl;
  shift(pInt,4,pInt2,pInt3,9);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  shift(pDBL,-6.8,pDBL2,pDBL3,8,1);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,5,vInt2,vInt3);
  cout<<vInt<<endl;
  shift(vDBL,9.2,vDBL2,vDBL3);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- exchange two vectors"<<endl;
  exchange(pInt,pInt2,5,2,1,1,2);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  exchange(pDBL,pDBL2,5,2,1,1,2);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  exchange(vInt,vInt2);
  cout<<vInt<<endl;
  exchange(vDBL,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- dot operation"<<endl;
  cout<<dot(pInt,pInt2,5,1,2,2,1)<<endl;
  cout<<dot(pDBL,pDBL2,5,1,2,2,1)<<endl;
  cout<<dot(vInt,vInt2)<<endl;
  cout<<dot(vDBL,vDBL2)<<endl;
  cout<<endl;

  cout<<"Test -- norm square operation"<<endl;
  cout<<normSQ(pInt,5,3,1)<<endl;
  cout<<normSQ(pDBL,4,1,2)<<endl;
  cout<<normSQ(vInt)<<endl;
  cout<<normSQ(vDBL)<<endl;
  cout<<endl;

  cout<<"Test -- norm operation"<<endl;
  cout<<norm(pDBL,3,2,2)<<endl;
  cout<<norm(vDBL)<<endl;
  cout<<endl;

  cout<<"Test -- sum of absolute values"<<endl;
  cout<<asum(pInt,5,1,2)<<endl;
  cout<<asum(pDBL,5,1,2)<<endl;
  cout<<asum(vInt)<<endl;
  cout<<asum(vDBL)<<endl;
  cout<<endl;

  cout<<"Test -- read from istream"<<endl;
  cin>>vDBL;
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- swap two vectors"<<endl;
  swap(vInt,vInt2);
  cout<<vInt<<endl;
  swap(vDBL,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  return 1;
}

