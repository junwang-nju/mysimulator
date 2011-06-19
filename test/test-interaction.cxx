

#include "interaction/func/interface.h"
#include "interaction/kernel/allocate.h"
#include "interaction/parameter/unit/allocate.h"
#include "interaction/calc.h"
#include "functional/harmonic/parameter/build.h"
#include "functional/lj612/parameter/build.h"
#include "functional/lj612cut/parameter/build.h"
#include "functional/lj1012/parameter/build.h"
#include "functional/lj1012cut/parameter/build.h"
#include "functional/core12/parameter/build.h"
#include "functional/corelj612/parameter/build.h"
#include "functional/coulomb/parameter/build.h"
#include "vector/allocate.h"
#include "geometry/distance/dbuffer-simple/calc.h"
#include "geometry/displacement/free/calc.h"
#include "buffer/distance/simple/allocate.h"
#include "boundary/free/allocate.h"
#include "vector/io.h"
#include "vector/fill.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  const unsigned int nunit=4;
  const unsigned int dim=2;
  const unsigned int nid=2;

  Vector<Vector<double> > X,G;
  allocate(X,nunit);
  allocate(G,nunit);
  for(unsigned int i=0;i<X.size;++i) allocate(X[i],dim);
  for(unsigned int i=0;i<G.size;++i) allocate(G[i],dim);
  X[0][0]=0.;       X[0][1]=0.;
  X[1][0]=1.2;      X[1][1]=0.;

  Vector<unsigned int> id;
  allocate(id,nid);
  id[0]=0;          id[1]=1;

  SimpleDistanceBuffer<double> SDB;
  allocate(SDB,dim,nunit);

  FreeSpace FS;
  allocate(FS,dim);

  Vector<UniqueParameter64Bit> Prm;
  double Energy;

  cout<<"Test Pairwise Harmonic:"<<endl;
  allocate(Prm,HarmonicNumberParameter);
  Prm[HarmonicEqLength].value<double>()=0.8;
  Prm[HarmonicEqStrength].value<double>()=100.;
  BuildParameterHarmonic<double>(Prm);
  Energy=0;
  InteractionFunc<Harmonic,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<"Calculate Energy only:"<<endl;
  cout<<"\t"<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<Harmonic,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<Harmonic,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  cout<<endl;
  cout<<"Test Pairwise LJ612:"<<endl;
  allocate(Prm,LJ612NumberParameter);
  Prm[LJ612EqRadius].value<double>()=1.;
  Prm[LJ612EqEnergyDepth].value<double>()=2.;
  BuildParameterLJ612<double>(Prm);
  Energy=0.;
  InteractionFunc<LJ612,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<"Calculate Energy only:"<<endl;
  cout<<"\t"<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<LJ612,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<LJ612,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  cout<<endl;
  cout<<"Test Pairwise LJ612Cut:"<<endl;
  allocate(Prm,LJ612CutNumberParameter);
  Prm[LJ612CutEqRadius].value<double>()=1.;
  Prm[LJ612CutEqEnergyDepth].value<double>()=2.;
  Prm[LJ612CutCutR].value<double>()=3.;
  BuildParameterLJ612Cut<double>(Prm);
  Energy=0.;
  InteractionFunc<LJ612Cut,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<"Calculate Energy only:"<<endl;
  cout<<"\t"<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<LJ612Cut,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<LJ612Cut,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  cout<<endl;
  cout<<"Test Pairwise LJ1012:"<<endl;
  allocate(Prm,LJ1012NumberParameter);
  Prm[LJ1012EqRadius].value<double>()=1.;
  Prm[LJ1012EqEnergyDepth].value<double>()=2.;
  BuildParameterLJ1012<double>(Prm);
  Energy=0.;
  InteractionFunc<LJ1012,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<"Calculate Energy only:"<<endl;
  cout<<"\t"<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<LJ1012,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<LJ1012,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  cout<<endl;
  cout<<"Test Pairwise LJ1012Cut:"<<endl;
  allocate(Prm,LJ1012CutNumberParameter);
  Prm[LJ1012CutEqRadius].value<double>()=1.;
  Prm[LJ1012CutEqEnergyDepth].value<double>()=2.;
  Prm[LJ1012CutCutR].value<double>()=3.;
  BuildParameterLJ1012Cut<double>(Prm);
  Energy=0.;
  InteractionFunc<LJ1012Cut,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<"Calculate Energy only:"<<endl;
  cout<<"\t"<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<LJ1012Cut,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<LJ1012Cut,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  cout<<endl;
  cout<<"Test Pairwise Core12:"<<endl;
  allocate(Prm,Core12NumberParameter);
  Prm[Core12EqStrength].value<double>()=1.;
  BuildParameterCore12<double>(Prm);
  Energy=0.;
  InteractionFunc<Core12,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<"Calculate Energy only:"<<endl;
  cout<<"\t"<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<Core12,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<Core12,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  cout<<endl;
  cout<<"Test Pairwise CoreLJ612:"<<endl;
  allocate(Prm,CoreLJ612NumberParameter);
  Prm[CoreLJ612Radius].value<double>()=1.5;
  Prm[CoreLJ612EnergyDepth].value<double>()=1.;
  BuildParameterCoreLJ612<double>(Prm);
  Energy=0.;
  InteractionFunc<CoreLJ612,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<"Calculate Energy only:"<<endl;
  cout<<"\t"<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<CoreLJ612,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<CoreLJ612,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  cout<<endl;
  cout<<"Test Pairwise Coulomb:"<<endl;
  allocate(Prm,CoulombNumberParameter);
  Prm[CoulombStrength].value<double>()=2.0;
  BuildParameterCoulomb<double>(Prm);
  Energy=0.;
  InteractionFunc<Coulomb,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<"Calculate Energy only:"<<endl;
  cout<<"\t"<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<Coulomb,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<Coulomb,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  cout<<endl;
  InteractionKernel<SimpleDistanceBuffer,FreeSpace,double> K,K1;
  cout<<"Before Allocation: status of object is:\t";
  cout<<IsValid(K)<<endl;
  allocate(K,Harmonic,4,2);
  cout<<"After Allocation: status of object is:\t";
  cout<<IsValid(K)<<endl;
  imprint(K1,K);
  cout<<"After Imprint: status of object is:\t";
  cout<<IsValid(K1)<<endl;
  release(K1);
  cout<<"After Release: status of object is:\t";
  cout<<IsValid(K1)<<endl;

  cout<<endl;
  InteractionParameterUnit P,P1;
  cout<<"Before Allocation: status of object is:\t";
  cout<<IsValid(P)<<endl;
  allocate(P,Harmonic);
  cout<<"After Allocation: status of object is:\t";
  cout<<IsValid(P)<<endl;
  imprint(P1,P);
  cout<<"After Imprint: status of object is:\t";
  cout<<IsValid(P1)<<endl;
  release(P1);
  cout<<"After Release: status of object is:\t";
  cout<<IsValid(P1)<<endl;

  cout<<endl;
  P.idx[0]=0;
  P.idx[1]=1;
  P.prm[HarmonicEqLength].value<double>()=0.8;
  P.prm[HarmonicEqStrength].value<double>()=100.;
  BuildParameterHarmonic<double>(P.prm);
  Energy=0.;
  Calc(K,X.pdata,P,Energy);
  cout<<"Calculate Energy only:"<<endl;
  cout<<Energy<<endl;
  fill(G,0.);
  Calc(K,X.pdata,P,G.pdata);
  cout<<"Calculate Gradient only:"<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;
  Energy=0.;
  fill(G,0.);
  Calc(K,X.pdata,P,Energy,G.pdata);
  cout<<"Calculate Energy and Gradient both:"<<endl;
  cout<<Energy<<endl;
  COut<<"\t"<<G[id[0]]<<Endl;
  COut<<"\t"<<G[id[1]]<<Endl;

  return 0;
}

