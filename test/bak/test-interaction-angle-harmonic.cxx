
#include "interaction-angle-harmonic.h"
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include "parameter-generate-angle-harmonic.h"
#include "var-property-list.h"
#include <iostream>

using namespace std;

int main() {

  cout<<"Test -- Calculate Energy of Angle Harmonic"<<endl;
  varDistanceEvalDirect vDED(3);
  varFreeSpace vFS;
  varPropertyList<double>::Type v,g;
  varVector<unsigned int> Sz(3);
  Sz=3;
  v.allocate(Sz);
  g.allocate(Sz);
  v[0]=0.;
  v[1]=0.;    v[1][0]=1.2;
  v[2]=0.;    v[2][0]=1.5;  v[2][1]=1;  v[2][2]=0.5;
  varVector<unsigned int> idx(3);
  idx[0]=0;   idx[1]=1;   idx[2]=2;
  varVector<double> prm(AngHarmonic_NumberParameter);
  prm[0]=0.6667*M_PI;
  prm[1]=20;
  ParameterGenerateAngHarmonic(prm);
  double E=0.;
  EFunc_Angle_Harmonic(v.Structure(),idx,prm,v.Structure(),vDED,vFS,E);
  cout<<E<<endl;
  cout<<endl;
  
  cout<<"Test -- Calculate Gradient for Angle-Harmonic"<<endl;
  varPropertyList<double>::Type tmVec;
  Sz.allocate(4);
  Sz=3;
  tmVec.allocate(Sz);
  g=0;
  GFunc_Angle_Harmonic(v.Structure(),idx,prm,tmVec.Structure(),vDED,vFS,
                       g.Structure());
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- Calculate Energy and Gradient for Angle-Harmonic"<<endl;
  E=0.;
  g=0;
  BFunc_Angle_Harmonic(v.Structure(),idx,prm,tmVec.Structure(),vDED,vFS,
                       E,g.Structure());
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 1;
}

