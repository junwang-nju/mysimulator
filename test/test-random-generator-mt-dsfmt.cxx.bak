
#include "operation/random/random-generator-mt-dsfmt-io.h"
#include "operation/random/random-generator-mt-dsfmt-op.h"
#include "operation/random/random-generator-op.h"
#include "data/basic/console-output.h"
#include "data/basic/string-buffer-output.h"
#include "data/basic/string-buffer-input.h"
using namespace std;

int main() {
  COut.precision(20);
  COut<<"Test -- initialize"<<Endl;
  dSFMT<216091> dg;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(dg);
  COut<<Endl;

  COut<<"Test -- init with a seed"<<Endl;
  init(dg,122378);
  COut<<Endl;

  COut<<"Test -- init with an array"<<Endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(i+1)*(i+2);
  init(dg,v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  init(dg,rv);
  delete[] v;
  COut<<Endl;

  COut<<"Test -- other interfaces to generate random numbers"<<Endl;
  COut<<rand<unsigned int>(dg)<<Endl;
  COut<<doubleClose1Open2(dg)<<Endl;
  COut<<doubleOpen0Close1(dg)<<Endl;
  COut<<doubleOpen0Open1(dg)<<Endl;
  COut<<Endl;

  COut<<"Test -- generate a vector of random data"<<Endl;
  v=new unsigned int[1000];
  fillarray(dg,v,900);
  refer(rv,v,1000);
  fillarray(dg,rv);
  delete[] v;
  double *dv=new double[100000];
  double *ndv;
  unsigned int ndvsize;
  ndv=dv; ndvsize=100000;
  fillarray(dg,ndv,ndvsize);
  COut<<ndv[0]<<"\t"<<ndv[9999]<<Endl;
  Vector<double> rdv;
  refer(rdv,ndv,ndvsize);
  fillarray(dg,rdv); 
  COut<<ndv[0]<<"\t"<<ndv[9999]<<Endl;
  fillarrayFast(dg,ndv,10000);
  fillarrayClose1Open2Fast(dg,ndv,ndvsize);
  fillarrayOpen0Close1Fast(dg,ndv,ndvsize);
  fillarrayOpen0Open1Fast(dg,ndv,ndvsize);
  fillarray(dg,ndv,1000,1,3);
  COut<<Endl;

  COut<<"Test -- save and load status of generator"<<Endl;
  const unsigned int nbuff=409600;
  char buffer[nbuff];
  StringOutput SO(buffer,nbuff);
  StringInput SI(buffer,nbuff);
  Vector<unsigned int> vbefore, vafter;
  unsigned int ncmp=10;
  allocate(vbefore,ncmp);
  allocate(vafter,ncmp);
  SO<<dg;
  fillarray(dg,vbefore);
  SI>>dg;
  fillarray(dg,vafter);
  for(unsigned int i=0;i<ncmp;++i)
    if(vbefore[i]!=vafter[i]) COut<<i<<"\tNot Equal"<<Endl;
  COut<<Endl;

  COut<<"Test -- degree of uniformness"<<Endl;
  unsigned int nhist=100000, nrnd=nhist*1000;
  allocate(rv,nhist);
  copy(rv,0U);
  for(unsigned int i=0;i<nrnd;++i)
    rv[static_cast<unsigned int>(rand<double>(dg)*nhist)]++;
  unsigned int nhhist=800;
  Vector<unsigned int> hv(nhhist);
  copy(hv,0U);
  for(unsigned int i=0;i<nhist;++i) hv[rv[i]-600]++;
  for(unsigned int i=0;i<nhhist;++i)  COut<<i<<"\t"<<hv[i]<<Endl;
  COut<<"(The data has been checked, but is not output here)"<<Endl;
  release(hv);
  release(rv);
  COut<<Endl;

  return 1;
}

