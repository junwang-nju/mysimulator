
#include "interaction-4listset.h"
#include "var-property-list.h"
#include "interaction-method-op.h"
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include "var-parameter-list.h"
#include <iostream>
using namespace std;

int main() {
  varPropertyList<double> CoorSeq, GradSeq;
  varVector<unsigned int> Sz;
  Sz.allocate(4);
  Sz=2;
  CoorSeq.allocate(Sz);
  GradSeq.allocate(Sz);
  varVector<InteractionMethod<DistanceEvalDirectBase,FreeSpaceBase> > vIM;
  vIM.allocate(2);
  SetInteractionMethod(vIM[0],ParticleParticle_Harmonic);
  SetInteractionMethod(vIM[1],ParticleParticle_LJ612);
  varPropertyList<unsigned int> IdxLst;
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
    vPL.valuelist()[i][Harmonic_DualEqStrength]=
        2*vPL.valuelist()[i][Harmonic_EqStrength];
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
  for(unsigned int i=9;i<18;++i) {
    vPL.valuelist()[i][LJ612_EqRadiusSQ]=
        vPL.valuelist()[i][LJ612_EqRadius]*vPL.valuelist()[i][LJ612_EqRadius];
    vPL.valuelist()[i][LJ612_TwlfEqStrength]=
        12*vPL.valuelist()[i][LJ612_EqStrength];
  }
  vPL.updateHashTree();
  varDistanceEvalDirect vDED(2);
  varFreeSpace vFS;

  CoorSeq[0][0]=0;    CoorSeq[0][1]=0;
  CoorSeq[1][0]=0;    CoorSeq[1][1]=1.2;
  CoorSeq[2][0]=1.3;  CoorSeq[2][1]=1.5;
  CoorSeq[3][0]=0.8;  CoorSeq[3][1]=2.2;
  cout<<"Test -- Energy for a list of units and a set of interaction with loose binding"<<endl;
  double E=0;
  EFunc(CoorSeq.Structure(),vIM,vIdx.Structure(),KindSeq,vPL,vDED,vFS,E);
  cout<<E<<endl;
  cout<<endl;

  return 1;
}

