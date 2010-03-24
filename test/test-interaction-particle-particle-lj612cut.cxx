
#include "interaction-particle-particle-lj612cut.h"
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
  varVector<double> prm(LJ612Cut_NumberParameter);
  prm[0]=1.;
  prm[1]=1.;
  prm[2]=4.;
  double r0rc=prm[LJ612Cut_EqRadius]/prm[LJ612Cut_CutR];
  double r0rc6;
  r0rc6=r0rc*r0rc*r0rc;
  r0rc6*=r0rc6;
  double r06;
  r06=prm[LJ612Cut_EqRadius];
  r06*=r06*r06;
  r06*=r06;
  prm[LJ612Cut_Sigma6]=r06*(1-r0rc6*r0rc)/(1-r0rc6*r0rc6*r0rc);
  double rc6;
  rc6=prm[LJ612Cut_CutR];
  rc6*=rc6*rc6;
  rc6*=rc6;
  double sgrc6=prm[LJ612Cut_Sigma6]/rc6;
  prm[LJ612Cut_Vc]=sgrc6*sgrc6-2*sgrc6;
  prm[LJ612Cut_Kc]=-12*sgrc6*(sgrc6-1)/prm[LJ612Cut_CutR];
  double sgr06=prm[LJ612Cut_Sigma6]/r06;
  double e=sgr06*(sgr06-2)-prm[LJ612Cut_Vc]-prm[LJ612Cut_Kc]*(prm[LJ612Cut_EqRadius]-prm[LJ612Cut_CutR]);
  prm[LJ612Cut_Strength]=-1./e;
  prm[LJ612Cut_Vc]*=prm[LJ612Cut_Strength];
  prm[LJ612Cut_Kc]*=prm[LJ612Cut_Strength];
  prm[LJ612Cut_TwlfStrength]=12.*prm[LJ612Cut_Strength];
  double E=0.;
  EFunc_ParticleParticle_LJ612Cut(v,vi,prm,vDED,vFS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  GFunc_ParticleParticle_LJ612Cut(v,vi,prm,vDED,vFS,g);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  gd=0.;
  BFunc_ParticleParticle_LJ612Cut(v,vi,prm,vDED,vFS,E,g);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 1;
}

