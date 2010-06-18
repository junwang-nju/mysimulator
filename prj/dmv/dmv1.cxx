
#include <iostream>
#include "random-generator.h"
using namespace std;

int main() {
  GaussianRNG gng;
  allocate(gng);
  init(gng,21389217);

  double T=0.5;
  double gamma=1;
  double dt=0.001;
  double DPI=M_PI+M_PI;

  double xl,xh;
  double vl,vh;
  double gl,gh;

  double k=0.002;
  double ml=1, mh=5000;
  double rl,rh;
  rl=sqrt(T*gamma*dt)/ml;
  rh=sqrt(T*gamma*dt)/mh;
  double flb,fla,fha,fhb;
  flb=1-gamma*dt*0.5/ml;
  fla=1./(1+gamma*dt*0.5/ml);
  fhb=1-gamma*dt*0.5/mh;
  fha=1./(1+gamma*dt*0.5/mh);

  xl=0; xh=-1.0;
  vl=vh=0.;

  gl=gh=0;
  gh=2*k*(xh-xl);
  gl=-gh+10*sin(xl*DPI)*DPI;

  double tau[]={15000,1000};
  int count, state;
  count=0;
  state=0;

  for(unsigned int rt=0;rt<1000000;++rt) {
    if(count>=tau[state]) {
      state=1-state;
      count=0;
    }
    vl*=flb;
    vl+=-gl*dt*0.5/ml+rl*rand(gng);
    vh*=fhb;
    vh+=-gh*dt*0.5/mh+rh*rand(gng);

    xl+=vl*dt;
    xh+=vh*dt;

    gl=gh=0;
    gh=2*k*(xh-xl);
    gl=-gh;
    if(state==0)
      gl+=+10*sin(xl*DPI)*DPI;

    vl+=-gl*dt*0.5/ml+rl*rand(gng);
    vl*=fla;
    vh+=-gh*dt*0.5/mh+rh*rand(gng);
    vh*=fha;
    if(rt%100==0)
    cout<<rt*dt<<"\t"<<xl<<"\t"<<xh<<endl;
    count++;
  }

  return 0;
}

