
#include "random-generator-mt-dsfmt.h"
#include "random-generator-generic.h"
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
  dg.Init(122378);
  cout<<endl;

  cout<<"Test -- init with an array"<<endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(i+1)*(i+2);
  dg.Init(v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  dg.Init(rv);
  delete[] v;
  cout<<endl;

  cout<<"Test -- generate random numbers"<<endl;
  cout.precision(20);
  cout<<dg.UInt32()<<endl;
  cout<<dg.DoubleClose1Open2()<<endl;
  cout<<dg.DoubleClose0Open1()<<endl;
  cout<<dg.DoubleOpen0Close1()<<endl;
  cout<<dg.DoubleOpen0Open1()<<endl;
  cout<<endl;

  cout<<"Test -- other interfaces to generate random numbers"<<endl;
  cout<<rand(dg)<<endl;
  cout<<rand<double>(dg)<<endl;
  cout<<rand<unsigned int>(dg)<<endl;
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
  dg.fillarrayClose1Open2(ndv,ndvsize);
  dg.fillarrayClose0Open1(ndv,ndvsize);
  dg.fillarrayOpen0Close1(ndv,ndvsize);
  dg.fillarrayOpen0Open1(ndv,ndvsize);
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
  v=new unsigned int[nhist];
  assign(v,0U,nhist);
  for(unsigned int i=0;i<nrnd;++i)
    v[static_cast<unsigned int>(rand(dg)*nhist)]++;
  unsigned int nhhist=800;
  unsigned int *hv=new unsigned int[nhhist];
  assign(hv,0U,nhhist);
  for(unsigned int i=0;i<nhist;++i) hv[v[i]-600]++;
  //for(unsigned int i=0;i<nhhist;++i)  cout<<i<<"\t"<<hv[i]<<endl;
  cout<<"(The data has not been checked, but is not output here)"<<endl;
  delete[] hv;
  delete[] v;
  cout<<endl;

  return 1;
}

