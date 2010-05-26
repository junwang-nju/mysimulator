
#include "monomer-propagator-particle-conste-vverlet.h"
#include <iostream>
using namespace std;

int main() {

  Vector<double> Coor,Vel,Grad,iMass,dMask;
  allocate(Coor,4);
  allocate(Vel,4);
  allocate(Grad,4);
  allocate(iMass,4);
  allocate(dMask,4);
  assign(Coor,0.);
  for(unsigned int i=0;i<Vel.size;++i) Vel[i]=i+1;
  for(unsigned int i=0;i<Grad.size;++i) Grad[i]=i*2;
  assign(iMass,0.5);
  assign(dMask,1.);

  Vector<UniqueParameter> GPrm, Prm;
  allocate(GPrm,NumberParameterEV);
  allocate(Prm,NumberParameterParticleEV);

  GPrm[DeltaTime]=1.;
  GPrm[HalfDeltaTime]=0.5;

  cout<<"Test -- synchronize"<<endl;
  PEVSynchronize(iMass,GPrm(),Prm());
  cout<<Prm[PEV_HalfDeltaTIvM].d<<endl;
  cout<<endl;

  cout<<"Test -- before G"<<endl;
  PEVMove_BeforeG(Coor(),Vel(),Grad(),dMask(),4,GPrm(),Prm());
  cout<<Coor<<endl;
  cout<<Vel<<endl;
  cout<<endl;

  cout<<"Test -- after G"<<endl;
  PEVMove_AfterG(Coor(),Vel(),Grad(),dMask(),4,GPrm(),Prm());
  cout<<Coor<<endl;
  cout<<Vel<<endl;
  cout<<endl;
  return 0;
}

