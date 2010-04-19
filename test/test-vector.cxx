
#include "vector.h"
#include <iostream>
using namespace std;

int main() {

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

  long* pLong=NULL;
  Vector<long> vLong;
  cout<<IsPointerAvailable(pLong)<<endl;
  cout<<IsPointerAvailable(pInt)<<endl;
  cout<<IsVectorAvailable(vLong)<<endl;
  cout<<IsVectorAvailable(vDBL)<<endl;
  cout<<endl;

  release(pLong);
  cout<<pLong<<endl;
  release(pUInt);
  cout<<pUInt<<endl;
  release(vInt);
  cout<<vInt.data<<"\t"<<vInt.size<<"\t"<<vInt.state<<endl;
  release(vLong);
  cout<<vLong.data<<"\t"<<vLong.size<<"\t"<<vLong.state<<endl;

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

  shift(pInt,-2,pInt2,4);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  shift(pDBL,2.5,pDBL2,5,1,1,2,1);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,-2,vInt2);
  cout<<vInt<<endl;
  shift(vDBL,2.5,vDBL2);
  cout<<vDBL<<endl;

  shift(pInt,pInt2,4,1,1,2,1);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  shift(pDBL,pDBL2,4,2,1,1,1);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,vInt2);
  cout<<vInt<<endl;
  shift(vDBL,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  shift(pInt,3,4,2,1);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  shift(pDBL,3.5,2,2,3);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,7);
  cout<<vInt<<endl;
  shift(vDBL,-2.4);
  cout<<vDBL<<endl;

  shift(vInt,vInt2,-2);
  cout<<vInt<<endl;
  shift(vDBL,vDBL2,-3.5);
  cout<<vDBL<<endl;
  return 1;
}

