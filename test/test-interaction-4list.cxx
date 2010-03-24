
#include "interaction-4list.h"
#include "var-property-list.h"
#include "interaction-method-op.h"
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include "var-parameter-list.h"
#include <iostream>
using namespace std;

int main() {
  varPropertyList<double>::Type CoorSeq,GradSeq;
  varVector<unsigned int> Sz(4);
  Sz=2;
  CoorSeq.allocate(Sz);
  GradSeq.allocate(Sz);
  InteractionMethod<DistanceEvalDirect,FreeSpace> runIM;
  SetInteractionMethod(runIM,ParticleParticle_Harmonic);
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
  varVector<unsigned int> KindSeq(4);
  KindSeq[0]=0;
  KindSeq[1]=1;
  KindSeq[2]=0;
  KindSeq[3]=2;
  varParameterList vPL;
  vPL.allocate(3,Harmonic_NumberParameter+1,9);
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
  vPL.updateHashTree();
  varDistanceEvalDirect vDED(2);
  varFreeSpace vFS;

  CoorSeq[0][0]=0;    CoorSeq[0][1]=0;
  CoorSeq[1][0]=0;    CoorSeq[1][1]=1.2;
  CoorSeq[2][0]=1.3;  CoorSeq[2][1]=1.5;
  CoorSeq[3][0]=0.8;  CoorSeq[3][1]=2.2;
  cout<<"Test -- Energy for a list of units with loose binding"<<endl;
  double E=0;
  EFunc(CoorSeq.Structure(),runIM,IdxLst.Structure(),KindSeq,vPL,vDED,vFS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- gradient for a list of units with loose binding"<<endl;
  GradSeq=0.;
  GFunc(CoorSeq.Structure(),runIM,IdxLst.Structure(),KindSeq,vPL,vDED,vFS,
        GradSeq.Structure());
  cout<<GradSeq<<endl;
  cout<<endl;

  cout<<"Test -- Energy and gradient for a list of units with loose binding"<<endl;
  E=0.;
  GradSeq=0.;
  BFunc(CoorSeq.Structure(),runIM,IdxLst.Structure(),KindSeq,vPL,vDED,vFS,
        E,GradSeq.Structure());
  cout<<E<<endl;
  cout<<GradSeq<<endl;
  cout<<endl;

  varPropertyList<refVector<double> >::Type CoorLst,GradLst;
  Sz.allocate(6);
  Sz=2;
  CoorLst.allocate(Sz);
  GradLst.allocate(Sz);
  for(unsigned int i=0;i<6;++i)
  for(unsigned int j=0;j<2;++j) {
    CoorLst[i][j].refer(CoorSeq[IdxLst[i][j]]);
    GradLst[i][j].refer(GradSeq[IdxLst[i][j]]);
  }
  varVector<refVector<double> > ParamLst(6);
  varVector<unsigned int> prmKey(3);
  for(unsigned int i=0;i<6;++i) {
    prmKey[0]=ParticleParticle_Harmonic;
    for(unsigned int k=0;k<2;++k)
      prmKey[k+1]=KindSeq[IdxLst[i][k]];
    ParamLst[i].refer(*vPL.get(prmKey));
  }
  cout<<"Test -- Energy for a list of units with tight binding"<<endl;
  E=0.;
  EFunc(CoorLst.Structure(),runIM,IdxLst.Structure(),ParamLst,vDED,vFS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- gradient for a list of units with tight binding"<<endl;
  GradSeq=0.;
  GFunc(CoorLst.Structure(),runIM,IdxLst.Structure(),ParamLst,vDED,vFS,
        GradLst.Structure());
  cout<<GradSeq<<endl;
  cout<<endl;

  cout<<"Test -- Energy and gradient for a list of units with tight binding"<<endl;
  E=0.;
  GradSeq=0.;
  BFunc(CoorLst.Structure(),runIM,IdxLst.Structure(),ParamLst,vDED,vFS,
        E,GradLst.Structure());
  cout<<E<<endl;
  cout<<GradSeq<<endl;
  cout<<endl;

  return 1;
}

