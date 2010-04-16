
#include "var-vector.h"
#include "random-generator.h"
#include <cmath>

#include <iostream>
using namespace std;

double min(double a, double b) {
  return (a<b?a:b);
}

int main() {
  const unsigned int NUnit=200000;
  varVector<double> State(NUnit);
  State=1;
  UniformDbRNG urng(23813);
  unsigned int u,v;
  double d;
  varVector<unsigned int> Hist(1000);
  Hist=0;
  for(unsigned int i=0;i<1000000000;++i) {
    u=static_cast<unsigned int>(urng()*NUnit);
    v=static_cast<unsigned int>(urng()*NUnit)+u+1;
    if(v>=NUnit)  v-=NUnit;
    //d=urng()*log(State[u]/2+1);
    d=urng()*(pow(State[u]+1,0.8)-1);
    State[u]-=d;
    State[v]+=d;
  }
  for(unsigned int i=0;i<NUnit;++i)
    if(State[i]<10)
      ++Hist[static_cast<unsigned int>(State[i]/0.01)];
  for(unsigned int i=0;i<Hist.size();++i)
    cout<<i<<"\t"<<Hist[i]<<endl;
  return 1;
}

