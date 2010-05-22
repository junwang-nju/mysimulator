
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
  double E,kE;
  E=kE=0.;
  EFunc(Coor,IdxLst,PrmLst,IMLst,6,DEval,Geo,E);
  for(unsigned int i=0;i<nunit;++i) kE+=normSQ(Vel[i])*Mass[i][0]*0.5;
  cout<<P.GParam[NowTime].d<<"\t"<<Coor[0]<<"\t"<<E<<"\t"<<kE<<endl;
}

int main() {
  PropertyList<double> Coor,Vel,Grad,Mass,iMass,dMask,RandV;
  Vector<unsigned int> sz;
  allocate(sz,4);
  assign(sz,2);
  allocate(Coor,sz);
  allocate(Vel,sz);
  allocate(Grad,sz);
  allocate(Mass,sz);
  allocate(iMass,sz);
  allocate(dMask,sz);
  allocate(RandV,sz);

  Coor[0][0]=0;       Coor[0][1]=0;
  Coor[1][0]=0;       Coor[1][1]=1.2;
  Coor[2][0]=1.3;     Coor[2][1]=1.5;
  Coor[3][0]=0.8;     Coor[3][1]=2.2;
  assign(Vel,0.);
  assign(Mass,2);
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
  fParamLst[0][HarmonicEqLength]=1.;
  fParamLst[0][HarmonicEqStrength]=100.;
  fParamLst[1][HarmonicEqLength]=1.;
  fParamLst[1][HarmonicEqStrength]=100.;
  fParamLst[2][HarmonicEqLength]=1.;
  fParamLst[2][HarmonicEqStrength]=100.;
  for(unsigned int i=0;i<3;++i) GenerateParameterHarmonic(fParamLst[i]);
  fParamLst[3][LJ612EqRadius]=1.;
  fParamLst[3][LJ612EqEnergyDepth]=1.;
  fParamLst[4][LJ612EqRadius]=1.;
  fParamLst[4][LJ612EqEnergyDepth]=1.;
  fParamLst[5][LJ612EqRadius]=1.;
  fParamLst[5][LJ612EqEnergyDepth]=1.;
  for(unsigned int i=3;i<6;++i) GenerateParameterLJ612(fParamLst[i]);
  fIdxLst[0][0]=0;       fIdxLst[0][1]=1;
  fIdxLst[1][0]=1;       fIdxLst[1][1]=2;
  fIdxLst[2][0]=2;       fIdxLst[2][1]=3;
  fIdxLst[3][0]=0;       fIdxLst[3][1]=2;
  fIdxLst[4][0]=0;       fIdxLst[4][1]=3;
  fIdxLst[5][0]=1;       fIdxLst[5][1]=3;

  DistanceEvalDirect DEval;
  FreeSpace FS;
  allocate(DEval,2,4);
  allocate(FS,2);

  assign(Grad,0.);
  GFunc(Coor.structure,fIdxLst.structure,fParamLst(),IMLst(),6,
        DEval,FS,Grad.structure);

  Propagator<DistanceEvalDirect,FreeSpace> P;
  allocate(P);
  Set(P,Langevin_VelocityVerlet);
  allocate(sz,4);
  assign(sz,ParticleType);
  buildUnit(P,sz);
  P.FOutput=OutFunc<DistanceEvalDirect,FreeSpace,
                    Vector<unsigned int>,Vector<UniqueParameter> >;
  P.HOutput=OutFunc<DistanceEvalDirect,FreeSpace,
                    Vector<Vector<unsigned int> >,
                    Vector<Vector<UniqueParameter> > >;

  setparameter(P,TimeStepCommon,0.001);
  setparameter(P,StartTimeCommon,100.);
  setparameter(P,TotalTimeCommon,0.01);
  setparameter(P,OutputTimeIntervalCommon,0.002);
  setparameter(P,TemperatureLV,0.5);
  setparameter(P,ViscosityLV,0.5);
  GaussianRNG gng;
  allocate(gng);
  init(gng,1237913);
  setparameter(P,GaussianRNGPointerLV,gng);
  for(unsigned int i=0;i<4;++i) {
    setparameter(P.Unit[i],HydrodynamicRadiusPLV,1.0);
    setparameter(P.Unit[i],RandomVelocityPointerPLV,RandV[i][0]);
  }

  cout<<"Test -- LV synchronize"<<endl;
  LVSynchronize(iMass.structure,dMask.structure,Vel.structure,4,P.GParam());
  cout<<endl;

  synchronize(P,iMass.structure,dMask.structure,Vel.structure,4);
  cout<<"Test -- LV step"<<endl;
  cout<<"=== Coor:"<<endl;
  cout<<Coor<<endl;
  cout<<"=== Vel:"<<endl;
  cout<<Vel<<endl;
  cout<<"=== Grad:"<<endl;
  cout<<Grad<<endl;
  LVStep(IMLst(),Coor.structure,Vel.structure,Grad.structure,Mass.structure,
         fIdxLst.structure,fParamLst(),P.GParam(),P.Unit(),4,6,
         DEval,FS);
  cout<<"=== Coor:"<<endl;
  cout<<Coor<<endl;
  cout<<"=== Vel:"<<endl;
  cout<<Vel<<endl;
  cout<<"=== Grad:"<<endl;
  cout<<Grad<<endl;
  cout<<endl;

  cout<<"Test -- simulation"<<endl;
  setparameter(P,TotalTimeCommon,200.);
  setparameter(P,OutputTimeIntervalCommon,0.001);
  synchronize(P,iMass.structure,dMask.structure,Vel.structure,4);
  Run(P,Coor.structure,Vel.structure,Grad.structure,Mass.structure,
      IMLst(),fIdxLst.structure,fParamLst(),4,6,DEval,FS);
  cout<<endl;

  return 0;
}

