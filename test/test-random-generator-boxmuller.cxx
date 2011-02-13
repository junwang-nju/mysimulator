
#include "operation/random/random-generator-boxmuller-io.h"
#include "operation/random/random-generator-boxmuller-op.h"
#include "operation/random/random-generator-op.h"
#include "data/basic/console-output.h"
#include "data/basic/string-buffer-output.h"
#include "data/basic/string-buffer-input.h"
#include "operation/random/random-generator-mt-dsfmt-io.h"
using namespace std;

int main() {
  COut.precision(20);
  COut<<"Test -- initialize"<<Endl;
  BoxMuller<dSFMT<19937> > bm;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(bm);
  COut<<Endl;

  COut<<"Test -- init with a seed"<<Endl;
  init(bm,1227389);
  COut<<Endl;

  COut<<"Test -- other interfaces to generate random numbers"<<Endl;
  COut<<rand<double>(bm)<<Endl;
  COut<<Endl;

  COut<<"Test -- generate a vector of random data"<<Endl;
  double *v=new double[1000];
  fillarray(bm,v,900,20,1);
  Vector<double> rv;
  refer(rv,v,1000);
  fillarray(bm,rv);
  COut<<Endl;

  COut<<"Test -- save and load status of generator"<<Endl;
  const unsigned int nbuff=409600;
  char buffer[nbuff];
  StringOutput SO(buffer,nbuff);
  StringInput SI(buffer,nbuff);
  Vector<UniqueParameter128b> vbefore, vafter;
  unsigned int ncmp=10;
  allocate(vbefore,ncmp);
  allocate(vafter,ncmp);
  SO<<bm;
  fillarray(bm,vbefore()->d,ncmp*2);
  SI>>bm;
  fillarray(bm,vafter()->d,ncmp*2);
  for(unsigned int i=0;i<ncmp+ncmp;++i)
    if(vbefore()->ull[i]!=vafter()->ull[i]) COut<<i<<"\tNot Equal"<<Endl;
  COut<<Endl;

  COut<<"Test -- distribution"<<Endl;
  unsigned int nhist=10000,nrnd=nhist*1000,hnhist=nhist/2,whist=1000;
  Vector<unsigned int> iv(nhist);
  copy(iv,0U);
  for(unsigned int i=0,m;i<nrnd;++i) {
    m=static_cast<unsigned int>(rand<double>(bm)*whist+hnhist);
    if((m>=0)&&(m<nhist)) iv[m]++;
  }
  for(unsigned int i=0;i<nhist;++i) COut<<i<<"\t"<<iv[i]<<Endl;
  COut<<"(data has been checked, but is not output here)"<<Endl;
  COut<<Endl;

  return 1;
}

