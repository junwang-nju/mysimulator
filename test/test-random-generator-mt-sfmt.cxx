
#include "operation/random/random-generator-mt-sfmt-op.h"
#include "operation/random/random-generator-op.h"
#include "operation/basic/console-output.h"
#include "operation/basic/string-buffer-input.h"
#include "operation/basic/string-buffer-output.h"
using namespace std;

int main() {
  COut<<"Test -- initialize"<<Endl;
  SFMT<216091> sg;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(sg);
  COut<<Endl;

  COut<<"Test -- init with a seed"<<Endl;
  init(sg,122378);
  COut<<Endl;

  COut<<"Test -- init with an array"<<Endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(i+1)*(i+2);
  init(sg,v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  init(sg,rv);
  safe_delete_array(v);
  COut<<Endl;

  COut<<"Test -- generate random numbers"<<Endl;
  //COut.precision(20);
  COut<<rand<unsigned int>(sg)<<Endl;
  irand(sg);
  COut<<rand<unsigned long long int>(sg)<<Endl;
  COut<<doubleClose0Close1(sg)<<Endl;
  COut<<doubleClose0Open1(sg)<<Endl;
  COut<<doubleOpen0Open1(sg)<<Endl;
  COut<<double53bitSlow(sg)<<Endl;
  COut<<rand<double>(sg)<<Endl;
  irand(sg);
  COut<<rand<long double>(sg)<<Endl;
  COut<<longdouble63bitSlow(sg)<<Endl;
  COut<<Endl;

  COut<<"Test -- generate a vector of random data"<<Endl;
  v=new unsigned int[10000];
  init(sg,328748327);
  fillarray(sg,v,9000);
  refer(rv,v,10000);
  fillarray(sg,rv);
  fillarray(sg,v,9000,5,1);
  safe_delete_array(v);
  double *dv=new double[100000];
  fillarray(sg,dv,10000);
  fillarray(sg,dv,10000,1,3);
  Vector<double> rdv;
  refer(rdv,dv,90000);
  fillarray(sg,rdv);
  safe_delete_array(dv);
  init(sg,2382261);
  unsigned long long int *lv=new unsigned long long int[10000];
  fillarray(sg,lv,5000);
  Vector<unsigned long long int> rlv;
  refer(rlv,lv,8000);
  fillarray(sg,rlv);
  safe_delete_array(lv);
  COut<<Endl;

  COut<<"Test -- save and load status of generator"<<Endl;
  const unsigned int nbuff=409600;
  char buffer[nbuff];
  StringOutput SO(buffer,nbuff);
  StringInput SI(buffer,nbuff);
  Vector<unsigned int> vbefore,vafter;
  unsigned int ncmp=10;
  allocate(vbefore,ncmp);
  allocate(vafter,ncmp);
  SO<<sg;
  fillarray(sg,vbefore.data,ncmp,0,1);
  SI>>sg;
  fillarray(sg,vafter.data,ncmp,0,1);
  for(unsigned int i=0;i<ncmp;++i)
    if(vbefore[i]!=vafter[i]) COut<<i<<"\tNot Equal"<<Endl;
  COut<<Endl;

  COut<<"Test -- degree of uniformness"<<Endl;
  unsigned int nhist=100000, nrnd=nhist*1000;
  allocate(rv,nhist);
  copy(rv,0U);
  for(unsigned int i=0;i<nrnd;++i)
    rv[static_cast<unsigned int>(rand<double>(sg)*nhist)]++;
  unsigned int nhhist=800;
  Vector<unsigned int> hv(nhhist);
  copy(hv,0U);
  for(unsigned int i=0;i<nhist;++i) hv[rv[i]-600]++;
  for(unsigned int i=0;i<nhhist;++i) COut<<i<<"\t"<<hv[i]<<Endl;
  COut<<"(The data has been checked, but is not output here)"<<Endl;
  release(hv);
  release(rv);
  COut<<Endl;

  return 1;
}

