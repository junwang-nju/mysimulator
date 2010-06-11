
#include <iostream>
#include "random-generator.h"
using namespace std;

int main() {
  const unsigned int tau[]={50000,5000};
  const double k=0.1;
  const double T=0.5;
  const double V0=10;
  const double dt=0.001;

  GaussianRNG gng;
  allocate(gng);
  //init(gng,21389217);
  initWithTime(gng);

  double gammaS=0.5;
  double gammaB=5;
  double mS=1.;
  double mB=1000.;

  double xS,xB;
  double vS,vB;
  double gS,gB;
  double rS,rB;
  double bfS,bfB;
  double efS,efB;
  double htmS,htmB;
  unsigned int count,state;

  htmS=0.5*dt/mS;
  htmB=0.5*dt/mB;

  rS=sqrt(T*gammaS*dt)/mS;
  rB=sqrt(T*gammaB*dt)/mB;
  
  bfS=1.-gammaS*htmS;
  bfB=1.-gammaB*htmB;
  efS=1./(1.+gammaS*htmS);
  efB=1./(1.+gammaB*htmB);

  xS=xB=0.;
  vS=vB=0.;

  xB=1;

  gS=gB=0.;
  gB=2*k*(xB-xS);
  gS=-gB+V0*sin(xS*M_PI*2)*M_PI*2;

  count=0;
  state=0;
  for(unsigned int rt=0;rt<100000000;++rt) {
    if(count>=tau[state]){
      state=1-state;
      count=0;
    }
    vS*=bfS;
    vB*=bfB;
    vS+=-gS*htmS+rS*rand(gng);
    vB+=-gB*htmB+rB*rand(gng);

    xS+=vS*dt;
    xB+=vB*dt;

    gB=2*k*(xB-xS);
    gS=-gB;
    if(state==0)
      gS+=+V0*sin(xS*M_PI*2)*M_PI*2;

    vS+=-gS*htmS+rS*rand(gng);
    vB+=-gB*htmB+rB*rand(gng);
    vS*=efS;
    vB*=efB;

    if(rt%1000==0)
      cout<<rt*dt<<"\t"<<xS<<"\t"<<xB<<endl;
    count++;
  }

  return 0;
}

