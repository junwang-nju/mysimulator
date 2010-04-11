
#include "var-vector.h"
#include "random-generator.h"

#include <iostream>
using namespace std;

int main() {
  const unsigned int NUnit=20000;
  varVector<double> State(NUnit);
  State=1;
  UniformDbRNG urng(23813);
  unsigned int u,v;
  double sd,d;
  for(unsigned int i=0;i<100000000;++i) {
    u=static_cast<unsigned int>(urng()*NUnit);
    v=static_cast<unsigned int>(urng()*NUnit)+u+1;
    if(v>=NUnit)  v-=NUnit;
    sd=State[u]+State[v];
    d=urng()*sd;
    State[u]=d;
    State[v]=sd-d;
  }
  varVector<unsigned int> Hist(1000);
  Hist=0;
  for(unsigned int i=0;i<NUnit;++i)
    if(State[i]<10)
      ++Hist[static_cast<unsigned int>(State[i]/0.01)];
  for(unsigned int i=0;i<Hist.size();++i)
    cout<<i<<"\t"<<Hist[i]<<endl;
  return 1;
}

