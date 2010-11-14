
#include "operation/random/random-generator-mt-dsfmt-op.h"
#include "operation/random/random-generator-op.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  dSFMT<216091> dg;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(dg);
  cout<<endl;

  cout<<"Test -- init with a seed"<<endl;
  init(dg,122378);
  cout<<endl;

  cout<<"Test -- init with an array"<<endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(i+1)*(i+2);
  init(dg,v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  init(dg,rv);
  delete[] v;
  cout<<endl;

  cout<<"Test -- other interfaces to generate random numbers"<<endl;
  cout<<rand<unsigned int>(dg)<<endl;
  cout<<doubleClose1Open2(dg)<<endl;
  cout<<doubleOpen0Close1(dg)<<endl;
  cout<<doubleOpen0Open1(dg)<<endl;
  cout<<endl;

  cout<<"Test -- generate a vector of random data"<<endl;
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
  cout<<ndv[0]<<"\t"<<ndv[9999]<<endl;
  Vector<double> rdv;
  refer(rdv,ndv,ndvsize);
  fillarray(dg,rdv); 
  cout<<ndv[0]<<"\t"<<ndv[9999]<<endl;
  fillarray(dg,ndv,1000,1,3);
  fillarrayClose1Open2(dg,ndv,ndvsize);
  fillarrayOpen0Close1(dg,ndv,ndvsize);
  fillarrayOpen0Open1(dg,ndv,ndvsize);
  cout<<endl;

  cout<<"Test -- save and load status of generator"<<endl;
  stringstream ss;
  Vector<unsigned int> vbefore, vafter;
  unsigned int ncmp=10;
  allocate(vbefore,ncmp);
  allocate(vafter,ncmp);
  ss<<dg;
  fillarray(dg,vbefore);
  ss>>dg;
  fillarray(dg,vafter);
  for(unsigned int i=0;i<ncmp;++i)
    if(vbefore[i]!=vafter[i]) cout<<i<<"\tNot Equal"<<endl;
  cout<<endl;

  cout<<"Test -- degree of uniformness"<<endl;
  unsigned int nhist=100000, nrnd=nhist*1000;
  allocate(rv,nhist);
  copy(rv,0U);
  for(unsigned int i=0;i<nrnd;++i)
    rv[static_cast<unsigned int>(rand<double>(dg)*nhist)]++;
  unsigned int nhhist=800;
  Vector<unsigned int> hv(nhhist);
  copy(hv,0U);
  for(unsigned int i=0;i<nhist;++i) hv[rv[i]-600]++;
  for(unsigned int i=0;i<nhhist;++i)  cout<<i<<"\t"<<hv[i]<<endl;
  cout<<"(The data has been checked, but is not output here)"<<endl;
  release(hv);
  release(rv);
  cout<<endl;

  return 1;
}

