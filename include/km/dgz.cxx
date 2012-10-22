
#include "system/interface.h"
#include "boundary/free/interface.h"
#include "array2d/interface.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

FreeSpace FS;
ArrayNumeric<double> Dsp;

void GetHessian(System<double,FreeSpace>& S,Array2DNumeric<double>& Hess,
                unsigned int N,unsigned int NB) {
  Hess.BlasFill(0);
  double T,T1,T2;
  unsigned int I,J,Ik,Jl,Il,Jk;
  for(unsigned int i=0;i<NB;++i) {
    I=S.Interaction(i).Index(0)[0];
    J=S.Interaction(i).Index(0)[1];
    T=1./Distance(Dsp,S.Location()[I],S.Location()[J],FS);
    Dsp.Scale(T);
    T1=2*Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength));
    T2=T1*Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength));
    T2*=T;
    T1-=T2;
    for(unsigned int k=0;k<3;++k) {
      Ik=I*3+k;
      Jk=J*3+k;
      for(unsigned int l=0;l<3;++l) {
        Il=I*3+l;
        Jl=J*3+l;
        T=T2*Dsp[k]*Dsp[l];
        if(k==l)  T+=T1;
        Hess[Ik][Il]+=T;
        Hess[Ik][Jl]-=T;
        Hess[Jk][Il]-=T;
        Hess[Jk][Jl]+=T;
      }
    }
  }
}

double GetGT(System<double,FreeSpace>& S,Array2DNumeric<double>& Hess,
             unsigned int N,unsigned int NB,Array2DNumeric<double>& GT,
             Array<bool>& Used) {
  GetHessian(S,Hess,N,NB);
  static const double IGamma=0.1;
  for(unsigned int i=0;i<NB;++i)
    S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k)
    S.Velocity()[i][k]=(Used[i]?-IGamma*S.Gradient()[i][k]:0);
  double T,Sum;
  Sum=0;
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) {
    if(Used[i]) {
      T=0;
      for(unsigned int m=0;m<N;++m)
      for(unsigned int n=0;n<3;++n)
        T+=Hess[i*3+k][m*3+n]*S.Velocity()[m][n];
    } else
      T=0;
    GT[i][k]=T;
    Sum+=T*T;
  }
  return sqrt(Sum);
}

int main() {

  Dsp.Allocate(3);

  const unsigned int N=67;
  System<double,FreeSpace> S;
  S.AllocateKind(N);
  for(unsigned int i=0;i<N;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(3);

  ifstream ifs;
  ifs.open("NAT");
  for(unsigned int i=0;i<N;++i)
  for(unsigned int k=0;k<3;++k)
    ifs>>S.Location()[i][k];
  ifs.close();

  const unsigned int NB=137+N-1;
  Array2DNumeric<unsigned int>  ID;
  ID.Allocate(NB,2);
  for(unsigned int i=0;i<N-1;++i) {
    ID[i][0]=i;
    ID[i][1]=i+1;
  }
  ifs.open("CntMap");
  for(unsigned int i=N-1;i<NB;++i)
    ifs>>ID[i][0]>>ID[i][1];
  ifs.close();

  Array2D<InteractionFuncName>  IFN;
  IFN.Allocate(NB,1);
  for(unsigned int i=0;i<NB;++i)
    IFN[i][0]=Harmonic;
  S.AllocateInteraction(IFN,3);
  for(unsigned int i=0;i<NB;++i) {
    S.Interaction(i).Index(0)[0]=ID[i][0];
    S.Interaction(i).Index(0)[1]=ID[i][1];
  }
  for(unsigned int i=0;i<NB;++i)
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength))=
      Distance(Dsp,S.Location()[ID[i][0]],S.Location()[ID[i][1]],FS);
  for(unsigned int i=0;i<N-2;++i)
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength))=100.;
  Value<double>(S.Interaction(N-2).Parameter(0,HarmonicEqStrength))=10.;
  for(unsigned int i=N-1;i<NB;++i)
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength))=20.;
  for(unsigned int i=0;i<NB;++i)
    S.Interaction(i).ParameterBuild(0);

  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(NB);
  for(unsigned int i=0;i<NB;++i)
    S.InteractionGroup(0).WorkID(i)=i;

  Array2DNumeric<double> Hess,GT;
  Hess.Allocate(N*3,N*3);
  GT.Imprint(S.Location());

  Array<bool> Used;
  Array<unsigned int> UsedID;
  unsigned int NUsed;

  Used.Allocate(N);
  for(unsigned int i=0;i<N;++i)
    Used[i]=true;
  /*
  //=======
  Used[65]=true;
  //=======
  Used[42]=true;
  Used[43]=true;
  Used[44]=true;
  Used[45]=true;
  Used[46]=true;
  Used[47]=true;
  Used[48]=true;
  Used[49]=true;
  Used[50]=true;
  //=======
  */
  NUsed=0;
  for(unsigned int i=0;i<N;++i)
    NUsed+=(Used[i]?1:0);
  UsedID.Allocate(NUsed);
  for(unsigned int i=0,n=0;i<N;++i)
    if(Used[i]) UsedID[n++]=i;

  double Step=1e-5;
  double TTH=0.01;
  double ZT;
  unsigned int MI;

  /*
  ifs.open("TMPP");
  for(unsigned int i=0;i<N;++i)
  for(unsigned int k=0;k<3;++k)
    ifs>>S.Location()[i][k];
  ifs.close();
  */

  S.Velocity().Fill(0);
  S.Velocity()[N-1][0]=1.;

  ZT=GetGT(S,Hess,N,NB,GT,Used);

  cout.precision(16);
  while(ZT>TTH) {
    for(unsigned int i=0;i<NUsed;++i) {
      MI=UsedID[i];
      for(unsigned int k=0;k<3;++k) 
        S.Location()[MI][k]+=1e-5/ZT*GT[MI][k];
    }
    ZT=GetGT(S,Hess,N,NB,GT,Used);
    cout<<ZT<<endl;
  }

  for(unsigned int i=0;i<N;++i) {
    for(unsigned int k=0;k<3;++k)
      cout<<"\t"<<S.Location()[i][k];
    cout<<endl;
  }


  return 0;
}

