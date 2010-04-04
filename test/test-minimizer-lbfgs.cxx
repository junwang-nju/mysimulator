
#include "minimizer-lbfgs-4propertylist.h"
#include "minimizer-line-tracking-4propertylist.h"
#include <iostream>

#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include "var-property-list.h"
#include "interaction-method-op.h"
#include "var-parameter-list.h"
#include "interaction-4listset.h"
using namespace std;

int main() {
  cout<<"Test -- initiate the minimizer"<<endl;
  LBFGSbMinimizer4PropertyList<DistanceEvalDirect,FreeSpace,StrongWolfe,
                               TrackingLineMinimizer4PropertyList>
    LM;
  cout<<endl;

  varDistanceEvalDirect vDED(2);
  varFreeSpace vFS;

  varPropertyList<double>::Type CoorSeq,GradSeq;
  varVector<unsigned int> Sz;
  Sz.allocate(4);     Sz=2;
  CoorSeq.allocate(Sz);
  GradSeq.allocate(Sz);
  CoorSeq[0][0]=0;      CoorSeq[0][1]=0;
  CoorSeq[1][0]=0;      CoorSeq[1][1]=1.2;
  CoorSeq[2][0]=1.3;    CoorSeq[2][1]=1.5;
  CoorSeq[3][0]=0.8;    CoorSeq[3][1]=2.2;

  varVector<InteractionMethod<DistanceEvalDirect,FreeSpace> > vIM;
  vIM.allocate(6);
  for(unsigned int i=0;i<3;++i)
    SetInteractionMethod(vIM[i],ParticleParticle_Harmonic);
  for(unsigned int i=3;i<6;++i)
    SetInteractionMethod(vIM[i],ParticleParticle_LJ612);

  varPropertyList<unsigned int> IdxLst;
  Sz.allocate(6);
  Sz=2;
  IdxLst.allocate(Sz);
  IdxLst[0][0]=0;       IdxLst[0][1]=1;
  IdxLst[1][0]=0;       IdxLst[1][1]=2;
  IdxLst[2][0]=0;       IdxLst[2][1]=3;
  IdxLst[3][0]=1;       IdxLst[3][1]=2;
  IdxLst[4][0]=1;       IdxLst[4][1]=3;
  IdxLst[5][0]=2;       IdxLst[5][1]=3;

  varVector<unsigned int> KindSeq(4);
  KindSeq[0]=0;
  KindSeq[1]=1;
  KindSeq[2]=0;
  KindSeq[3]=2;
  varParameterList vPL;
  varVector<unsigned int> kS(18),vS(18);
  refVector<unsigned int> rvS;
  kS=3;
  rvS.refer(vS,0,9);    rvS=Harmonic_NumberParameter;
  rvS.refer(vS,9,9);    rvS=LJ612_NumberParameter;
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
  varVector<refVector<double> > ParamLst(6);
  varVector<unsigned int> prmKey(3);
  for(unsigned int i=0;i<3;++i) {
    prmKey[0]=ParticleParticle_Harmonic;
    for(unsigned int k=0;k<2;++k) prmKey[k+1]=KindSeq[IdxLst[i][k]];
    ParamLst[i].refer(*vPL.get(prmKey));
  }
  for(unsigned int i=3;i<6;++i) {
    prmKey[0]=ParticleParticle_LJ612;
    for(unsigned int k=0;k<2;++k) prmKey[k+1]=KindSeq[IdxLst[i][k]];
    ParamLst[i].refer(*vPL.get(prmKey));
  }

  varPropertyList<unsigned int>::Type Mask;
  varPropertyList<double>::Type dMask;
  Sz.allocate(4);     Sz=2;
  Mask.allocate(Sz);
  dMask.allocate(Sz);
  Mask=1;
  dMask=1.;

  cout<<"Test -- Import data into steepest-descent minimizer"<<endl;
  LM.ImportState(CoorSeq,Mask,dMask,vDED,vFS,ParamLst,vIM,IdxLst);
  cout<<LM.MinE<<endl;
  cout<<endl;

  cout<<"Test -- Minimize"<<endl;
  cout<<LM.Go()<<endl;
  cout<<LM.MinE<<endl;
  cout<<LM.MinCoorSeq<<endl;
  cout<<LM.MinGCount<<"\t"<<LM.MinLineCount<<endl;
  cout<<endl;

  return 1;
}

