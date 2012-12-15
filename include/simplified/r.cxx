
#include "system/interface.h"
#include "basic/util/point-2-dihedral.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main() {
  System<FreeSpace<3>>  S;
  S._X.allocate(65,3);
  ifstream ifs;
  ifs.open("XAxis");
  for(unsigned int i=0;i<65;++i)
  for(unsigned int j=0;j<3;++j)
    ifs>>S._X[i][j];
  ifs.close();
  S._V.imprint_structure(S._X);
  S._G.imprint_structure(S._X);
  S._E.reset(new double,__delete_unit<double>);

  const unsigned int NC=(64*(64+1))/2;
  S._Interaction.allocate(NC);
  Array2D<InteractionName> FN;
  FN.allocate(NC,1);
  for(unsigned int i=0;i<64;++i)  FN[i][0]=InteractionName::PairHarmonic;
  for(unsigned int i=0;i<63;++i)  FN[i+64][0]=InteractionName::AngleHarmonic;
  for(unsigned int i=0;i<62;++i)  FN[i+64+63][0]=InteractionName::DihedralDualPeriodicCommonPhase;
  for(unsigned int i=0;i<153;++i) FN[i+64+63+62][0]=InteractionName::PairLJ1012;
  for(unsigned int i=153+64+63+62;i<NC;++i) FN[i]=InteractionName::PairCoreLJ612;
  for(unsigned int i=0;i<NC;++i) {
    S._Interaction[i].allocate(FN[i]);
    S._Interaction[i].imprint_gradient_energy(S._X);
  }

  Array<Double> tdsp(3);
  for(unsigned int i=0;i<64;++i) {
    S._Interaction[i].ID(0)[0]=i;
    S._Interaction[i].ID(0)[1]=i+1;
    S._Interaction[i].Parameter(0)[PairHarmonicParameterName::EqLength]=
      Distance<SystemKindName::Particle,SystemKindName::Particle>(
          tdsp,S._X[i],S._X[i+1],S._Interaction[i].Geometry());
    S._Interaction[i].Parameter(0)[PairHarmonicParameterName::EqStrength]=100.;
    S._Interaction[i].Parameter(0).build();
  }
  double td1,td2,td3;
  for(unsigned int i=0;i<63;++i) {
    S._Interaction[i+64].ID(0)[0]=i;
    S._Interaction[i+64].ID(0)[1]=i+1;
    S._Interaction[i+64].ID(0)[2]=i+2;
    td1=DistanceSQ<SystemKindName::Particle,SystemKindName::Particle>(
          tdsp,S._X[i],S._X[i+2],S._Interaction[i+64].Geometry());
    td2=Distance<SystemKindName::Particle,SystemKindName::Particle>(
          tdsp,S._X[i],S._X[i+1],S._Interaction[i+64].Geometry());
    td3=Distance<SystemKindName::Particle,SystemKindName::Particle>(
          tdsp,S._X[i+1],S._X[i+2],S._Interaction[i+64].Geometry());
    S._Interaction[i+64].Parameter(0)[AngleHarmonicParameterName::EqAngle]=
      acos((-td1+td2*td2+td3*td3)/(2*td2*td3));
    S._Interaction[i+64].Parameter(0)[AngleHarmonicParameterName::EqStrength]=20.;
    S._Interaction[i+64].Parameter(0).build();
  }
  for(unsigned int i=0;i<62;++i) {
    for(unsigned int k=0;k<4;++k)
      S._Interaction[i+64+63].ID(0)[k]=i+k;
    S._Interaction[i+64+63].Parameter(0)[DihedralDualPeriodicCommonPhaseParameterName::Double::Phase]=Dihedral(S._X[i],S._X[i+1],S._X[i+2],S._X[i+3]);
    S._Interaction[i+64+63].Parameter(0).child(DihedralDualPeriodicCommonPhaseParameterName::Child::Period1)[DihedralPeriodicParameterName::Double::Strength]=1.;
    S._Interaction[i+64+63].Parameter(0).child(DihedralDualPeriodicCommonPhaseParameterName::Child::Period1)(DihedralPeriodicParameterName::Int::Frequency)=1;
    S._Interaction[i+64+63].Parameter(0).child(DihedralDualPeriodicCommonPhaseParameterName::Child::Period2)[DihedralPeriodicParameterName::Double::Strength]=0.5;
    S._Interaction[i+64+63].Parameter(0).child(DihedralDualPeriodicCommonPhaseParameterName::Child::Period2)(DihedralPeriodicParameterName::Int::Frequency)=3;
    S._Interaction[i+64+63].Parameter(0).build();
  }
  ifs.open("2ci2.cnt");
  unsigned int z;
  double zf;
  ifs>>z;
  ifs>>z;
  Array2D<UInt> FG;
  FG.allocate(65,65);
  FG=0;
  for(unsigned int i=0;i<153;++i) {
    ifs>>S._Interaction[i+64+63+62].ID(0)[0];
    ifs>>S._Interaction[i+64+63+62].ID(0)[1];
    FG[S._Interaction[i+64+63+62].ID(0)[0]][S._Interaction[i+64+63+62].ID(0)[1]]=1;
    ifs>>S._Interaction[i+64+63+62].Parameter(0)[PairLJ1012ParameterName::EqRadius];
    S._Interaction[i+64+63+62].Parameter(0)[PairLJ1012ParameterName::EqEnergyDepth]=
      1.;
    S._Interaction[i+64+63+62].Parameter(0).build();
  }
  for(unsigned int i=0,n=153+64+63+62;i<65;++i)
  for(unsigned int j=i+4;j<65;++j) {
    if(FG[i][j]==1) continue;
    S._Interaction[n].ID(0)[0]=i;
    S._Interaction[n].ID(0)[1]=j;
    S._Interaction[n].Parameter(0)[PairCoreLJ612ParameterName::EqRadius]=4.;
    S._Interaction[n].Parameter(0)[PairCoreLJ612ParameterName::EqEnergyDepth]=1.;
    S._Interaction[n].Parameter(0).build();
    ++n;
    if(n>NC)  { cerr<<">NC!"<<endl; return 1; }
  }

  mt19937 engine;
  normal_distribution<> rdist(0,1);
  auto generator=bind(rdist,engine);
  for(unsigned int i=0;i<S._V.Data().size();++i)
    S._V.Data()[i]=generator();
  S._V*=Double(0.5);

  double dt=0.001;
  double gamma=0.1;
  double gammaL=0.5;
  double temperature=1.13;
  double rsize=sqrt(2*gamma*temperature*dt*0.5);

  S._G=0;
  for(unsigned int i=0;i<NC;++i) {
    S._Interaction[i].ClearStatus();
    S._Interaction[i].UpdateEnergyGradient(S._X);
    S._G+=S._Interaction[i].Gradient();
  }

  double DS,DS0,GM;
  Array2D<Double,ArrayKernelName::SSE,__system_vec_type<3>::NAME> dV;
  Array<Double,__system_vec_type<3>::NAME> tV(3);
  unsigned int I,J;
  dV.imprint_structure(S._X);
  cout.precision(16);
  for(unsigned int rt=0;rt<100000000;++rt) {
    //S._V-=Double(0.5*dt)*S._G;
    //S._V=Double(1-gamma*0.5*dt)*S._V-Double(0.5*dt)*S._G;
    dV=0;
    for(unsigned int i=0;i<153;++i) {
      SystemInteraction<FreeSpace<3>>& _SI=S._Interaction[i+64+63+62];
      I=_SI.ID(0)[0];
      J=_SI.ID(0)[1];
      DS=_SI.Function(0)._pre[PairwisePreName::DistanceSQ];
      DS0=_SI.Parameter(0)[PairLJ1012ParameterName::EqRadius];
      DS0*=DS0;
      //GM=(DS<DS0?gammaL:(DS<DS0*5?gammaL*(1-(DS-DS0)/(4*DS0)):0));
      if(DS<DS0)  GM=gammaL;
      else GM=-gammaL*_SI.Energy();
      tV=(S._V[I]-S._V[J])*Double(-GM*0.5*dt);
      for(unsigned int k=0;k<3;++k)
        tV[k]+=sqrt(2*GM*temperature*dt*0.5)*generator();
      dV[I]+=tV;
      dV[J]-=tV;
    }
    dV+=Double(-gamma*0.5*dt)*S._V;
    S._V+=dV-Double(0.5*dt)*S._G;
    for(unsigned int i=0;i<S._V.Data().size();++i)
      S._V.Data()[i]+=rsize*generator();
    S._X+=Double(dt)*S._V;
    S._G=0;
    *S._E=0;
    for(unsigned int i=0;i<NC;++i) {
      S._Interaction[i].ClearStatus();
      S._Interaction[i].UpdateEnergyGradient(S._X);
      S._G+=S._Interaction[i].Gradient();
      //*(S._E)+=S._Interaction[i].Energy();
    }
    //S._V-=Double(0.5*dt)*S._G;
    //for(unsigned int i=0;i<S._V.Data().size();++i)
    //  S._V.Data()[i]+=rsize*generator();
    //S._V*=Double(1./(1+gamma*dt*0.5));
    dV=0;
    S._V-=Double(0.5*dt)*S._G;
    for(unsigned int i=0;i<S._V.Data().size();++i)
      S._V.Data()[i]+=rsize*generator();
    for(unsigned int i=0;i<153;++i) {
      SystemInteraction<FreeSpace<3>>& _SI=S._Interaction[i+64+63+62];
      I=_SI.ID(0)[0];
      J=_SI.ID(0)[1];
      DS=_SI.Function(0)._pre[PairwisePreName::DistanceSQ];
      DS0=_SI.Parameter(0)[PairLJ1012ParameterName::EqRadius];
      DS0*=DS0;
      //GM=(DS<DS0?gammaL:(DS<DS0*5?gammaL*(1-(DS-DS0)/(4*DS0)):0));
      if(DS<DS0)  GM=gammaL;
      else GM=-gammaL*_SI.Energy();
      for(unsigned int k=0;k<3;++k)
        tV[k]=sqrt(2*GM*temperature*dt*0.5)*generator();
      S._V[I]+=tV;
      S._V[J]-=tV;
    }
    for(unsigned int i=0;i<153;++i) {
      I=S._Interaction[i+64+63+62].ID(0)[0];
      J=S._Interaction[i+64+63+62].ID(0)[1];
      DS=
        __square_root(S._Interaction[i+64+63+62].
                      Function(0)._pre[PairwisePreName::DistanceSQ]);
      DS0=
        S._Interaction[i+64+63+62].
        Parameter(0)[PairLJ1012ParameterName::EqRadius];
      //GM=(DS<DS0?gammaL:(DS<DS0*5?gammaL*(1-(DS-DS0)/(4*DS0)):0));
      if(DS<DS0)  GM=gammaL;
      else GM=-gammaL*S._Interaction[i+64+63+62].Energy();
      tV=(S._V[I]-S._V[J])*Double(-GM*0.5*dt);
      dV[I]+=tV;
      dV[J]-=tV;
    }
    dV+=Double(-gamma*0.5*dt)*S._V;
    S._V+=dV;
    if(rt%200==0) {
      *S._E=0;
      for(unsigned int i=0;i<153;++i)
        *S._E+=S._Interaction[i+64+63+62].Energy();
      cout<<rt<<"\t"<<*S._E<<"\t"<<0.5*NormSQ(S._V.Data())<<endl;
    }
  }

  return 0;
}

