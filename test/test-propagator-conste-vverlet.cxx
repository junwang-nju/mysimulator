
#include "operation/propagator/EV-move.h"
#include "operation/propagator/monomer-PEV-move.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/property-list.h"
#include "operation/interaction/interaction-calc.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-lj612.h"
#include "operation/parameter/build-param-propagator-conste-vverlet.h"
#include "operation/parameter/build-param-propagator-monomer-particle-conste-vverlet.h"
#include <iostream>
using namespace std;

/*
template <typename DistEvalMethod, typename GeomType,
          typename IdxLstType, typename PrmLstType>
void OutFunc(ostream& os, const Propagator<DistEvalMethod,GeomType>& P,
             InteractionMethod<DistEvalMethod,GeomType>* IMLst,
             const Vector<double>* Coor, const Vector<double>* Vel,
             const Vector<double>* Grad, const Vector<double>* Mass,
             const Vector<double>* dMask,
             const IdxLstType *IdxLst, const PrmLstType* PrmLst,
             const unsigned int nunit, const unsigned int nlst,
             DistEvalMethod& DEval, const GeomType& Geo) {
  double E,kE;
  E=kE=0.;
  EFunc(Coor,IdxLst,PrmLst,IMLst,6,DEval,Geo,E);
  for(unsigned int i=0;i<nunit;++i) kE+=normSQ(Vel[i])*Mass[i][0]*0.5;
  cout<<P.GParam[NowTime].d<<"\t"<<Coor[0]<<"\t"<<E<<"\t"<<kE<<endl;
}
*/

int main() {
  PropertyList<double> Coor,Vel,Grad,dMask;
  Vector<unsigned int> sz;
  allocate(sz,4);
  copy(sz,2);
  allocate(Coor,sz);
  allocate(Vel,sz);
  allocate(Grad,sz);
  allocate(dMask,sz);

  Coor[0][0]=0;       Coor[0][1]=0;
  Coor[1][0]=0;       Coor[1][1]=1.2;
  Coor[2][0]=1.3;     Coor[2][1]=1.5;
  Coor[3][0]=0.8;     Coor[3][1]=2.2;
  copy(Vel,0.);
  copy(dMask,1.);

  Vector<Interaction<double,DistanceBufferSimple,FreeSpace> > F;

  allocate(F,6);
  for(unsigned int i=0;i<3;++i) allocate(F[i],Harmonic,2,4);
  for(unsigned int i=3;i<6;++i) allocate(F[i],LJ612,2,4);
  F[0].prm[HarmonicEqLength].d=1.;
  F[0].prm[HarmonicEqStrength].d=100.;
  F[1].prm[HarmonicEqLength].d=1.;
  F[1].prm[HarmonicEqStrength].d=100.;
  F[2].prm[HarmonicEqLength].d=1.;
  F[2].prm[HarmonicEqStrength].d=100.;
  for(unsigned int i=0;i<3;++i) BuildParameterHarmonic<double>(F[i].prm);
  F[3].prm[LJ612EqRadius].d=1.;
  F[3].prm[LJ612EqEnergyDepth].d=1.;
  F[4].prm[LJ612EqRadius].d=1.;
  F[4].prm[LJ612EqEnergyDepth].d=1.;
  F[5].prm[LJ612EqRadius].d=1.;
  F[5].prm[LJ612EqEnergyDepth].d=1.;
  for(unsigned int i=3;i<6;++i) BuildParameterLJ612<double>(F[i].prm);
  PropertyList<unsigned int> Idx;
  allocate(sz,6);
  copy(sz,2);
  allocate(Idx,sz);
  Idx[0][0]=0;       Idx[0][1]=1;
  Idx[1][0]=1;       Idx[1][1]=2;
  Idx[2][0]=2;       Idx[2][1]=3;
  Idx[3][0]=0;       Idx[3][1]=2;
  Idx[4][0]=0;       Idx[4][1]=3;
  Idx[5][0]=1;       Idx[5][1]=3;

  copy(Grad,0.);
  CalcInteraction(F,Coor.structure,Idx.structure,Grad.structure);

  Vector<UniqueParameter> GP;
  Vector<Vector<UniqueParameter> > MP;

  allocatePropagatorEVParameter(GP);
  allocate(MP,4);
  for(unsigned int i=0;i<4;++i)
    allocatePropagatorMonomerPEVParameter<double>(MP[i]);
  GP[DeltaTime].d=0.001;
  GP[StartTime].d=100.;
  GP[TotalTime].d=0.01;
  GP[OutputInterval].d=0.002;
  for(unsigned int i=0;i<4;++i) MP[i][MassData].d=2.;
  BuildParameterPropagatorEV<double>(GP,MP);

  cout<<"=== Coor:"<<endl;
  cout<<Coor<<endl;
  cout<<"=== Vel:"<<endl;
  cout<<Vel<<endl;
  cout<<"=== Grad:"<<endl;
  cout<<Grad<<endl;
  EVMoveStep(F,Coor.structure,Vel.structure,Grad.structure,
             dMask.structure,Idx.structure,GP,MP.data,4);
  cout<<"=== Coor:"<<endl;
  cout<<Coor<<endl;
  cout<<"=== Vel:"<<endl;
  cout<<Vel<<endl;
  cout<<"=== Grad:"<<endl;
  cout<<Grad<<endl;
  /*
  Propagator<DistanceEvalDirect,FreeSpace> P;
  allocate(P);
  Set(P,ConstantE_VelocityVerlet);
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

  cout<<"Test -- EV synchronize"<<endl;
  EVSynchronize(iMass.structure,dMask.structure,Vel.structure,4,P.GParam());
  cout<<endl;

  synchronize(P,iMass.structure,dMask.structure,Vel.structure,4);
  cout<<"Test -- EV step"<<endl;
  cout<<"=== Coor:"<<endl;
  cout<<Coor<<endl;
  cout<<"=== Vel:"<<endl;
  cout<<Vel<<endl;
  cout<<"=== Grad:"<<endl;
  cout<<Grad<<endl;
  EVStep(IMLst(),Coor.structure,Vel.structure,Grad.structure,Mass.structure,
         dMask.structure,fIdxLst.structure,fParamLst(),P.GParam(),P.Unit(),
         4,6,DEval,FS);
  cout<<"=== Coor:"<<endl;
  cout<<Coor<<endl;
  cout<<"=== Vel:"<<endl;
  cout<<Vel<<endl;
  cout<<"=== Grad:"<<endl;
  cout<<Grad<<endl;
  cout<<endl;

  cout<<"Test -- simulation"<<endl;
  setparameter(P,TotalTimeCommon,10.);
  setparameter(P,OutputTimeIntervalCommon,0.001);
  synchronize(P,iMass.structure,dMask.structure,Vel.structure,4);
  Run(P,Coor.structure,Vel.structure,Grad.structure,Mass.structure,
      dMask.structure,IMLst(),fIdxLst.structure,fParamLst(),4,6,DEval,FS);
  cout<<endl;
  */

  return 0;
}

