
#include "operation/basic/vector-op.h"
#include "operation/basic/vector-io.h"
#include "data/basic/console-output.h"
#include "data/basic/console-input.h"
using namespace std;

int main() {

  COut<<"Test -- allocation"<<Endl;
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
  COut<<Endl;

  COut<<"Test -- availability test"<<Endl;
  long* pLong=NULL;
  Vector<long> vLong;
  COut<<IsAvailable(pLong)<<Endl;
  COut<<IsAvailable(pInt)<<Endl;
  COut<<IsAvailable(vLong)<<Endl;
  COut<<IsAvailable(vDBL)<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  delete pLong;
  COut<<pLong<<Endl;
  delete pUInt;
  COut<<pUInt<<Endl;
  release(vInt);
  COut<<vInt.data<<"\t"<<vInt.size<<"\t"<<vInt.state<<Endl;
  release(vLong);
  COut<<vLong.data<<"\t"<<vLong.size<<"\t"<<vLong.state<<Endl;
  COut<<Endl;

  COut<<"Test -- assign pointer and vector with pointer and constant"<<Endl;
  int* pInt2=NULL;
  double* pDBL2=NULL;
  delete pInt;
  pInt=new int[10];
  pInt2=new int[10];
  delete pDBL;
  pDBL=new double[10];
  pDBL2=new double[10];
  for(int i=0;i<9;++i)  pInt[i]=-1;
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  for(int i=0;i<5;++i)  pInt2[i]=pInt[i];
  for(unsigned int i=0;i<10;++i)  COut<<pInt2[i]<<" "; COut<<Endl;
  for(int i=0;i<9;++i)  pDBL[i]=-1.3;
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  for(int i=0;i<6;++i)  pDBL2[i]=pDBL[i];
  for(unsigned int i=0;i<10;++i)  COut<<pDBL2[i]<<" "; COut<<Endl;
  Vector<int> vInt2;
  allocate(vInt,10);
  allocate(vInt2,10);
  copy(vInt,2);
  COut<<vInt<<Endl;
  copy(vInt2,vInt);
  COut<<vInt2<<Endl;
  Vector<double> vDBL2;
  allocate(vDBL,10);
  allocate(vDBL2,10);
  copy(vDBL,1.5);
  COut<<vDBL<<Endl;
  copy(vDBL2,vDBL);
  COut<<vDBL2<<Endl;
  COut<<Endl;

  COut<<"Test -- scale pointer and vector"<<Endl;
  for(int i=0;i<5;++i) pInt[0+i*2]*=2;
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  scale(vInt,3);
  COut<<vInt<<Endl;
  for(int i=0;i<3;++i) pDBL[0+i*2]*=2;
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  scale(vDBL,1.2);
  COut<<vDBL<<Endl;
  for(int i=0;i<5;++i) pInt[i]*=pInt2[i];
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  scale(vInt,vInt2);
  COut<<vInt<<Endl;
  for(int i=0;i<3;++i) pInt[1+i*3]*=static_cast<int>(pDBL2[i]);
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  scale(vDBL,vDBL2);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- shift with constant and vector"<<Endl;
  for(int i=0;i<4;++i)  pInt[i]+=-2*pInt2[i];
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  for(int i=0;i<5;++i)  pDBL[1+i]+=2.5*pDBL2[2+i];
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  shift(vInt,-2,vInt2);
  COut<<vInt<<Endl;
  shift(vDBL,2.5,vDBL2);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- shift with vector only"<<Endl;
  for(int i=0;i<4;++i)  pInt[1+i]+=pInt2[2+i];
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  for(int i=0;i<4;++i)  pDBL[1+i]+=2.5*pDBL2[1+i];
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  shift(vInt,vInt2);
  COut<<vInt<<Endl;
  shift(vDBL,vDBL2);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- shift with constant only"<<Endl;
  for(int i=0;i<4;++i)  pInt[2+i]+=3;
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  for(int i=0;i<2;++i)  pDBL[2+i*3]+=3.5;
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  shift(vInt,7);
  COut<<vInt<<Endl;
  shift(vDBL,-2.4);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- shift with components with different order only"<<Endl;
  shift(vInt,vInt2,-2);
  COut<<vInt<<Endl;
  shift(vDBL,vDBL2,-3.5);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- scale-shift operation with all components"<<Endl;
  int* pInt3=NULL;
  pInt3=new int[10];
  for(int i=0;i<5;++i) pInt3[1+i]=pInt[i];
  for(int i=0;i<7;++i) pInt[i]=pInt[i]*(-4)+2*pInt3[i]*pInt2[i];
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  double* pDBL3=NULL;
  pDBL3=new double[10];
  for(int i=0;i<2;++i)  pDBL3[4+i]=pDBL2[i];
  for(int i=0;i<7;++i) pDBL[1+i]=pDBL[1+i]*(-1.4)+2.1*pDBL3[i]*pDBL2[i];
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  Vector<int> vInt3;
  allocate(vInt3,10);
  copy(vInt3,vInt);
  scaleshift(vInt,4,-3,vInt3,vInt2);
  COut<<vInt<<Endl;
  Vector<double> vDBL3;
  allocate(vDBL3,11);
  copy(vDBL3,-3.5);
  scaleshift(vDBL,1.4,-2.1,vDBL3,vDBL2);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- scale-shift operation with simplified components"<<Endl;
  for(int i=0;i<6;++i) pInt[1+i]=pInt[1+i]*2-5*pInt2[i];
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  for(int i=0;i<4;++i) pDBL[1+i*2]=pDBL[1+i*2]*2.3-8.9*pDBL2[i];
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  scaleshift(vInt,-5,2,vInt2);
  COut<<vInt<<Endl;
  scaleshift(vDBL,-2.1,1.4,vDBL2);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- shift with a constant and two vectors"<<Endl;
  for(int i=0;i<9;++i) pInt[i]+=4*pInt2[i]*pInt3[i];
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  for(int i=0;i<8;++i) pDBL[1+i]+=-6.8*pDBL2[i]*pDBL3[i];
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  shift(vInt,5,vInt2,vInt3);
  COut<<vInt<<Endl;
  shift(vDBL,9.2,vDBL2,vDBL3);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- exchange two vectors"<<Endl;
  for(int i=0;i<5;++i) exchange(pInt[2+i],pInt2[1+i*2]);
  for(unsigned int i=0;i<10;++i)  COut<<pInt[i]<<" "; COut<<Endl;
  for(int i=0;i<5;++i) exchange(pDBL[2+i],pDBL2[1+i*2]);
  for(unsigned int i=0;i<10;++i)  COut<<pDBL[i]<<" "; COut<<Endl;
  exchange(vInt,vInt2);
  COut<<vInt<<Endl;
  exchange(vDBL,vDBL2);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- dot operation"<<Endl;
  int gi;
  gi=0; for(int i=0;i<5;++i) gi+=pInt[1+2*i]*pInt2[2+i];
  COut<<gi<<Endl;
  double gd;
  gd=0; for(int i=0;i<5;++i) gd+=pDBL[1+2*i]*pDBL2[2+i];
  COut<<gd<<Endl;
  COut<<dot(vInt,vInt2)<<Endl;
  COut<<dot(vDBL,vDBL2)<<Endl;
  COut<<Endl;

  COut<<"Test -- norm square operation"<<Endl;
  gi=0; for(int i=0;i<5;++i) gi+=pInt[3+i]*pInt[3+i];
  COut<<gi<<Endl;
  gd=0; for(int i=0;i<4;++i) gd+=pDBL[1+i*2]*pDBL[1+i*2];
  COut<<gd<<Endl;
  COut<<normSQ(vInt)<<Endl;
  COut<<normSQ(vDBL)<<Endl;
  COut<<Endl;

  COut<<"Test -- norm operation"<<Endl;
  gd=0; for(int i=0;i<3;++i) gd+=pDBL[2+i*2]*pDBL[2+i*2];
  COut<<sqrt(gd)<<Endl;
  COut<<norm(vDBL)<<Endl;
  COut<<Endl;

  COut<<"Test -- sum of absolute values"<<Endl;
  gi=0; for(int i=0;i<5;++i)  gi+=absval(pInt[1+2*i]);
  COut<<gi<<Endl;
  gd=0; for(int i=0;i<5;++i)  gd+=absval(pDBL[1+2*i]);
  COut<<gd<<Endl;
  COut<<asum(vInt)<<Endl;
  COut<<asum(vDBL)<<Endl;
  COut<<Endl;

  COut<<"Test -- read from istream"<<Endl;
  CIn>>vDBL;
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- swap two vectors"<<Endl;
  swap(vInt,vInt2);
  COut<<vInt<<Endl;
  swap(vDBL,vDBL2);
  COut<<vDBL<<Endl;
  COut<<Endl;

  COut<<"Test -- cross product"<<Endl;
  Vector<double> cva,cvb,cv;
  allocate(cva,3);
  allocate(cvb,10);
  allocate(cv,6);
  copy(cva,1.);
  for(unsigned int i=0;i<10;i++)  cvb[i]=i;
  copy(cv,0.);
  crossProd(cv,cva,cvb,1,2,0,1,1,3);
  COut<<cv<<Endl;
  COut<<Endl;

  return 1;
}

