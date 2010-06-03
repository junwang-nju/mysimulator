
#include "propagator-op.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

template <typename DistEvalMethod, typename GeomType>
void OutFunc(ostream& os, const Propagator<DistEvalMethod,GeomType>& P,
             InteractionMethod<DistEvalMethod,GeomType>* IMLst,
             const Vector<double>* Coor, const Vector<double>* Vel,
             const Vector<double>* Grad, const Vector<double>* Mass,
             const Vector<double>* dMask,
             const Vector<unsigned int>* IdxLst,
             const Vector<UniqueParameter> *PrmLst,
             const unsigned int nunit, const unsigned int nlst,
             DistEvalMethod& DEval, const GeomType& Geo) {
  double E,kE,Es;
  E=kE=Es=0.;
  unsigned int g=((nunit-1)*(nunit-2))/2;
  EFunc(Coor,IdxLst+g,PrmLst+g,IMLst+g,nunit-1,DEval,Geo,E);
  EFunc(Coor,IdxLst+nlst-1,PrmLst+nlst-1,IMLst+nlst-1,1,DEval,Geo,Es);
  for(unsigned int i=0;i<nunit;++i) kE+=normSQ(Vel[i])*Mass[i][0]*0.5;
  MassCenter(Coor,IdxLst[nlst-1](),nunit-1,(*(IMLst[nlst-1].tmpvec))[0]);
  cout<<P.GParam[NowTime].d<<"\t"<<(*(IMLst[nlst-1].tmpvec))[0];
  cout<<"\t"<<E<<"\t"<<kE<<"\t"<<Es;
  cout<<"\t"<<norm((*(IMLst[nlst-1].tmpvec))[0]);
  assign((*(IMLst[nlst-1].tmpvec))[0],Coor[0]);
  shift((*(IMLst[nlst-1].tmpvec))[0],-dOne,Coor[nunit-2]);
  cout<<"\t"<<norm((*(IMLst[nlst-1].tmpvec))[0]);
  unsigned int q;
  q=0;
  for(unsigned int i=0;i<nunit-1;++i) {
    assign((*(IMLst[nlst-1].tmpvec))[0],Coor[i]);
    shift((*(IMLst[nlst-1].tmpvec))[0],-dOne,Coor[nunit-1]);
    if(norm((*(IMLst[nlst-1].tmpvec))[0])-0.1<1.2)  ++q;
  }
  cout<<"\t"<<q;
  cout<<endl;
}

