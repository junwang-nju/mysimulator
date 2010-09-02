
#include "property-list.h"
#include <iostream>
using namespace std;

const double e=0.1;
const double a=0.1;
const double b=0.1;
const double c=100;
const double D=0.001;
const double tau0=5;

double F1(const double& x, const double& y) {
  return (e*e+x*x)/(1+x*x)/(1+y)-a*x;
}

double F2(const double& x, const double& y) {
  return (b-y/(1+c*x*x))/tau0;
}

int main() {
  PropertyList<double> ru,nru;
  Vector<unsigned int> sz;
  allocate(sz,201);
  assign(sz,201);
  allocate(ru,sz);
  allocate(nru,sz);
  assign(ru,1.);
  for(unsigned int i=0;i<201;++i) {
    ru[0][i]=0;
    ru[200][i]=0;
    ru[i][0]=0;
    ru[i][200]=0;
  }
  double S=1./asum(ru);
  scale(ru,S);

  double dx=0.05;
  double dt=0.002;
  for(unsigned int rt=0;rt<100000000;++rt) {
    for(unsigned int i=2;i<=198;++i)
    for(unsigned int j=2;j<=198;++j) {
      S=((ru[i+1][j]+ru[i-1][j])+(ru[i][j+1]+ru[i][j-1])-4*ru[i][j])/(dx*dx);
      S*=D;
      S-=(F1((i+1)*dx,j*dx)*ru[i+1][j]-F1((i-1)*dx,j*dx)*ru[i-1][j])/(2*dx);
      S-=(F2(i*dx,(j+1)*dx)*ru[i][j+1]-F2(i*dx,(j-1)*dx)*ru[i][j-1])/(2*dx);
      nru[i][j]=ru[i][j]+dt*S;
    }
    for(unsigned int i=2;i<=198;++i) {
      S=((ru[i+1][1]+ru[i-1][1])+(ru[i][2]+ru[i][1])-4*ru[i][1])/(dx*dx);
      S*=D;
      S-=(F1((i+1)*dx,1*dx)*ru[i+1][1]-F1((i-1)*dx,1*dx)*ru[i-1][1])/(2*dx);
      S-=(F2(i*dx,2*dx)*ru[i][2]+F2(i*dx,dx)*ru[i][1])/(2*dx);
      nru[i][1]=ru[i][1]+dt*S;
    }
    for(unsigned int i=2;i<=198;++i) {
      S=((ru[i+1][199]+ru[i-1][199])+(ru[i][199]+ru[i][198])-4*ru[i][199])/(dx*dx);
      S*=D;
      S-=(F1((i+1)*dx,199*dx)*ru[i+1][199]-F1((i-1)*dx,199*dx)*ru[i-1][199])/(2*dx);
      S-=-(F2(i*dx,199*dx)*ru[i][199]+F2(i*dx,198*dx)*ru[i][198])/(2*dx);
      nru[i][199]=ru[i][199]+dt*S;
    }
    for(unsigned int j=2;j<=198;++j) {
      S=((ru[2][j]+ru[1][j])+(ru[1][j+1]+ru[1][j-1])-4*ru[1][j])/(dx*dx);
      S*=D;
      S-=(F1(2*dx,j*dx)*ru[2][j]+F1(dx,j*dx)*ru[1][j])/(2*dx);
      S-=(F2(dx,(j+1)*dx)*ru[1][j+1]-F2(dx,(j-1)*dx)*ru[1][j-1])/(2*dx);
      nru[1][j]=ru[1][j]+dt*S;
    }
    for(unsigned int j=2;j<=198;++j) {
      S=((ru[199][j]+ru[198][j])+(ru[199][j+1]+ru[199][j-1])-4*ru[199][j])/(dx*dx);
      S*=D;
      S-=-(F1(199*dx,j*dx)*ru[199][j]+F1(198*dx,j*dx)*ru[198][j])/(2*dx);
      S-=(F2(199*dx,(j+1)*dx)*ru[199][j+1]-F2(199*dx,(j-1)*dx)*ru[199][j-1])/(2*dx);
      nru[199][j]=ru[199][j]+dt*S;
    }
    S=((ru[2][1]+ru[1][1])+(ru[1][2]+ru[1][1])-4*ru[1][1])/(dx*dx);
    S*=D;
    S-=(F1(2*dx,dx)*ru[2][1]+F1(dx,dx)*ru[1][1])/(2*dx);
    S-=(F2(dx,2*dx)*ru[1][2]+F2(dx,dx)*ru[1][1])/(2*dx);
    nru[1][1]=ru[1][1]+dt*S;
    S=((ru[2][199]+ru[1][199])+(ru[1][199]+ru[1][198])-4*ru[1][199])/(dx*dx);
    S*=D;
    S-=(F1(2*dx,199*dx)*ru[2][199]+F1(dx,199*dx)*ru[1][199])/(2*dx);
    S-=-(F2(dx,199*dx)*ru[1][199]+F2(dx,198*dx)*ru[1][198])/(2*dx);
    nru[1][199]=ru[1][199]+dt*S;
    S=((ru[199][1]+ru[198][1])+(ru[199][2]+ru[199][1])-4*ru[199][1])/(dx*dx);
    S*=D;
    S-=-(F1(199*dx,dx)*ru[199][1]+F1(198*dx,dx)*ru[198][1])/(2*dx);
    S-=(F2(199*dx,2*dx)*ru[199][2]+F2(199*dx,dx)*ru[199][1])/(2*dx);
    nru[199][1]=ru[199][1]+dt*S;
    S=((ru[199][199]+ru[198][199])+(ru[199][199]+ru[199][198])-4*ru[199][199])/(dx*dx);
    S*=D;
    S-=-(F1(199*dx,199*dx)*ru[199][199]+F1(198*dx,199*dx)*ru[198][199])/(2*dx);
    S-=-(F2(199*dx,199*dx)*ru[199][199]+F2(199*dx,198*dx)*ru[199][198])/(2*dx);
    nru[199][199]=ru[199][199]+dt*S;
    ru=nru;
    if(rt%20==0)
      cout<<rt*dt<<"\t"<<ru[40][40]<<"\t"<<ru[2][40]<<"\t"<<ru[80][40]<<"\t"<<ru[40][10]<<endl;
  }

  return 0;
}

