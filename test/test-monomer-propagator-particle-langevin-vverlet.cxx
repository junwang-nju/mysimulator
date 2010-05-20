
#include "monomer-propagator-particle-langevin-vverlet.h"
#include <iostream>
using namespace std;

int main() {

  Vector<double> Coor,Vel,Grad,iMass,RandV;
  allocate(Coor,4);
  allocate(Vel,4);
  allocate(Grad,4);
  allocate(iMass,4);
  allocate(RandV,4);
  assign(Coor,0.);
  for(unsigned int i=0;i<Vel.size;++i) Vel[i]=i+1;
  for(unsigned int i=0;i<Grad.size;++i) Grad[i]=i*2;
  assign(iMass,0.5);

  Vector<UniqueParameter> GPrm, Prm;
  allocate(GPrm,NumberParameterLV);
  allocate(Prm,NumberParameterParticleLV);

  GPrm[DeltaTime]=1.;
  GPrm[HalfDeltaTime]=0.5;

  cout<<"Test -- set hydro-radius"<<endl;
  double tmd;
  tmd=1.;
  PLVSet_HydrodynamicRadius(Prm(),&tmd);
  cout<<Prm[PLV_HydrodynamicRadius].d<<endl;
  cout<<endl;

  cout<<"Test -- set random velocity"<<endl;
  PLVSet_RandomVelocityPointer(Prm(),RandV());
  for(unsigned int i=0;i<4;++i)
    *(reinterpret_cast<double*>(Prm[PLV_RandomVelocityPointer].ptr)+i)=i*2.+.5;
  cout<<RandV<<endl;
  cout<<endl;

  GPrm[LV_Viscosity]=0.2;
  GPrm[LV_TemperatureDeltaT]=1.;
  cout<<"Test -- synchronize"<<endl;
  PLVSynchronize(iMass,GPrm(),Prm());
  cout<<Prm[PLV_HalfDeltaTIvM].d<<endl;
  cout<<Prm[PLV_FrictionCoef].d<<endl;
  cout<<Prm[PLV_RandomVelocitySize].d<<endl;
  cout<<Prm[PLV_FactorBeforeG].d<<endl;
  cout<<Prm[PLV_FactorAfterG].d<<endl;
  cout<<endl;

  GaussianRNG gng;
  allocate(gng);
  init(gng,1290237);
  GPrm[LV_GaussianRNGPointer].ptr=reinterpret_cast<void*>(&gng);

  cout<<"Test -- before G"<<endl;
  PLVMove_BeforeG(Coor(),Vel(),Grad(),4,GPrm(),Prm());
  cout<<RandV<<endl;
  cout<<Coor<<endl;
  cout<<Vel<<endl;
  cout<<endl;

  cout<<"Test -- after G"<<endl;
  PLVMove_AfterG(Coor(),Vel(),Grad(),4,GPrm(),Prm());
  cout<<RandV<<endl;
  cout<<Coor<<endl;
  cout<<Vel<<endl;
  cout<<endl;

  return 0;
}

