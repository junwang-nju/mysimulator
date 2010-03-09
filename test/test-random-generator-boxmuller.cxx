
#include "random-generator-interface.h"
#include "random-generator-boxmuller.h"
#include "random-generator-mt-dsfmt.h"
#include "fix-vector.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  typedef RandGenerator<dSFMT<216091>,double> UniformDbRNG;
  typedef RandGenerator<BoxMuller<UniformDbRNG>,double> GaussianRNG;

  GaussianRNG rg;
  GaussianRNG rg1(324287);

  rg.Init(23812);

  fixVector<double,901> dv;
  refVector<double> rv;
  BuildRationalVector(rg,dv,rv);
  rg.FillArray(rv.data(),800);
  rg.FillArray(rv);

  cout<<rg.GenRandNormal()<<endl;

  double d;
  cout<<rg()<<endl;
  cout<<rg.Default(d)<<endl;

  cout<<"Test -- save status"<<endl;
  fixVector<double,10> v1,v2;
  stringstream ss;
  rg.save(ss);
  for(unsigned int i=0;i<10;++i) v1[i]=rg.GenRandNormal();
  rg.load(ss);
  for(unsigned int i=0;i<10;++i) v2[i]=rg.GenRandNormal();
  cout<<scientific;
  cout.precision(20);
  for(unsigned int i=0;i<10;++i) {
    double g;
    g=fabs(v1[i]-v2[i]);
    cout<<"----------- "<<v1[i]+v2[i]<<endl;
    if(g<DRelDelta*0.5*(v1[i]+v2[i]))  cout<<i<<"\t"<<g<<"\t"<<"\tNot Equal!"<<endl;
  }
  cout<<endl;
  return 1;
}

