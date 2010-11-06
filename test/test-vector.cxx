
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
  pInt=new int[10];
  pUInt=new unsigned int[10];
  pDBL=new double[10];
  pFLT=new float[10];
  allocate(vInt,10);
  allocate(vUInt,10);
  allocate(vDBL,10);
  allocate(vFLT,10);
  cout<<endl;

  cout<<"Test -- availability test"<<endl;
  long* pLong=NULL;
  Vector<long> vLong;
  cout<<IsAvailable(pLong)<<endl;
  cout<<IsAvailable(pInt)<<endl;
  cout<<IsAvailable(vLong)<<endl;
  cout<<IsAvailable(vDBL)<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  delete pLong;
  cout<<pLong<<endl;
  delete pUInt;
  cout<<pUInt<<endl;
  release(vInt);
  cout<<vInt.data<<"\t"<<vInt.size<<"\t"<<vInt.state<<endl;
  release(vLong);
  cout<<vLong.data<<"\t"<<vLong.size<<"\t"<<vLong.state<<endl;
  cout<<endl;

  cout<<"Test -- assign pointer and vector with pointer and constant"<<endl;
  int* pInt2=NULL;
  double* pDBL2=NULL;
  delete pInt;
  pInt=new int[10];
  pInt2=new int[10];
  delete pDBL;
  pDBL=new double[10];
  pDBL2=new double[10];
  for(int i=0;i<9;++i)  pInt[i]=-1;
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  for(int i=0;i<5;++i)  pInt2[i]=pInt[i];
  for(unsigned int i=0;i<10;++i)  cout<<pInt2[i]<<" "; cout<<endl;
  for(int i=0;i<9;++i)  pDBL[i]=-1.3;
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  for(int i=0;i<6;++i)  pDBL2[i]=pDBL[i];
  for(unsigned int i=0;i<10;++i)  cout<<pDBL2[i]<<" "; cout<<endl;
  Vector<int> vInt2;
  allocate(vInt,10);
  allocate(vInt2,10);
  copy(vInt,2);
  cout<<vInt<<endl;
  copy(vInt2,vInt);
  cout<<vInt2<<endl;
  Vector<double> vDBL2;
  allocate(vDBL,10);
  allocate(vDBL2,10);
  copy(vDBL,1.5);
  cout<<vDBL<<endl;
  copy(vDBL2,vDBL);
  cout<<vDBL2<<endl;
  cout<<endl;

  cout<<"Test -- scale pointer and vector"<<endl;
  for(int i=0;i<5;++i) pInt[0+i*2]*=2;
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  scale(vInt,3);
  cout<<vInt<<endl;
  for(int i=0;i<3;++i) pDBL[0+i*2]*=2;
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  scale(vDBL,1.2);
  cout<<vDBL<<endl;
  for(int i=0;i<5;++i) pInt[i]*=pInt2[i];
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  scale(vInt,vInt2);
  cout<<vInt<<endl;
  for(int i=0;i<3;++i) pInt[1+i*3]*=pDBL2[i];
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  scale(vDBL,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with constant and vector"<<endl;
  for(int i=0;i<4;++i)  pInt[i]+=-2*pInt2[i];
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  for(int i=0;i<5;++i)  pDBL[1+i]+=2.5*pDBL2[2+i];
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,-2,vInt2);
  cout<<vInt<<endl;
  shift(vDBL,2.5,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with vector only"<<endl;
  for(int i=0;i<4;++i)  pInt[1+i]+=pInt2[2+i];
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  for(int i=0;i<4;++i)  pDBL[1+i]+=2.5*pDBL2[1+i];
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,vInt2,lOne);
  cout<<vInt<<endl;
  shift(vDBL,vDBL2,lOne);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with constant only"<<endl;
  for(int i=0;i<4;++i)  pInt[2+i]+=3;
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  for(int i=0;i<2;++i)  pDBL[2+i*3]+=3.5;
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
  pInt3=new int[10];
  for(int i=0;i<5;++i) pInt3[1+i]=pInt[i];
  for(int i=0;i<7;++i) pInt[i]=pInt[i]*(-4)+2*pInt3[i]*pInt2[i];
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  double* pDBL3=NULL;
  pDBL3=new double[10];
  for(int i=0;i<2;++i)  pDBL3[4+i]=pDBL2[i];
  for(int i=0;i<7;++i) pDBL[1+i]=pDBL[1+i]*(-1.4)+2.1*pDBL3[i]*pDBL2[i];
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  Vector<int> vInt3;
  allocate(vInt3,10);
  copy(vInt3,vInt);
  scaleshift(vInt,4,-3,vInt3,vInt2);
  cout<<vInt<<endl;
  Vector<double> vDBL3;
  allocate(vDBL3,11);
  copy(vDBL3,-3.5);
  scaleshift(vDBL,1.4,-2.1,vDBL3,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- scale-shift operation with simplified components"<<endl;
  for(int i=0;i<6;++i) pInt[1+i]=pInt[1+i]*2-5*pInt2[i];
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  for(int i=0;i<4;++i) pDBL[1+i*2]=pDBL[1+i*2]*2.3-8.9*pDBL2[i];
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  scaleshift(vInt,-5,2,vInt2);
  cout<<vInt<<endl;
  scaleshift(vDBL,-2.1,1.4,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- shift with a constant and two vectors"<<endl;
  for(int i=0;i<9;++i) pInt[i]+=4*pInt2[i]*pInt3[i];
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  for(int i=0;i<8;++i) pDBL[1+i]+=-6.8*pDBL2[i]*pDBL3[i];
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  shift(vInt,5,vInt2,vInt3);
  cout<<vInt<<endl;
  shift(vDBL,9.2,vDBL2,vDBL3);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- exchange two vectors"<<endl;
  for(int i=0;i<5;++i) exchange(pInt[2+i],pInt2[1+i*2]);
  for(unsigned int i=0;i<10;++i)  cout<<pInt[i]<<" "; cout<<endl;
  for(int i=0;i<5;++i) exchange(pDBL[2+i],pDBL2[1+i*2]);
  for(unsigned int i=0;i<10;++i)  cout<<pDBL[i]<<" "; cout<<endl;
  exchange(vInt,vInt2);
  cout<<vInt<<endl;
  exchange(vDBL,vDBL2);
  cout<<vDBL<<endl;
  cout<<endl;

  cout<<"Test -- dot operation"<<endl;
  int gi;
  gi=0; for(int i=0;i<5;++i) gi+=pInt[1+2*i]*pInt2[2+i];
  cout<<gi<<endl;
  double gd;
  gd=0; for(int i=0;i<5;++i) gd+=pDBL[1+2*i]*pDBL2[2+i];
  cout<<gd<<endl;
  cout<<dot(vInt,vInt2)<<endl;
  cout<<dot(vDBL,vDBL2)<<endl;
  cout<<endl;

  cout<<"Test -- norm square operation"<<endl;
  gi=0; for(int i=0;i<5;++i) gi+=pInt[3+i]*pInt[3+i];
  cout<<gi<<endl;
  gd=0; for(int i=0;i<4;++i) gd+=pDBL[1+i*2]*pDBL[1+i*2];
  cout<<gd<<endl;
  cout<<normSQ(vInt)<<endl;
  cout<<normSQ(vDBL)<<endl;
  cout<<endl;

  cout<<"Test -- norm operation"<<endl;
  gd=0; for(int i=0;i<3;++i) gd+=pDBL[2+i*2]*pDBL[2+i*2];
  cout<<sqrt(gd)<<endl;
  cout<<norm(vDBL)<<endl;
  cout<<endl;

  cout<<"Test -- sum of absolute values"<<endl;
  gi=0; for(int i=0;i<5;++i)  gi+=absval(pInt[1+2*i]);
  cout<<gi<<endl;
  gd=0; for(int i=0;i<5;++i)  gd+=absval(pDBL[1+2*i]);
  cout<<gd<<endl;
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

  cout<<"Test -- cross product"<<endl;
  Vector<double> cva,cvb,cv;
  allocate(cva,3);
  allocate(cvb,10);
  allocate(cv,6);
  copy(cva,1.);
  for(unsigned int i=0;i<10;i++)  cvb[i]=i;
  copy(cv,0.);
  crossProd(cva,cvb,cv,0,1,1,3,1,2);
  cout<<cv<<endl;
  cout<<endl;

  return 1;
}

