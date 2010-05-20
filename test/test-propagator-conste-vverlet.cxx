
#include "propagator-op.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

template <typename DistEvalMethod, typename GeomType,
          typename IdxLstType, typename PrmLstType>
void OutFunc(ostream& os, const Propagator<DistEvalMethod,GeomType>& P,
             InteractionMethod<DistEvalMethod,GeomType>* IMLst,
             const Vector<double>* Coor, const Vector<double>* Vel,
             const Vector<double>* Grad, const Vector<double>* Mass,
             const IdxLstType *IdxLst, const PrmLstType* PrmLst,
             const unsigned int nunit, const unsigned int nlst,
             DistEvalMethod& DEval, const GeomType& Geo) {
  cout<<P.GParam[NowTime].d<<"\t"<<Coor[0]<<endl;
}

int main() {
  PropertyList<double> Coor,Vel,Grad,iMass,dMask;
  Vector<unsigned int> sz;
  allocate(sz,4);
  assign(sz,2);
  allocate(Coor,sz);
  allocate(Vel,sz);
  allocate(Grad,sz);
  allocate(iMass,sz);
  allocate(dMask,sz);

  Coor[0][0]=0;       Coor[0][1]=0;
  Coor[1][0]=0;       Coor[1][1]=1.2;
  Coor[2][0]=1.3;     Coor[2][1]=1.5;
  Coor[3][0]=0.8;     Coor[3][1]=2.2;
  assign(iMass,0.5);
  assign(dMask,1.);

  Vector<InteractionMethod<DistanceEvalDirect,FreeSpace> > IMLst;

  allocate(IMLst,6);
  for(unsigned int i=0;i<6;++i) allocate(IMLst[i]);
  for(unsigned int i=0;i<3;++i) Set(IMLst[i],PairwiseHarmonic);
  for(unsigned int i=3;i<6;++i) Set(IMLst[i],PairwiseLJ612);
  Vector<Vector<UniqueParameter> > fParamLst;
  allocate(fParamLst,6);
  for(unsigned int i=0;i<3;++i) allocate(fParamLst[i],HarmonicNumberParameter);
  for(unsigned int i=3;i<6;++i) allocate(fParamLst[i],LJ612NumberParameter);
  PropertyList<unsigned int> fIdxLst;
  allocate(sz,6);
  assign(sz,2);
  allocate(fIdxLst,sz);
  fParamLst[0][HarmonicEqLength]=2.;
  fParamLst[0][HarmonicEqStrength]=100.;
  fParamLst[1][HarmonicEqLength]=1.;
  fParamLst[1][HarmonicEqStrength]=100.;
  fParamLst[2][HarmonicEqLength]=0.5;
  fParamLst[2][HarmonicEqStrength]=100.;
  for(unsigned int i=0;i<3;++i) GenerateParameterHarmonic(fParamLst[i]);
  fParamLst[3][LJ612EqRadius]=0.8;
  fParamLst[3][LJ612EqEnergyDepth]=2.;
  fParamLst[4][LJ612EqRadius]=1.1;
  fParamLst[4][LJ612EqEnergyDepth]=3.;
  fParamLst[5][LJ612EqRadius]=0.5;
  fParamLst[5][LJ612EqEnergyDepth]=1.;
  for(unsigned int i=3;i<6;++i) GenerateParameterLJ612(fParamLst[i]);
  fIdxLst[0][0]=0;       fIdxLst[0][1]=1;
  fIdxLst[1][0]=0;       fIdxLst[1][1]=2;
  fIdxLst[2][0]=0;       fIdxLst[2][1]=3;
  fIdxLst[3][0]=1;       fIdxLst[3][1]=2;
  fIdxLst[4][0]=1;       fIdxLst[4][1]=3;
  fIdxLst[5][0]=2;       fIdxLst[5][1]=3;

  Propagator<DistanceEvalDirect,FreeSpace> P;
  allocate(P);
  Set(P,ConstantE_VelocityVerlet);
  assign(sz,ParticleType);
  buildUnit(P,ConstantE_VelocityVerlet,sz);

  cout<<"Test -- EV synchronize"<<endl;
  EVSynchronize(iMass.structure,dMask.structure,4,P.GParam());
  cout<<endl;

  cout<<"Test -- EV step"<<endl;
  cout<<endl;

  cout<<"Test -- simulation"<<endl;
  cout<<endl;

  return 0;
}

