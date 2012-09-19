
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

double GetDV(System<double,FreeSpace>& S,Array2DNumeric<double>& Hess,
             double* A,double* B,int* IP,unsigned int N,unsigned int NB,
             unsigned int M) {
  GetHessian(S,Hess,N,NB);
  unsigned int NS=M*3;
  for(unsigned int k=0;k<NS;++k)
  for(unsigned int l=0;l<NS;++l) A[k*NS+l]=Hess[k+3+(N-2-M)*3][l+3+(N-2-M)*3];
  double T;
  for(unsigned int k=0;k<NS;++k) {
    T=0;
    for(unsigned int i=0;i<3;++i) T+=Hess[k+3+(N-2-M)*3][(N-1)*3+i]*S.Velocity()[N-1][i];
    B[k]=-T;
  }
  int INS=static_cast<int>(NS);
  int One=1;
  int Inf;
  dgesv_(&INS,&One,A,&INS,IP,B,&INS,&Inf);
  T=0;
  for(unsigned int i=0;i<NS;++i)  T+=B[i]*B[i];
  T=1./sqrt(T);
  for(unsigned int i=0;i<NS;++i)  B[i]*=T;

  for(unsigned int i=0;i<NB;++i)  S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  T=0;
  for(unsigned int i=N-1-M;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) T+=S.Gradient()[i][k]*S.Gradient()[i][k];
  T=sqrt(T);
  if(T<1e-8)  return 100;
  T=1./T;
  for(unsigned int i=N-1-M;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) S.Gradient()[i][k]*=T;
  T=0;
  for(unsigned int i=N-1-M,n=0;i<N-1;++i)
  for(unsigned int k=0;k<3;++k,++n) T+=B[n]*S.Gradient()[i][k];
  return T;
}

double GetGT(System<double,FreeSpace>& S,Array2DNumeric<double>& Hess,
             Array2DNumeric<double>& GT,unsigned int N,unsigned int NB,
             unsigned int M) {
  static const double IGamma=0.1;
  for(unsigned int i=0;i<NB;++i)  S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  for(unsigned int i=N-1-M;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) S.Velocity()[i][k]=-IGamma*S.Gradient()[i][k];
  GetHessian(S,Hess,N,NB);
  double T;
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) {
    T=0;
    for(unsigned int m=1;m<N;++m)
    for(unsigned int n=0;n<3;++n) T+=Hess[i*3+k][m*3+n]*S.Velocity()[m][n];
    GT[i][k]=T;
  }
  T=0;
  for(unsigned int i=N-1-M;i<N-1;++i)
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
  double *A,*B;
  int *IP;
  Hess.Allocate(N*3,N*3);
  A=new double[(N-2)*3*(N-2)*3];
  B=new double[(N-2)*3];
  IP=new int[(N-2)*3];

  unsigned int NB=NC+N-1;
  unsigned int M=25;
  double T,TT,PT,ZT,ZPT;
  double Step=2e-11;
  double THD=-0.91;

  cout.precision(20);
  Array2DNumeric<double> MV,GT;
  MV.Imprint(S.Location());
  GT.Imprint(MV);

  BoxMuller<MersenneTwisterDSFMT<19937> > BG;
  BG.Allocate();
  BG.InitWithTime();

  ifs.open("ZZZZ");
  for(unsigned int i=0;i<N;++i)
  for(unsigned int k=0;k<3;++k)   ifs>>S.Location()[i][k];
  ifs.close();

  S.Velocity()[N-1][0]=1;

  cout.precision(10);

  ZT=GetGT(S,Hess,GT,N,NB,M);
  do{
    T=GetDV(S,Hess,A,B,IP,N,NB,M);
    if(T<THD) break;
    cout<<T<<'\t'<<ZT<<endl;
    do{
      for(unsigned int i=N-1-M;i<N-1;++i)
      for(unsigned int k=0;k<3;++k) MV[i][k]=BG.Double();
      for(unsigned int i=N-1-M;i<N-1;++i)
      for(unsigned int k=0;k<3;++k) S.Location()[i][k]+=MV[i][k]*Step;
      ZPT=GetGT(S,Hess,GT,N,NB,M);
      PT=GetDV(S,Hess,A,B,IP,N,NB,M);
      //if((fabs(ZPT-ZT)>5)||(PT>T)) {
      if(PT>T) {
        for(unsigned int i=1;i<N-1;++i)
        for(unsigned int k=0;k<3;++k) S.Location()[i][k]-=MV[i][k]*Step;
        //cout<<PT<<"\t"<<ZPT<<endl;
      } else { cout<<"=====A========  "<<ZPT<<"\t"<<PT<<endl; break; }
    } while(true);

    T=GetDV(S,Hess,A,B,IP,N,NB,M);
    if(T<THD) break;
  }while(true);

  for(unsigned int i=0;i<N;++i) {
    for(unsigned int k=0;k<3;++k) cout<<"\t"<<S.Location()[i][k];
    cout<<endl;
  }

  return 0;
}

