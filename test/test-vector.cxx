
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

  return 1;
}

