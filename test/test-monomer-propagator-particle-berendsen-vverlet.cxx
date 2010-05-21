
#include "monomer-propagator-particle-berendsen-vverlet.h"
#include <iostream>
using namespace std;

int main() {

  Vector<double> Coor,Vel,Grad,iMass;
  allocate(Coor,4);
  allocate(Vel,4);
  allocate(Grad,4);
  allocate(iMass,4);
  assign(Coor,0.);
  for(unsigned int i=0;i<Vel.size;++i) Vel[i]=i+1;
  for(unsigned int i=0;i<Grad.size;++i) Grad[i]=i*2;
  assign(iMass,0.5);

  Vector<UniqueParameter> GPrm, Prm;
  allocate(GPrm,NumberParameterBV);
  allocate(Prm,NumberParameterParticleBV);

  GPrm[DeltaTime]=1.;
  GPrm[HalfDeltaTime]=0.5;

  cout<<"Test -- synchronize"<<endl;
  PBVSynchronize(iMass,GPrm(),Prm());
  cout<<Prm[PBV_HalfDeltaTIvM].d<<endl;
  cout<<endl;

  cout<<"Test -- before G"<<endl;
  PBVMove_BeforeG(Coor(),Vel(),Grad(),4,GPrm(),Prm());
  cout<<Coor<<endl;
  cout<<Vel<<endl;
  cout<<endl;

  cout<<"Test -- after G"<<endl;
  PBVMove_AfterG(Coor(),Vel(),Grad(),4,GPrm(),Prm());
  cout<<Coor<<endl;
  cout<<Vel<<endl;
  cout<<endl;

  GPrm[BV_AScaleFactor]=0.4;
  cout<<"Test -- post process"<<endl;
  PBVMove_PostProcess(Coor(),Vel(),Grad(),4,GPrm(),Prm());
  cout<<Coor<<endl;
  cout<<Vel<<endl;
  cout<<endl;

  GPrm[BV_BScaleFactor]=0.3;
  cout<<"Test -- post process"<<endl;
  PBVMove_PreProcess(Coor(),Vel(),Grad(),4,GPrm(),Prm());
  cout<<Coor<<endl;
  cout<<Vel<<endl;
  cout<<endl;

  return 0;
}

