
#include "propagator.h"
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include "var-property-list.h"
#include "interaction-method-op.h"
#include "var-parameter-list.h"
#include "parameter-generate-harmonic.h"
#include "parameter-generate-lj612.h"
#include <iostream>
using namespace std;

template <template <template <typename> class> class DistEvalMethod,
          template <template <typename> class> class GeomType,
          template <typename> class VecTypeD,
          template <typename> class VecTypeG>
void OutFunc(
    ostream& os, const Propagator<DistEvalMethod,GeomType>& P,
    const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& vIM,
    const VectorBase<refVector<double> >& Coor,
    const VectorBase<refVector<double> >& Vel,
    const VectorBase<refVector<double> >& Grad,
    const VectorBase<refVector<unsigned int> >& IdxLst,
    const VectorBase<refVector<double> >& ParamLst,
    DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo) {
  cout<<P.GlobalParam[NowTime].d<<"\t"<<Coor[0]<<endl;
}

template <template <template <typename> class> class DistEvalMethod,
          template <template <typename> class> class GeomType,
          template <typename> class VecTypeD,
          template <typename> class VecTypeG>
void OutFunc(
    ostream& os, const Propagator<DistEvalMethod,GeomType>& P,
    const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& vIM,
    const VectorBase<refVector<double> >& Coor,
    const VectorBase<refVector<double> >& Vel,
    const VectorBase<refVector<double> >& Grad,
    const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
    const VectorBase<refVector<refVector<double> > >& ParamLst,
    DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo) {
  cout<<P.GlobalParam[NowTime].d<<"\t"<<Coor[0]<<endl;
}

