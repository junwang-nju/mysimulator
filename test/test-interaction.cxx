

#include "interaction/func/interface.h"
#include "functional/harmonic/parameter/build.h"
#include "functional/lj612/parameter/build.h"
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

  allocate(Prm,HarmonicNumberParameter);
  Prm[HarmonicEqLength].value<double>()=0.8;
  Prm[HarmonicEqStrength].value<double>()=100.;
  BuildParameterHarmonic<double>(Prm);
  Energy=0;
  InteractionFunc<Harmonic,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<Harmonic,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  COut<<G<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<Harmonic,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<Energy<<endl;
  COut<<G<<Endl;

  allocate(Prm,LJ612NumberParameter);
  Prm[LJ612EqRadius].value<double>()=1.;
  Prm[LJ612EqEnergyDepth].value<double>()=2.;
  BuildParameterLJ612<double>(Prm);
  Energy=0.;
  InteractionFunc<LJ612,SimpleDistanceBuffer,FreeSpace>::Energy(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,NULL);
  cout<<Energy<<endl;
  fill(G,0.);
  InteractionFunc<LJ612,SimpleDistanceBuffer,FreeSpace>::Gradient(X.pdata,id.pdata,Prm.pdata,SDB,FS,G.pdata,NULL);
  COut<<G<<Endl;
  Energy=0.;
  fill(G,0.);
  InteractionFunc<LJ612,SimpleDistanceBuffer,FreeSpace>::Both(X.pdata,id.pdata,Prm.pdata,SDB,FS,Energy,G.pdata,NULL);
  cout<<Energy<<endl;
  COut<<G<<Endl;

  return 0;
}

