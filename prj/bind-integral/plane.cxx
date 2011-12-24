
#include "io/console.h"
#include <cmath>
using namespace mysimulator;

const double em0=1;
const double rm0=0.2;
const double R=10;
const double Lc=2;
const double l0=2;
const double eb0=10;
const double T=0.1;

double em(const double& r) {
  return -em0*exp(-(r+r)/rm0);
}

double sm(const double& r) {
  return 2*log(r+r)-(r*r*4)/R;
}

double eb(const double& d) {
  double e=0;
  if(d<Lc)  e=-1;
  else e=-exp(-(d-Lc)/l0);
  return eb0*e;
}

double Z(const double& e) {
  return exp(-e/T);
}

int main() {
  double l,r,sr;
  double minr,maxr;
  double dr;
  double sum;
  l=1.;
  minr=0.002;
  maxr=10.;
  for(l=1.;l<20;l+=0.05) {
  for(r=minr;r<maxr;r+=0.003) {
    sr=(l>r?r:l);
    dr=sr/1000.;
    sum=0;
    sum=0.5*Z(eb(l-sr));
    for(unsigned int i=1;i<2000;++i)
      sum+=Z(eb(l-sr+dr*i));
    sum+=0.5*Z(eb(l+sr));
    sum*=dr;
    sum/=r;
    COut<<l<<"\t"<<r<<"\t"<<-T*log(sum)+em(r)-T*sm(r)-T*log(2*M_PI)<<Endl;
  }
  COut<<Endl;
  }
  return 0;
}

