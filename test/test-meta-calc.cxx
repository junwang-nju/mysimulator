
#include "operation/interaction/meta-calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-gao-enhanced-sampling.h"

using namespace std;

int main() {
  SimpleInteraction<double,DistanceBufferSimple,FreeSpace> F;
  InteractionMetaParameter<
    InteractionParameterUnit,
    SimpleInteraction<double,DistanceBufferSimple,FreeSpace>,double>  MP;
  allocate(F,Harmonic,3,2);
  allocate(MP,GaoEnhancedSampling);
  allocate(MP.inprm,Harmonic);
  MP.inprm.prm[HarmonicEqLength].d=1.;
  MP.inprm.prm[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(MP.inprm.prm);
  Vector<double> ds,ts,lnds,bt,lnbd;
  allocate(ds,5);
  allocate(ts,5);
  copy(ds,1.);
  ts[0]=0.5;
  ts[1]=0.8;
  ts[2]=1.;
  ts[3]=2;
  ts[4]=5;
  allocate(lnds,5);
  allocate(bt,5);
  allocate(lnbd,5);
  MP.prm[DensitySet].ptr=reinterpret_cast<void*>(&ds);
  MP.prm[TemperatureSet].ptr=reinterpret_cast<void*>(&ts);
  MP.prm[LnDensitySet].ptr=reinterpret_cast<void*>(&lnds);
  MP.prm[BetaSet].ptr=reinterpret_cast<void*>(&bt);
  MP.prm[LnBetaDensitySet].ptr=reinterpret_cast<void*>(&lnbd);
  MP.prm[RunTemperature].d=1.2;
  MP.prm[GaoNumberAllUnits].u=2;
  BuildParameterGaoEnhancedSampling<double>(MP.prm);
  MP.inprm.idx[0]=0;
  MP.inprm.idx[1]=1;

  Vector<unsigned int> sz;
  PropertyList<double> x,g;
  allocate(sz,2);
  copy(sz,3);
  allocate(x,sz);
  allocate(g,sz);
  copy(x,0.);
  x[1][0]=1.3;

  double E;
  E=0.;
  CalcInteraction(F,x.structure,MP,E);
  cout<<E<<endl;
  cout<<endl;

  copy(g,0.);
  CalcInteraction(F,x.structure,MP,g.structure);
  cout<<g<<endl;
  cout<<endl;

  E=0.;
  copy(g,0.);
  CalcInteraction(F,x.structure,MP,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  double EE;
  for(int i=-100;i<=100;++i) {
    x[1][0]=1+i*0.02;
    E=0.;
    CalcInteraction(F,x.structure,MP,E);
    EE=0.;
    CalcInteraction(F,x.structure,MP.inprm,EE);
    cout<<1+i*0.02<<"\t"<<EE<<"\t"<<E<<endl;
  }

  return 0;
}

