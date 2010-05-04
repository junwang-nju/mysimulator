
#include "random-generator-mt-standard.h"
#include "random-generator-generic.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  cout<<"Test -- Initialize"<<endl;
  MT_Standard MS;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(MS);
  cout<<endl;

  cout<<"Test -- init with a seed"<<endl;
  MS.Init(122378);
  cout<<endl;

  cout<<"Test -- init with an array"<<endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(1+i)*(2+i);
  MS.Init(v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  MS.Init(rv);
  delete[] v;
  cout<<endl;

  cout<<"Test -- generate random number"<<endl;
  cout.precision(20);
  cout<<MS.UInt32()<<endl;
  cout<<MS.Int31()<<endl;
  cout<<MS.DoubleClose0Close1()<<endl;
  cout<<MS.DoubleClose0Open1()<<endl;
  cout<<MS.DoubleOpen0Open1()<<endl;
  cout<<MS.Double53Close0Open1()<<endl;
  cout<<MS.Double53Close0Open1Slow()<<endl;
  cout<<MS.LDouble63Close0Open1()<<endl;
  cout<<MS.LDouble63Close0Open1Slow()<<endl;
  cout<<endl;

  cout<<"Test -- other interface to generate random number"<<endl;
  cout<<rand(MS)<<endl;
  cout<<rand<unsigned int>(MS)<<endl;
  cout<<rand<int>(MS)<<endl;
  cout<<rand<double>(MS)<<endl;
  cout<<rand<long double>(MS)<<endl;
  cout<<endl;

  cout<<"Test -- generate a vector of random data"<<endl;
  v=new unsigned int[1000];
  fillarray(MS,v,900);
  refer(rv,v,1000);
  fillarray(MS,rv);
  delete[] v;
  cout<<endl;

  cout<<"Test -- save and load status of generator"<<endl;
  stringstream ss;
  Vector<unsigned int> vbefore,vafter;
  unsigned int ncmp=10;
  allocate(vbefore,ncmp);
  allocate(vafter,ncmp);
  ss<<MS;
  fillarray(MS,vbefore);
  ss>>MS;
  fillarray(MS,vafter);
  for(unsigned int i=0;i<ncmp;++i)
    if(vbefore[i]!=vafter[i]) cout<<i<<"\tNot Equal!"<<endl;
  cout<<endl;

  cout<<"Test -- degree of uniformness"<<endl;
  unsigned int nhist=100000, nrnd=nhist*1000;
  v=new unsigned int[nhist];
  assign(v,0U,nhist);
  for(unsigned int i=0;i<nrnd;++i)
    v[static_cast<unsigned int>(rand(MS)*nhist)]++;
  unsigned int nhhist=800;
  unsigned int *hv=new unsigned int[nhhist];
  assign(hv,0U,nhhist);
  for(unsigned int i=0;i<nhist;++i) hv[v[i]-600]++;
  cout<<"(The data has been checked, but is not output here)"<<endl;
  delete[] hv;
  delete[] v;
  cout<<endl;

  return 1;
}

