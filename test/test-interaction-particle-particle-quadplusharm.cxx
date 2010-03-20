
#include "interaction-particle-particle-quadplusharm.h"
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- EFunc"<<endl;
  varDistanceEvalDirect vDED(3);
  varFreeSpace vFS;
  varVector<double> vd(6),gd(6);
  varVector<refVector<double> > v(2), g(2);
  v[0].refer(vd,0,3);
  v[1].refer(vd,3,3);
  v[0]=0.;
  v[1]=0.;  v[1][0]=1.2;
  g[0].refer(gd,0,3);
  g[1].refer(gd,3,3);
  varVector<unsigned int> vi(2);
  vi[0]=0;
  vi[1]=1;
  varVector<double> prm(QuadPlusHarm_NumberParameter);
  prm[0]=1.;
  prm[1]=10000.;
  prm[2]=100.;
  prm[3]=40000.;
  prm[4]=200.;
  double E=0.;
  EFunc_ParticleParticle_QuadPlusHarm<DistanceEvalDirectBase,FreeSpace,varVector,varVector>(v,vi,prm,vDED,vFS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  GFunc_ParticleParticle_QuadPlusHarm<DistanceEvalDirectBase,FreeSpace,varVector,varVector>(v,vi,prm,vDED,vFS,g);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  gd=0.;
  BFunc_ParticleParticle_QuadPlusHarm<DistanceEvalDirectBase,FreeSpace,varVector,varVector>(v,vi,prm,vDED,vFS,E,g);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 1;
}

