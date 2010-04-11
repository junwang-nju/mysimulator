
#include "var-vector.h"
#include "random-generator.h"

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
  unsigned int u,v,z;
  double sd,d;
  varVector<unsigned int> Hist(5000);
  Hist=0;
  for(unsigned int i=0;i<1000000000;++i) {
    u=static_cast<unsigned int>(urng()*NUnit);
    v=static_cast<unsigned int>(urng()*NUnit)+u+1;
    if(v>=NUnit)  v-=NUnit;
    z=(State[u]<State[v]?u:v);
    sd=State[u]+State[v];
    if(z==u) {
      d=urng()*(State[u]*2+min(State[u],(State[v]-State[u])*0.1));
      State[u]=d;
      State[v]=sd-d;
    } else  {
      d=urng()*(State[v]*2+min(State[u],(State[u]-State[v])*0.1));
      State[v]=d;
      State[u]=sd-d;
    }
    /*
    if(i>5000000)
    if((i+1)%50000==0)
      for(unsigned int i=0;i<NUnit;++i)
        if(State[i]<10)
          ++Hist[static_cast<unsigned int>(State[i]/0.01)];
          */
  }
      for(unsigned int i=0;i<NUnit;++i)
        if(State[i]<50)
          ++Hist[static_cast<unsigned int>(State[i]/0.01)];
  for(unsigned int i=0;i<Hist.size();++i)
    cout<<i<<"\t"<<Hist[i]<<endl;
  return 1;
}

