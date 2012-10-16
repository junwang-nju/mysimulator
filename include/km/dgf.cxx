
#include "system/interface.h"
#include "pdb-file/interface.h"
#include "boundary/free/interface.h"
#include "random/interface.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
using namespace std;

extern "C" {
  void dgesv_(int*,int*,double*,int*,int*,double*,int*,int*);
}

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
      Ik=I*3+k;   Jk=J*3+k;
      for(unsigned int l=0;l<3;++l) {
        Il=I*3+l;   Jl=J*3+l;
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
             Array2DNumeric<double>& GT,unsigned int N,unsigned int NB) {
  static const double IGamma=0.1;
  for(unsigned int i=0;i<NB;++i)  S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k)
    S.Velocity()[i][k]=-IGamma*S.Gradient()[i][k];
  double T;
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) {
    T=0;
    for(unsigned int m=0;m<N;++m)
    for(unsigned int n=0;n<3;++n) T+=Hess[i*3+k][m*3+n]*S.Velocity()[m][n];
    GT[i][k]=T;
  }
  T=0;
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k)
    T+=GT[i][k]*GT[i][k];
  return sqrt(T);
}

int main() {
  const unsigned int N=67;
  System<double,FreeSpace> S;
  S.AllocateKind(N);
  for(unsigned int i=0;i<N;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(3);

  ifstream ifs;
  ifs.open("XAxis");
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k)   ifs>>S.Location()[i][k];
  ifs.close();

  for(unsigned int i=2;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) S.Location()[i][k]-=S.Location()[1][k];
  for(unsigned int k=0;k<3;++k) S.Location()[1][k]=0;
  ArrayNumeric<double> R1,R2,R3,R4;
  R1.Allocate(3);
  R2.Allocate(3);
  R3.Allocate(3);
  R4.Allocate(3);
  R1.Copy(S.Location()[N-2]);
  R1.Scale(1./R1.Norm());
  R2.Copy(R1);
  R2[0]+=1;
  R2.Shift(R1,-_Dot(R1,R2));
  R2.Scale(1./R2.Norm());
  Cross(R3,R1,R2);
  R3.Scale(1./R3.Norm());
  for(unsigned int i=2;i<N-1;++i) {
    R4.Fill(0);
    for(unsigned int k=0;k<3;++k) R4[0]+=S.Location()[i][k]*R1[k];
    for(unsigned int k=0;k<3;++k) R4[1]+=S.Location()[i][k]*R2[k];
    for(unsigned int k=0;k<3;++k) R4[2]+=S.Location()[i][k]*R3[k];
    S.Location()[i].Copy(R4);
  }
  for(unsigned int i=1;i<N-1;++i) S.Location()[i][0]+=1;
  for(unsigned int k=0;k<3;++k) S.Location()[0][k]=0;
  S.Location()[N-1].Copy(S.Location()[N-2]);
  S.Location()[N-1][0]+=1;

  S.Velocity().Fill(0);

  PDBFile PF;
  PDBObject PO;
  PF.Load("2CI2");
  PF.Produce(PO);
  Array2D<unsigned int> CM;
  const unsigned int NP=PO.ProduceContact<SheaDef,UseFirstModel>(CM);
  unsigned int NC=0;
  for(unsigned int i=0;i<NP;++i)
    if(CM[i][0]!=CM[i][2])          ++NC;
    else if(CM[i][3]-CM[i][1]>=4)   ++NC;


  Array2D<InteractionFuncName>  IFN;
  IFN.Allocate(NC+N-1,1);
  for(unsigned int i=0;i<NC+N-1;++i)  IFN[i][0]=Harmonic;
  S.AllocateInteraction(IFN,3);
  for(unsigned int i=0;i<N-3;++i) {
    S.Interaction(i).Index(0)[0]=i+1;
    S.Interaction(i).Index(0)[1]=i+2;
  }
  for(unsigned int i=0,n=0;i<NP;++i)
    if((CM[i][0]!=CM[i][2])||(CM[i][3]-CM[i][1]>=4)) {
      S.Interaction(n+N-3).Index(0)[0]=PO.Index(CM[i][0],CM[i][1])+1;
      S.Interaction(n+N-3).Index(0)[1]=PO.Index(CM[i][2],CM[i][3])+1;
      ++n;
    }
  S.Interaction(NC+N-3).Index(0)[0]=0;
  S.Interaction(NC+N-3).Index(0)[1]=1;
  S.Interaction(NC+N-2).Index(0)[0]=N-2;
  S.Interaction(NC+N-2).Index(0)[1]=N-1;

  Dsp.Allocate(3);
  for(unsigned int i=0;i<NC+N-1;++i)
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength))=
      Distance(Dsp,S.Location()[S.Interaction(i).Index(0)[0]],
                   S.Location()[S.Interaction(i).Index(0)[1]],FS);
  for(unsigned int i=0;i<N-3;++i) {
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength))=100.;
    S.Interaction(i).ParameterBuild(0);
  }
  for(unsigned int i=0;i<NC;++i) {
    Value<double>(S.Interaction(i+N-3).Parameter(0,HarmonicEqStrength))=20;
    S.Interaction(i+N-3).ParameterBuild(0);
  }
  Value<double>(S.Interaction(NC+N-3).Parameter(0,HarmonicEqStrength))=20.;
  Value<double>(S.Interaction(NC+N-2).Parameter(0,HarmonicEqStrength))=20.;
  S.Interaction(NC+N-3).ParameterBuild(0);
  S.Interaction(NC+N-2).ParameterBuild(0);

  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(IFN.Size());
  for(unsigned int i=0;i<IFN.Size();++i)  S.InteractionGroup(0).WorkID(i)=i;

  Array2DNumeric<double> Hess;
  Hess.Allocate(N*3,N*3);

  unsigned int NB=NC+N-1;
  double ZT;
  double Step=3e-6;
  double TTH=0.3;

  cout.precision(20);
  Array2DNumeric<double> GT;
  GT.Imprint(S.Location());

  ifs.open("GGGG");
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k)   ifs>>S.Location()[i][k];
  ifs.close();

  S.Velocity().Fill(0.);
  S.Velocity()[N-1][0]=1;

  GetHessian(S,Hess,N,NB);
  ZT=GetGT(S,Hess,GT,N,NB);
  cout<<ZT<<endl; //getchar();

  do {
    for(unsigned int i=1;i<N-1;++i)
    for(unsigned int k=0;k<3;++k)
      S.Location()[i][k]+=Step*GT[i][k];
    GetHessian(S,Hess,N,NB);
    ZT=GetGT(S,Hess,GT,N,NB);
    cout<<ZT<<endl;
    if(ZT<TTH)  break;
  } while(true);

  for(unsigned int i=1;i<N-1;++i) {
    for(unsigned int k=0;k<3;++k)
      cout<<"\t"<<S.Location()[i][k];
    cout<<endl;
  }

  /*
  do {
    GetHessian(S,Hess,N,NB);
    ZT=GetGT(S,Hess,GT,N,NB);
    VT=DGetDV(S,Hess,A,B,IP,N,NB);
    cout<<ZT<<"\t"<<VT<<endl;
    if(ZT<10) break;
    if(VT<-0.9) break;

    MV.Copy(S.Location());
    GetDV(S,Hess,A,B,IP,N,NB,Step*0.5);
    for(unsigned int i=1,n=0;i<N-1;++i)
    for(unsigned int k=0;k<3;++k,++n) S.Location()[i][k]+=B[n];
    GetHessian(S,Hess,N,NB);
    GetDV(S,Hess,A,B,IP,N,NB,Step);
    for(unsigned int i=1,n=0;i<N-1;++i)
    for(unsigned int k=0;k<3;++k,++n) S.Location()[i][k]=MV[i][k]+B[n];
  } while(true);
  */

  return 0;
}

