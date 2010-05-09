
#include "random-generator-mt-sfmt.h"
#include "random-generator-generic.h"
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
  sg.Init(122378);
  cout<<endl;

  cout<<"Test -- init with an array"<<endl;
  unsigned int *v=new unsigned int[100];
  for(unsigned int i=0;i<100;++i) v[i]=(i+1)*(i+2);
  sg.Init(v,40,1,2);
  Vector<unsigned int> rv;
  refer(rv,v,80);
  sg.Init(rv);
  safe_delete_array(v);
  cout<<endl;

  cout<<"Test -- generate random numbers"<<endl;
  cout.precision(20);
  cout<<sg.UInt32()<<endl;
  sg.UInt32();
  cout<<sg.UInt64()<<endl;
  cout<<sg.DoubleClose0Close1()<<endl;
  cout<<sg.DoubleClose0Open1()<<endl;
  cout<<sg.DoubleOpen0Open1()<<endl;
  cout<<sg.Double53Close0Open1()<<endl;
  cout<<sg.Double53Close0Open1Slow()<<endl;
  sg.UInt32();
  cout<<sg.LDouble63Close0Open1()<<endl;
  cout<<sg.LDouble63Close0Open1Slow()<<endl;
  cout<<endl;

  cout<<"Test -- other interface to generate random numbers"<<endl;
  cout<<rand(sg)<<endl;
  cout<<rand<unsigned int>(sg)<<endl;
  cout<<rand<double>(sg)<<endl;
  cout<<rand<unsigned long long int>(sg)<<endl;
  cout<<rand<long double>(sg)<<endl;
  cout<<endl;

  cout<<"Test -- generate a vector of random data"<<endl;
  v=new unsigned int[10000];
  sg.Init(328748327);
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
  sg.Init(2382261);
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
  fillarray(sg,vbefore(),ncmp,0,1);
  ss>>sg;
  fillarray(sg,vafter(),ncmp,0,1);
  for(unsigned int i=0;i<ncmp;++i)
    if(vbefore[i]!=vafter[i]) cout<<i<<"\tNot Equal"<<endl;
  cout<<endl;

  cout<<"Test -- degree of uniformness"<<endl;
  unsigned int nhist=100000, nrnd=nhist*1000;
  v=new unsigned int[nhist];
  assign(v,0U,nhist);
  for(unsigned int i=0;i<nrnd;++i)
    v[static_cast<unsigned int>(rand<double>(sg)*nhist)]++;
  unsigned int nhhist=800;
  unsigned int *hv=new unsigned int[nhhist];
  assign(hv,0U,nhhist);
  for(unsigned int i=0;i<nhist;++i) hv[v[i]-600]++;
  //for(unsigned int i=0;i<nhhist;++i) cout<<i<<"\t"<<hv[i]<<endl;
  cout<<"(The data has not been checked, but is not output here)"<<endl;
  safe_delete_array(hv);
  safe_delete_array(v);
  cout<<endl;

  return 1;
}

