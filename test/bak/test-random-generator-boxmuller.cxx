
#include "random-generator-interface.h"
#include "random-generator-boxmuller.h"
#include "random-generator-mt-dsfmt.h"
#include "random-generator-mt-standard.h"
#include "fix-vector.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  typedef RandGenerator<dSFMT<216091>,double> UniformDbRNG;
  typedef RandGenerator<BoxMuller<UniformDbRNG>,double> GaussianRNG;

  cout<<"Test -- test init"<<endl;
  GaussianRNG rg;
  GaussianRNG rg1(324287);
  cout<<endl;

  cout<<"Test -- test Init function"<<endl;
  rg.Init(23812);
  cout<<endl;

  cout<<"Test -- test generate a value"<<endl;
  cout<<rg.GenRandNormal()<<endl;
  cout<<endl;

  cout<<"Test -- fill array"<<endl;
  fixVector<double,901> dv;
  refVector<double> rv;
  BuildRationalVector(rg,dv,rv);
  rg.FillArray(rv.data(),800);
  rg.FillArray(rv);
  cout<<endl;

  cout<<"Test -- default function"<<endl;
  double d;
  cout<<rg()<<endl;
  cout<<rg.Default(d)<<endl;
  cout<<endl;

  cout<<"Test -- save status"<<endl;
  fixVector<double,10> v1,v2;
  stringstream ss;
  rg.save(ss);
  for(unsigned int i=0;i<10;++i) v1[i]=rg.GenRandNormal();
  rg.load(ss);
  for(unsigned int i=0;i<10;++i) v2[i]=rg.GenRandNormal();
  cout<<scientific;
  cout.precision(20);
  for(unsigned int i=0;i<10;++i)
    if(fabs(v1[i]-v2[i])>DRelDelta*0.5*(fabs(v1[i])+fabs(v2[i])))
      cout<<"Not Equal!"<<endl;
  cout<<endl;

  cout<<"Test -- test distribution"<<endl;
  fixVector<unsigned int,20000> hist;
  hist=0u;
  for(unsigned int i=0;i<100000000;++i)
    hist[static_cast<unsigned int>(rg()*1000+10000)]++;
  return 1;
}

