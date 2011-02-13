
#include "operation/random/random-generator-mt-standard-op.h"
#include "operation/random/random-generator-mt-standard-io.h"
#include "operation/random/random-generator-op.h"
#include "data/basic/console-output.h"
#include "data/basic/string-buffer-output.h"
#include "data/basic/string-buffer-input.h"
using namespace std;

int main() {
  COut<<"Test -- Initialize"<<Endl;
  MT_Standard MS;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(MS);
  COut<<Endl;

  COut<<"Test -- init with a seed"<<Endl;
  init(MS,122378);
  COut<<Endl;

  COut<<"Test -- init with an array"<<Endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(1+i)*(2+i);
  init(MS,v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  init(MS,rv);
  delete[] v;
  COut<<Endl;

  COut<<"Test -- generate random number"<<Endl;
  COut.precision(20);
  COut<<rand<unsigned int>(MS)<<Endl;
  COut<<rand<int>(MS)<<Endl;
  COut<<doubleClose0Close1(MS)<<Endl;
  COut<<doubleClose0Open1(MS)<<Endl;
  COut<<doubleOpen0Open1(MS)<<Endl;
  COut<<double53bitSlow(MS)<<Endl;
  COut<<rand<double>(MS)<<Endl;
  COut<<rand<long double>(MS)<<Endl;
  COut<<longdouble63bitSlow(MS)<<Endl;
  COut<<Endl;

  COut<<"Test -- generate a vector of random data"<<Endl;
  v=new unsigned int[1000];
  fillarray(MS,v,900);
  refer(rv,v,1000);
  fillarray(MS,rv);
  delete[] v;
  COut<<Endl;

  COut<<"Test -- save and load status of generator"<<Endl;
  const unsigned int NBuffer=409600;
  char buff[NBuffer];
  StringOutput SO(buff,NBuffer);
  StringInput SI(buff,NBuffer);
  Vector<unsigned int> vbefore,vafter;
  unsigned int ncmp=10;
  allocate(vbefore,ncmp);
  allocate(vafter,ncmp);
  SO<<MS;
  fillarray(MS,vbefore);
  SI>>MS;
  fillarray(MS,vafter);
  for(unsigned int i=0;i<ncmp;++i)
    if(vbefore[i]!=vafter[i]) COut<<i<<"\tNot Equal!"<<Endl;
  COut<<Endl;

  COut<<"Test -- degree of uniformness"<<Endl;
  unsigned int nhist=100000, nrnd=nhist*1000;
  allocate(rv,nhist);
  copy(rv,0);
  for(unsigned int i=0;i<nrnd;++i)
    rv[static_cast<unsigned int>(rand<double>(MS)*nhist)]++;
  COut<<"==========="<<Endl;
  unsigned int nhhist=800;
  Vector<unsigned int> hv(nhhist);
  copy(hv,0);
  for(unsigned int i=0;i<nhist;++i) hv[rv[i]-600]++;
  COut<<"==========="<<Endl;
  for(unsigned int i=0;i<nhhist;++i)  COut<<i<<"\t"<<hv[i]<<Endl;
  COut<<"(The data has been checked, but is not output here)"<<Endl;
  release(hv);
  release(rv);
  COut<<Endl;

  return 0;

}