int main() {

  cout<<"Test -- create a propagator"<<endl;
  Propagator<DistanceEvalDirect,FreeSpace>  P;
  cout<<endl;

  cout<<"Test -- allocate a propagator"<<endl;
  varVector<unsigned int> uMode(4);
  uMode=ParticleType;
  P.allocate(ConstE_VelocityVerlet,uMode);
  cout<<endl;

  cout<<"Test -- set a series of property"<<endl;
  P.SetTimeStep(0.002);
  P.SetStartTime(100);
  P.SetTotalTime(0.006);
  P.SetOutputInterval(0.002);
  cout<<endl;

  cout<<"Test -- synchronize other internal data"<<endl;
  varPropertyList<double>::Type Mass,IvMass;
  varPropertyList<double>::Type dMask;
  varVector<unsigned int> Sz(4);
  Sz=2;
  Mass.allocate(Sz);
  IvMass.allocate(Sz);
  dMask.allocate(Sz);
  Mass=2.;
  IvMass=0.5;
  Mass[2]=0.1;
  IvMass[2]=10;
  dMask=1;
  P.synchronize(IvMass,dMask);
  cout<<endl;

  cout<<"Test -- Step, WriteOut and Run function for Hierarchy form of data"<<endl;
  varPropertyList<double>::Type CoorSeq,VelSeq,GradSeq,oCoorSeq;
  CoorSeq.allocate(Sz);
  VelSeq.allocate(Sz);
  GradSeq.allocate(Sz);
  oCoorSeq.allocate(Sz);
  CoorSeq[0][0]=0;    CoorSeq[0][1]=0;
  CoorSeq[1][0]=0;    CoorSeq[1][1]=1.2;
  CoorSeq[2][0]=1.3;  CoorSeq[2][1]=1.5;
  CoorSeq[3][0]=0.8;  CoorSeq[3][1]=2.2;
  VelSeq=0.;

  varVector<InteractionMethod<DistanceEvalDirect,FreeSpace> > IM;
  IM.allocate(2);
  SetInteractionMethod(IM[0],ParticleParticle_Harmonic);
  SetInteractionMethod(IM[1],ParticleParticle_LJ612);

  varPropertyList<unsigned int>::Type IdxLst;
  Sz.allocate(6);
  Sz=2;
  IdxLst.allocate(Sz);
  IdxLst[0][0]=0;   IdxLst[0][1]=1;
  IdxLst[1][0]=0;   IdxLst[1][1]=2;
  IdxLst[2][0]=0;   IdxLst[2][1]=3;
  IdxLst[3][0]=1;   IdxLst[3][1]=2;
  IdxLst[4][0]=1;   IdxLst[4][1]=3;
  IdxLst[5][0]=2;   IdxLst[5][1]=3;
  varPropertyList<refVector<unsigned int> > vIdx;
  Sz.allocate(2);
  Sz=3;
  vIdx.allocate(Sz);
  for(unsigned int i=0,n=0;i<2;++i)
  for(unsigned int j=0;j<3;++j,++n)
    vIdx[i][j].refer(IdxLst[n]);

  varVector<unsigned int> KindSeq(4);
  KindSeq[0]=0;
  KindSeq[1]=1;
  KindSeq[2]=0;
  KindSeq[3]=2;


  varParameterList vPL;
  varVector<unsigned int> kS(18),vS(18);
  for(unsigned int i=0;i<18;++i)  kS[i]=3;
  for(unsigned int i=0;i<9;++i)   vS[i]=Harmonic_NumberParameter;
  for(unsigned int i=9;i<18;++i)  vS[i]=LJ612_NumberParameter;
  vPL.allocate(kS,vS);
  for(unsigned int i=0,n=0;i<3;++i)
  for(unsigned int j=0;j<3;++j,++n) {
    vPL.keylist()[n].index()[0]=ParticleParticle_Harmonic;
    vPL.keylist()[n].index()[1]=i;
    vPL.keylist()[n].index()[2]=j;
    vPL.keylist()[n].BuildHash();
  }
  vPL.valuelist()[0][Harmonic_EqLength]=1.;
  vPL.valuelist()[0][Harmonic_EqStrength]=100.;
  vPL.valuelist()[1][Harmonic_EqLength]=2.;
  vPL.valuelist()[1][Harmonic_EqStrength]=100.;
  vPL.valuelist()[2][Harmonic_EqLength]=0.5;
  vPL.valuelist()[2][Harmonic_EqStrength]=100.;
  vPL.valuelist()[3]=vPL.valuelist()[1];
  vPL.valuelist()[4][Harmonic_EqLength]=1.;
  vPL.valuelist()[4][Harmonic_EqStrength]=200.;
  vPL.valuelist()[5][Harmonic_EqLength]=1.;
  vPL.valuelist()[5][Harmonic_EqStrength]=30.;
  vPL.valuelist()[6]=vPL.valuelist()[2];
  vPL.valuelist()[7]=vPL.valuelist()[5];
  vPL.valuelist()[8][Harmonic_EqLength]=1.5;
  vPL.valuelist()[8][Harmonic_EqStrength]=2000.;
  for(unsigned int i=0;i<9;++i)
    ParameterGenerateHarmonic(vPL.valuelist()[i]);
  for(unsigned int i=0,n=9;i<3;++i)
  for(unsigned int j=0;j<3;++j,++n) {
    vPL.keylist()[n].index()[0]=ParticleParticle_LJ612;
    vPL.keylist()[n].index()[1]=i;
    vPL.keylist()[n].index()[2]=j;
    vPL.keylist()[n].BuildHash();
  }
  vPL.valuelist()[9][LJ612_EqRadius]=1.;
  vPL.valuelist()[9][LJ612_EqStrength]=1.;
  vPL.valuelist()[10][LJ612_EqRadius]=0.8;
  vPL.valuelist()[10][LJ612_EqStrength]=2.;
  vPL.valuelist()[11][LJ612_EqRadius]=0.5;
  vPL.valuelist()[11][LJ612_EqStrength]=1.;
  vPL.valuelist()[12]=vPL.valuelist()[10];
  vPL.valuelist()[13][LJ612_EqRadius]=1.2;
  vPL.valuelist()[13][LJ612_EqStrength]=2.;
  vPL.valuelist()[14][LJ612_EqRadius]=1.1;
  vPL.valuelist()[14][LJ612_EqStrength]=3.;
  vPL.valuelist()[15]=vPL.valuelist()[11];
  vPL.valuelist()[16]=vPL.valuelist()[14];
  vPL.valuelist()[17][LJ612_EqRadius]=1.5;
  vPL.valuelist()[17][LJ612_EqStrength]=2.;
  for(unsigned int i=9;i<18;++i)
    ParameterGenerateLJ612(vPL.valuelist()[i]);
  vPL.updateHashTree();

  varVector<refVector<double> > ParamLst(6);
  varVector<unsigned int> prmKey(3);
  for(unsigned int i=0;i<3;++i) {
    prmKey[0]=ParticleParticle_Harmonic;
    for(unsigned int k=0;k<2;++k)
      prmKey[k+1]=KindSeq[IdxLst[i][k]];
    ParamLst[i].refer(*vPL.get(prmKey));
  }
  for(unsigned int i=3;i<6;++i) {
    prmKey[0]=ParticleParticle_LJ612;
    for(unsigned int k=0;k<2;++k)
      prmKey[k+1]=KindSeq[IdxLst[i][k]];
    ParamLst[i].refer(*vPL.get(prmKey));
  }

  varPropertyList<refVector<double> >::Type vPrm;
  Sz.allocate(2);
  Sz=3;
  vPrm.allocate(Sz);
  for(unsigned int i=0,n=0;i<2;++i)
  for(unsigned int j=0;j<3;++j,++n)
    vPrm[i][j].refer(ParamLst[n]);

  varDistanceEvalDirect vDED(2);
  varFreeSpace vFS;

  P.FWriteOutVV=OutFunc<DistanceEvalDirect,FreeSpace,varVector,varVector>;
  P.FWriteOutVR=OutFunc<DistanceEvalDirect,FreeSpace,varVector,refVector>;
  P.FWriteOutRV=OutFunc<DistanceEvalDirect,FreeSpace,refVector,varVector>;
  P.FWriteOutRR=OutFunc<DistanceEvalDirect,FreeSpace,refVector,refVector>;
  P.HWriteOutVV=OutFunc<DistanceEvalDirect,FreeSpace,varVector,varVector>;
  P.HWriteOutVR=OutFunc<DistanceEvalDirect,FreeSpace,varVector,refVector>;
  P.HWriteOutRV=OutFunc<DistanceEvalDirect,FreeSpace,refVector,varVector>;
  P.HWriteOutRR=OutFunc<DistanceEvalDirect,FreeSpace,refVector,refVector>;

  oCoorSeq=CoorSeq;
  GFunc(CoorSeq.Structure(),IM,vIdx.Structure(),vPrm.Structure(),vDED,vFS,
        GradSeq.Structure());
  cout<<"=== Initial Coordinate, Velocity, and Gradient"<<endl;
  cout<<CoorSeq<<endl;
  cout<<VelSeq<<endl;
  cout<<GradSeq<<endl;
  P.Step(IM,CoorSeq.Structure(),VelSeq.Structure(),GradSeq.Structure(),
         vIdx.Structure(),vPrm.Structure(),vDED,vFS);
  cout<<"=== Coordinate, Velocity, and Gradient after a step"<<endl;
  cout<<CoorSeq<<endl;
  cout<<VelSeq<<endl;
  cout<<GradSeq<<endl;

  cout<<"=== Invoke WriteOut"<<endl;
  P.WriteOut(cout,IM,CoorSeq.Structure(),VelSeq.Structure(),
             GradSeq.Structure(),vIdx.Structure(),vPrm.Structure(),vDED,vFS);

  cout<<"=== Run"<<endl;
  CoorSeq=oCoorSeq;
  VelSeq=0.;
  GradSeq=0.;
  GFunc(CoorSeq.Structure(),IM,vIdx.Structure(),vPrm.Structure(),vDED,vFS,
        GradSeq.Structure());
  P.Run(CoorSeq,VelSeq,GradSeq,Mass,IM,vIdx,vPrm,vDED,vFS,cout);
  cout<<endl;

  cout<<"Test -- Step, WriteOut and Run function for Flat form of data"<<endl;
  IM.allocate(6);
  for(unsigned int i=0;i<3;++i)
    SetInteractionMethod(IM[i],ParticleParticle_Harmonic);
  for(unsigned int i=3;i<6;++i)
    SetInteractionMethod(IM[i],ParticleParticle_LJ612);

  CoorSeq=oCoorSeq;
  VelSeq=0.;
  GradSeq=0.;
  GFunc(CoorSeq.Structure(),IM,IdxLst.Structure(),ParamLst,vDED,vFS,
        GradSeq.Structure());
  cout<<"=== Initial Coordinate, Velocity, and Gradient"<<endl;
  cout<<CoorSeq<<endl;
  cout<<VelSeq<<endl;
  cout<<GradSeq<<endl;
  P.Step(IM,CoorSeq.Structure(),VelSeq.Structure(),GradSeq.Structure(),
         IdxLst.Structure(),ParamLst,vDED,vFS);
  cout<<"=== Coordinate, Velocity, and Gradient after a step"<<endl;
  cout<<CoorSeq<<endl;
  cout<<VelSeq<<endl;
  cout<<GradSeq<<endl;

  cout<<"=== Invoke WriteOut"<<endl;
  P.WriteOut(cout,IM,CoorSeq.Structure(),VelSeq.Structure(),
             GradSeq.Structure(),IdxLst.Structure(),ParamLst,vDED,vFS);

  cout<<"=== Run"<<endl;
  CoorSeq=oCoorSeq;
  VelSeq=0.;
  GradSeq=0.;
  GFunc(CoorSeq.Structure(),IM,IdxLst.Structure(),ParamLst,vDED,vFS,
        GradSeq.Structure());
  P.Run(CoorSeq,VelSeq,GradSeq,Mass,IM,IdxLst,ParamLst,vDED,vFS,cout);
  cout<<endl;

  cout<<"Test -- assign to another propagator"<<endl;
  Propagator<DistanceEvalDirect,FreeSpace>  P1;
  P1=P;
  cout<<endl;

  return 1;
}

