
#include "random-generator-boxmuller.h"
#include "random-generator-generic.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  BoxMuller<dSFMT<19937> > bm;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(bm);
  cout<<endl;

  cout<<"Test -- init with a seed"<<endl;
  bm.Init(1227389);
  cout<<endl;

  cout<<"Test -- generate random numbers"<<endl;
  cout.precision(20);
  cout<<bm.DoubleNormal()<<endl;
  cout<<endl;

  cout<<"Test -- other interfaces to generate random numbers"<<endl;
  cout<<rand(bm)<<endl;
  cout<<rand<double>(bm)<<endl;
  cout<<endl;

  cout<<"Test -- generate a vector of random data"<<endl;
  double *v=new double[1000];
  fillarray(bm,v,900,20,1);
  Vector<double> rv;
  refer(rv,v,1000);
  fillarray(bm,rv);
  cout<<endl;

  cout<<"Test -- save and load status of generator"<<endl;
  stringstream ss;
  Vector<UniqueParameter128b> vbefore, vafter;
  unsigned int ncmp=10;
  allocate(vbefore,ncmp);
  allocate(vafter,ncmp);
  ss<<bm;
  fillarray(bm,vbefore()->d,ncmp*2);
  ss>>bm;
  fillarray(bm,vafter()->d,ncmp*2);
  for(unsigned int i=0;i<ncmp+ncmp;++i)
    if(vbefore()->ull[i]!=vafter()->ull[i]) cout<<i<<"\tNot Equal"<<endl;
  cout<<endl;

  cout<<"Test -- distribution"<<endl;
  unsigned int nhist=10000,nrnd=nhist*1000,hnhist=nhist/2,whist=1000;
  unsigned int *iv=new unsigned int[nhist];
  assign(iv,0U,nhist);
  for(unsigned int i=0,m;i<nrnd;++i) {
    m=static_cast<unsigned int>(rand(bm)*whist+hnhist);
    if((m>=0)&&(m<nhist)) iv[m]++;
  }
  //for(unsigned int i=0;i<nhist;++i) cout<<i<<"\t"<<iv[i]<<endl;
  cout<<"(data has been checked, but is not output here)"<<endl;
  cout<<endl;

  return 1;
}