int main(int argc, char** argv) {
  //if(argc<3) myError("pOs-nbasic <center-distance> <e-strength>");
  //const double dcent=atof(argv[1]);
  //const double esize=atof(argv[2]);
  const double esize=1.0;

  const unsigned int NMer=20;
  const unsigned int NInter=NMer-1+((NMer-2)*(NMer-1))/2+NMer+1;

  PropertyList<double> Coor,Vel,Grad,Mass,iMass,dMask,RandV;
  Vector<unsigned int> sz;
  allocate(sz,NMer+1);
  assign(sz,3);
  allocate(Coor,sz);
  allocate(Vel,sz);
  allocate(Grad,sz);
  allocate(Mass,sz);
  allocate(iMass,sz);
  allocate(dMask,sz);
  allocate(RandV,sz);

  assign(Coor,0.);
  for(unsigned int i=0;i<NMer;++i) {
    Coor[i][0]=i-(NMer-1.)*0.5;
    Coor[i][1]=1.5;
  }
  assign(Vel,0.);
  assign(Mass,1.);
  assign(iMass,1.);
  assign(dMask,1.);
  assign(dMask[NMer],0.);

  Vector<InteractionMethod<DistanceEvalDirect,FreeSpace> > IMLst;
  allocate(IMLst,NInter);
  for(unsigned int i=0;i<NInter;++i)  allocate(IMLst[i]);
  unsigned int n;
  n=0;
  for(unsigned int i=0;i<NMer-1;++i,++n)
    Set(IMLst[n],PairwiseHarmonic);
  for(unsigned int i=0;i<((NMer-2)*(NMer-1))/2;++i,++n)
    Set(IMLst[n],PairwiseCoreLJ612);
  for(unsigned int i=0;i<NMer;++i,++n)
    Set(IMLst[n],PairwiseCoreExpandCoreLJ612);
  Set(IMLst[n],CentroidHarmonic,3);

  Vector<Vector<UniqueParameter> > ParamLst;
  allocate(ParamLst,NInter);
  n=0;
  for(unsigned int i=0;i<NMer-1;++i,++n)
    allocate(ParamLst[n],HarmonicNumberParameter);
  for(unsigned int i=0;i<((NMer-1)*(NMer-2))/2;++i,++n)
    allocate(ParamLst[n],CoreLJ612NumberParameter);
  for(unsigned int i=0;i<NMer;++i,++n)
    allocate(ParamLst[n],CoreExpCoreLJ612NumberParameter);
  allocate(ParamLst[n],CentroidHarmonicNumberParameter);
  n=0;
  for(unsigned int i=0;i<NMer-1;++i,++n) {
    ParamLst[n][HarmonicEqLength]=1.;
    ParamLst[n][HarmonicEqStrength]=100.;
    GenerateParameterHarmonic(ParamLst[n]);
  }
  for(unsigned int i=0;i<((NMer-1)*(NMer-2))/2;++i,++n) {
    ParamLst[n][CoreLJ612Radius]=1;
    ParamLst[n][CoreLJ612EnergyDepth]=1.;
    GenerateParameterCoreLJ612(ParamLst[n]);
  }
  for(unsigned int i=0;i<NMer;++i,++n) {
    ParamLst[n][CoreExpCoreRadius]=0.1;
    ParamLst[n][CoreExpCoreLJ612Radius]=1.;
    ParamLst[n][CoreExpCoreLJ612EnergyDepth]=1.;
    GenerateParameterCoreExpandCoreLJ612(ParamLst[n]);
  }
  ParamLst[n][CentroidHarmonicEqLength]=0.5;
  ParamLst[n][CentroidHarmonicEqStrength]=10.;
  GenerateParameterCentroidHarmonic(ParamLst[n]);

  PropertyList<unsigned int> IdxLst;
  allocate(sz,NInter);
  assign(sz,2);
  sz[NInter-1]=NMer+1+4;
  allocate(IdxLst,sz);
  n=0;
  for(unsigned int i=0;i<NMer-1;++i,++n) {
    IdxLst[n][0]=i;
    IdxLst[n][1]=i+1;
  }
  for(unsigned int i=0;i<NMer;++i)
  for(unsigned int j=i+2;j<NMer;++j,++n) {
    IdxLst[n][0]=i;
    IdxLst[n][1]=j;
  }
  for(unsigned int i=0;i<NMer;++i,++n) {
    IdxLst[n][0]=i;
    IdxLst[n][1]=NMer;
  }
  for(unsigned int i=0;i<=NMer;++i)
    IdxLst[n][i]=i;
  IdxLst[n][NMer+1]=0;    IdxLst[n][NMer+2]=NMer;
  IdxLst[n][NMer+3]=NMer; IdxLst[n][NMer+4]=1;

  DistanceEvalDirect DEval;
  FreeSpace FS;
  allocate(DEval,3,NMer);
  allocate(FS,3);

  assign(Grad,0.);
  GFunc(Coor.structure,IdxLst.structure,ParamLst(),IMLst(),NInter,
        DEval,FS,Grad.structure);

  GaussianRNG gng;
  allocate(gng);
  //init(gng,1237913);
  initWithTime(gng);

  Propagator<DistanceEvalDirect,FreeSpace>  P;
  allocate(P);
  Set(P,Langevin_VelocityVerlet);
  allocate(sz,NMer+1);
  assign(sz,ParticleType);
  buildUnit(P,sz);

  setparameter(P,TimeStepCommon,0.001);
  setparameter(P,StartTimeCommon,0.);
  setparameter(P,TotalTimeCommon,1000.0);
  setparameter(P,OutputTimeIntervalCommon,1.);
  setparameter(P,TemperatureLV,1.0);
  setparameter(P,ViscosityLV,0.5);
  setparameter(P,GaussianRNGPointerLV,gng);
  for(unsigned int i=0;i<NMer+1;++i) {
    setparameter(P.Unit[i],HydrodynamicRadiusPLV,1.0);
    setparameter(P.Unit[i],RandomVelocityPointerPLV,RandV[i][0]);
  }

  synchronize(P,iMass.structure,dMask.structure,Vel.structure,NMer+1);

  P.FOutput=OutFunc<DistanceEvalDirect,FreeSpace>;
  P.HOutput=NULL;

  Run(P,Coor.structure,Vel.structure,Grad.structure,Mass.structure,
      dMask.structure,IMLst(),IdxLst.structure,ParamLst(),NMer+1,NInter,
      DEval,FS);

  n=(NMer*(NMer-1))/2;
  for(unsigned int i=0;i<NMer;++i,++n)
    Set(IMLst[n],PairwiseCoreExpandLJ612);
  n=(NMer*(NMer-1))/2;
  for(unsigned int i=0;i<NMer;++i,++n)
    allocate(ParamLst[n],CoreExpLJ612NumberParameter);
  n=(NMer*(NMer-1))/2;
  for(unsigned int i=0;i<NMer;++i,++n) {
    ParamLst[n][CoreExpCoreRadius]=0.1;
    ParamLst[n][CoreExpLJ612EqRadius]=1.;
    ParamLst[n][CoreExpLJ612EqEnergyDepth]=esize;
    GenerateParameterCoreExpandLJ612(ParamLst[n]);
  }
  assign(Grad,0.);
  GFunc(Coor.structure,IdxLst.structure,ParamLst(),IMLst(),NInter,
        DEval,FS,Grad.structure);

  setparameter(P,StartTimeCommon,P.GParam[NowTime].d);
  setparameter(P,TotalTimeCommon,10000.0);
  setparameter(P,OutputTimeIntervalCommon,0.1);
  synchronize(P,iMass.structure,dMask.structure,Vel.structure,NMer+1);

  Run(P,Coor.structure,Vel.structure,Grad.structure,Mass.structure,
      dMask.structure,IMLst(),IdxLst.structure,ParamLst(),NMer+1,NInter,
      DEval,FS);

  return 0;
}

