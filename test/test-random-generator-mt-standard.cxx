
#include "operation/random/random-generator-mt-standard-op.h"
#include "operation/random/random-generator-op.h"
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
  init(MS,122378);
  cout<<endl;

  cout<<"Test -- init with an array"<<endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(1+i)*(2+i);
  init(MS,v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  init(MS,rv);
  delete[] v;
  cout<<endl;

  cout<<"Test -- generate random number"<<endl;
  cout.precision(20);
  cout<<rand<unsigned int>(MS)<<endl;
  cout<<rand<int>(MS)<<endl;
  cout<<doubleClose0Close1(MS)<<endl;
  cout<<doubleClose0Open1(MS)<<endl;
  cout<<doubleOpen0Open1(MS)<<endl;
  cout<<double53bitSlow(MS)<<endl;
  cout<<rand<double>(MS)<<endl;
  cout<<rand<long double>(MS)<<endl;
  cout<<longdouble63bitSlow(MS)<<endl;
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
  allocate(rv,nhist);
  copy(rv,0);
  for(unsigned int i=0;i<nrnd;++i)
    rv[static_cast<unsigned int>(rand<double>(MS)*nhist)]++;
  cout<<"==========="<<endl;
  unsigned int nhhist=800;
  Vector<unsigned int> hv(nhhist);
  copy(hv,0);
  for(unsigned int i=0;i<nhist;++i) hv[rv[i]-600]++;
  cout<<"==========="<<endl;
  for(unsigned int i=0;i<nhhist;++i)  cout<<i<<"\t"<<hv[i]<<endl;
  cout<<"(The data has been checked, but is not output here)"<<endl;
  release(hv);
  release(rv);
  cout<<endl;

  return 0;

}

