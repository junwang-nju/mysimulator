
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/interaction/calc.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-lj612.h"
#include "operation/parameter/build-param-propagator-langevin-vverlet.h"
#include "operation/parameter/build-param-propagator-monomer-particle-langevin-vverlet.h"
#include "operation/propagate/run.h"
#include "operation/random/random-generator-boxmuller-op.h"
#include <iostream>
using namespace std;

template <template<typename,template<typename>class,typename> class IType,
          typename PmType,typename T,template<typename> class Dbuffer,
          typename GeomType>
void OutFunc(IType<T,Dbuffer,GeomType>& F,
             Vector<T>* X,Vector<T>* V,Vector<T>* G,const Vector<T>* dMsk,
             const PmType& pmx,Vector<UniqueParameter>& GP,
             Vector<UniqueParameter>* MP,const unsigned int& nu,ostream& os) {
  T E,kE;
  E=kE=0.;
  CalcInteraction(F,X,pmx,E);
  for(unsigned int i=0;i<nu;++i)
    kE+=0.5*MP[i][MassData].value<T>()*norm(V[i]);
  os<<GP[NowTime].value<T>()<<"\t"<<E<<"\t"<<kE<<endl;
}

int main() {
  PropertyList<double> Coor,Vel,Grad,dMask,RandV;
  Vector<unsigned int> sz;
  allocate(sz,4);
  copy(sz,2);
  allocate(Coor,sz);
  allocate(Vel,sz);
  allocate(Grad,sz);
  allocate(dMask,sz);
  allocate(RandV,sz);

  Coor[0][0]=0;       Coor[0][1]=0;
  Coor[1][0]=0;       Coor[1][1]=1.2;
  Coor[2][0]=1.3;     Coor[2][1]=1.5;
  Coor[3][0]=0.8;     Coor[3][1]=2.2;
  copy(Vel,0.);
  copy(dMask,1.);

  ListInteraction<double,DistanceBufferSimple,FreeSpace> F;

  allocate(sz,6);
  for(unsigned int i=0;i<3;++i) sz[i]=Harmonic;
  for(unsigned int i=3;i<6;++i) sz[i]=LJ612;
  allocate(F,sz,2,4);
  Vector<InteractionParameterUnit> RP(6);
  for(unsigned int i=0;i<3;++i) allocate(RP[i],Harmonic);
  for(unsigned int i=3;i<6;++i) allocate(RP[i],LJ612);
  RP[0].prm[HarmonicEqLength].d=1.;
  RP[0].prm[HarmonicEqStrength].d=100.;
  RP[1].prm[HarmonicEqLength].d=1.;
  RP[1].prm[HarmonicEqStrength].d=100.;
  RP[2].prm[HarmonicEqLength].d=1.;
  RP[2].prm[HarmonicEqStrength].d=100.;
  for(unsigned int i=0;i<3;++i) BuildParameterHarmonic<double>(RP[i].prm);
  RP[3].prm[LJ612EqRadius].d=1.;
  RP[3].prm[LJ612EqEnergyDepth].d=1.;
  RP[4].prm[LJ612EqRadius].d=1.;
  RP[4].prm[LJ612EqEnergyDepth].d=1.;
  RP[5].prm[LJ612EqRadius].d=1.;
  RP[5].prm[LJ612EqEnergyDepth].d=1.;
  for(unsigned int i=3;i<6;++i) BuildParameterLJ612<double>(RP[i].prm);
  RP[0].idx[0]=0;       RP[0].idx[1]=1;
  RP[1].idx[0]=1;       RP[1].idx[1]=2;
  RP[2].idx[0]=2;       RP[2].idx[1]=3;
  RP[3].idx[0]=0;       RP[3].idx[1]=2;
  RP[4].idx[0]=0;       RP[4].idx[1]=3;
  RP[5].idx[0]=1;       RP[5].idx[1]=3;

  copy(Grad,0.);
  CalcInteraction(F,Coor.structure,RP,Grad.structure);

  Vector<UniqueParameter> GP;
  Vector<Vector<UniqueParameter> > MP;

  allocatePropagatorLVParameter<
    ListInteraction,Vector<InteractionParameterUnit>,double,
    DistanceBufferSimple,FreeSpace>(GP);
  allocate(MP,4);
  for(unsigned int i=0;i<4;++i)
    allocatePropagatorMonomerPLVParameter<double>(MP[i]);
  GaussianRNG grng;
  allocate(grng);
  init(grng,1237913);
  GP[LV_GaussianRNG].ptr=reinterpret_cast<void*>(&grng);
  GP[DeltaTime].d=0.001;
  GP[StartTime].d=100.;
  GP[TotalTime].d=0.01;
  GP[OutputInterval].d=0.002;
  GP[LV_Temperature].d=0.5;
  GP[LV_Viscosity].d=0.5;
  for(unsigned int i=0;i<4;++i) {
    MP[i][MassData].d=2.;
    MP[i][PLV_HydrodynamicRadius].d=1.;
    MP[i][PLV_RandomVelocity].ptr=reinterpret_cast<void*>(RandV.structure+i);
  }
  BuildParameterPropagatorLV<double>(GP,MP);

  cout<<"Test -- LV step"<<endl;
  cout<<"=== Coor:"<<endl;
  cout<<Coor<<endl;
  cout<<"=== Vel:"<<endl;
  cout<<Vel<<endl;
  cout<<"=== Grad:"<<endl;
  cout<<Grad<<endl;
  LVMoveStep(F,Coor.structure,Vel.structure,Grad.structure,
             dMask.structure,RP,GP,MP.data,4);
  cout<<"=== Coor:"<<endl;
  cout<<Coor<<endl;
  cout<<"=== Vel:"<<endl;
  cout<<Vel<<endl;
  cout<<"=== Grad:"<<endl;
  cout<<Grad<<endl;
  cout<<endl;

  cout<<"Test -- simulation"<<endl;
  GP[TotalTime].d=100.;
  GP[OutputInterval].d=0.002;
  BuildParameterPropagatorLV<double>(GP,MP);
  SetOutput(GP,
            OutFunc<ListInteraction,Vector<InteractionParameterUnit>,double,
                    DistanceBufferSimple,FreeSpace>);
  Run(F,Coor.structure,Vel.structure,Grad.structure,dMask.structure,
      RP,GP,MP.data,4,cout);
  cout<<endl;

  return 0;
}

