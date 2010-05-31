
#include "interaction-dihedral-periodic.h"
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include "parameter-generate-dihedral-periodic.h"
#include "var-property-list.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- Calculate Energy of Dihedral Paeriodic"<<endl;
  varDistanceEvalDirect vDED(3);
  varFreeSpace vFS;
  varPropertyList<double>::Type v,g;
  varVector<unsigned int> Sz(4);
  Sz=3;
  v.allocate(Sz);
  g.allocate(Sz);
  v[0]=0;   v[0][0]=-1.;    v[0][1]=-2.;
  v[1]=0;
  v[2]=0;   v[2][0]=3;
  v[3]=0;   v[3][0]=4;      v[3][1]=2;    v[3][2]=2;
  varVector<unsigned int> idx(4);
  for(unsigned int i=0;i<4;++i) idx[i]=i;
  varVector<double> prm(8);
  prm[0]=1.;    prm[1]=1;   prm[2]=0.;
  prm[4]=0.5;   prm[5]=3;   prm[6]=0.;
  ParameterGenerateDihedralPeriodic(prm);
  varPropertyList<double>::Type tmVec;
  Sz.allocate(6);
  Sz=3;
  tmVec.allocate(Sz);
  double E=0.;
  EFunc_Dihedral_Periodic(v.Structure(),idx,prm,tmVec.Structure(),vDED,vFS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- Calculate Gradient for Dihedral Periodic"<<endl;
  g=0.;
  GFunc_Dihedral_Periodic(v.Structure(),idx,prm,tmVec.Structure(),vDED,vFS,
                          g.Structure());
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- Calculate Energy and Gradient for Dihedral Periodic"<<endl;
  E=0.;
  g=0.;
  BFunc_Dihedral_Periodic(v.Structure(),idx,prm,tmVec.Structure(),vDED,vFS,
                          E,g.Structure());
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;
  return 1;
}

