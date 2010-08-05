
#include "vector.h"
#include "random-generator.h"
using namespace std;

double potential(const double& x) {
  double d;
  d=x*x;
  return d*d-2*d-0.3*x;
}

double gradient(const double& x) {
  double d;
  d=x*x;
  return 4*(d-1)*x-0.3;
}

int main() {
  double xc=-0.8;
  double x,v,f;
  x=-1.0;
  v=0;
  f=-gradient(x);

  double dt;
  double gamma;
  double T;
  double rsize;
  GaussianRNG grng;
  dt=0.001;
  gamma=1.;
  T=1;
  rsize=sqrt(2*gamma*T*(dt*0.5));
  allocate(grng);
  initWithTime(grng);

  Vector<double> state;
  allocate(state,50000);
  assign(state,0.);
  for(unsigned int z=0;z<10000;++z) {
    x=+0.2;
    v=0.;
    f=-gradient(x);
    for(unsigned int i=0;i<50000;++i) {
      v+=(f-gamma*v)*dt*0.5;
      v+=rand(grng)*rsize;
      x+=v*dt;
      f=-gradient(x);
      v+=f*dt*0.5+rand(grng)*rsize;
      v/=(1+gamma*dt*0.5);
      state[i]+=(x>xc?1:0);
      //cout<<i<<"\t"<<x<<"\t"<<v<<"\t"<<potential(x)+0.5*v*v<<endl;
    }
  }
  for(unsigned int i=0;i<50000;++i)
    cout<<i<<"\t"<<state[i]/10000.<<endl;
  return 0;
}

