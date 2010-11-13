
#include "operation/random/random-generator-mt-sfmt-op.h"
#include "operation/random/random-generator-op.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  SFMT<216091> sg;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(sg);
  cout<<endl;

  cout<<"Test -- init with a seed"<<endl;
  init(sg,122378);
  cout<<endl;

  cout<<"Test -- init with an array"<<endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(i+1)*(i+2);
  init(sg,v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  init(sg,rv);
  safe_delete_array(v);
  cout<<endl;

  cout<<"Test -- generate random numbers"<<endl;
  cout.precision(20);
  cout<<rand<unsigned int>(sg)<<endl;
  irand(sg);
  cout<<rand<unsigned long long int>(sg)<<endl;
  cout<<doubleClose0Close1(sg)<<endl;
  cout<<doubleClose0Open1(sg)<<endl;
  cout<<doubleOpen0Open1(sg)<<endl;
  cout<<double53bitSlow(sg)<<endl;
  cout<<rand<double>(sg)<<endl;
  irand(sg);
  cout<<rand<long double>(sg)<<endl;
  cout<<longdouble63bitSlow(sg)<<endl;
  cout<<endl;

  cout<<"Test -- generate a vector of random data"<<endl;
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
  cout<<endl;

  cout<<"Test -- save and load status of generator"<<endl;
  stringstream ss;
  Vector<unsigned int> vbefore,vafter;
  unsigned int ncmp=10;
  allocate(vbefore,ncmp);
  allocate(vafter,ncmp);
  ss<<sg;
  fillarray(sg,vbefore.data,ncmp,0,1);
  ss>>sg;
  fillarray(sg,vafter.data,ncmp,0,1);
  for(unsigned int i=0;i<ncmp;++i)
    if(vbefore[i]!=vafter[i]) cout<<i<<"\tNot Equal"<<endl;
  cout<<endl;

  cout<<"Test -- degree of uniformness"<<endl;
  unsigned int nhist=100000, nrnd=nhist*1000;
  allocate(rv,nhist);
  copy(rv,0U);
  for(unsigned int i=0;i<nrnd;++i)
    rv[static_cast<unsigned int>(rand<double>(sg)*nhist)]++;
  unsigned int nhhist=800;
  Vector<unsigned int> hv(nhhist);
  copy(hv,0U);
  for(unsigned int i=0;i<nhist;++i) hv[rv[i]-600]++;
  for(unsigned int i=0;i<nhhist;++i) cout<<i<<"\t"<<hv[i]<<endl;
  cout<<"(The data has been checked, but is not output here)"<<endl;
  release(hv);
  release(rv);
  cout<<endl;

  return 1;
}

