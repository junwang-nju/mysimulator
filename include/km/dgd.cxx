
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
             int* Used, int* UsedID, unsigned int NU) {
  double T;
  for(unsigned int i=0;i<NB;++i)  S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  T=0;
  for(unsigned int i=0;i<NU;++i)
  for(unsigned int k=0;k<3;++k) T+=S.Gradient()[UsedID[i]][k]*
                                   S.Gradient()[UsedID[i]][k];
  T=sqrt(T);
  cout<<"-----1-------\t"<<T<<endl;  getchar();
  if(T<1e-8)  return 100;
  T=1./T;
  for(unsigned int i=0;i<NU;++i)
  for(unsigned int k=0;k<3;++k) S.Gradient()[UsedID[i]][k]*=T;

  unsigned int NS=NU*3;
  for(unsigned int i=0,m=0;i<NU;++i)
  for(unsigned int k=0;k<3;++k,++m)
  for(unsigned int j=0,n=0;j<NU;++j)
  for(unsigned int l=0;l<3;++l,++n) {
    A[m*NS+n]=Hess[UsedID[i]*3+k][UsedID[j]*3+l];
  }
  for(unsigned int i=0,m=0;i<NU;++i)
  for(unsigned int k=0;k<3;++k,++m) {
    T=0;
    for(unsigned int g=0;g<3;++g)
      T+=Hess[UsedID[i]*3+k][(N-1)*3+g]*S.Velocity()[N-1][g];
    B[m]=-T;
  }
  int INS=static_cast<int>(NS);
  int One=1;
  int Inf;
  dgesv_(&INS,&One,A,&INS,IP,B,&INS,&Inf);
  T=0;
  for(unsigned int i=0;i<NS;++i)  T+=B[i]*B[i];
  //cout<<T<<endl;  getchar();
  cout<<"-----2-------\t"<<T<<endl;  getchar();
  T=1./sqrt(T);
  //cout<<T<<endl;  getchar();
  for(unsigned int i=0;i<NS;++i)  B[i]*=T;

  T=0;
  for(unsigned int i=0,m=0;i<NU;++i)
  for(unsigned int k=0;k<3;++k,++m) T+=S.Gradient()[UsedID[i]][k]*B[m];

  return T;
}

double GetGT(System<double,FreeSpace>& S,Array2DNumeric<double>& Hess,
             Array2DNumeric<double>& GT,unsigned int N,unsigned int NB,
             int* Used, int* UsedID, int NU) {
  static const double IGamma=0.1;
  for(unsigned int i=0;i<NB;++i)  S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) {
    if(Used[i]==0) S.Velocity()[i][k]=0.;
    else S.Velocity()[i][k]=-IGamma*S.Gradient()[i][k];
  }
  double T;
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k) {
    if(Used[i]==0)  GT[i][k]=0;
    else {
      T=0;
      for(unsigned int m=0;m<N;++m)
      for(unsigned int n=0;n<3;++n) T+=Hess[i*3+k][m*3+n]*S.Velocity()[m][n];
      GT[i][k]=T;
    }
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
  double *A,*B;
  int *IP;
  Hess.Allocate(N*3,N*3);
  A=new double[(N-2)*3*(N-2)*3];
  B=new double[(N-2)*3];
  IP=new int[(N-2)*3];

  int *Used,*UsedID;
  unsigned int NUsed;
  Used=new int[N];
  for(unsigned int i=0;i<N;++i) Used[i]=0;

  NUsed=1;
  NUsed=1+9;
  //NUsed=1+9+14;
  //NUsed=1+9+16+20;
  //NUsed=1+9+16+20+16;
  //NUsed=1+9+16+20+16+3;
  //NUsed=1+9+14+15+14;
  //NUsed=1+9+14+15+14+2;
  UsedID=new int[NUsed];
  // ----
  Used[65]=1;
  // ----
  Used[42]=1;
  Used[43]=1;
  Used[44]=1;
  Used[45]=1;
  Used[46]=1;
  Used[47]=1;
  Used[48]=1;
  Used[49]=1;
  Used[64]=1;
  // ----
  //Used[4]=1;
  //Used[5]=1;
  //Used[21]=1;
  //Used[25]=1;
  //Used[27]=1;
  //Used[28]=1;
  //Used[29]=1;
  //Used[30]=1;
  //Used[31]=1;
  //Used[32]=1;
  //Used[33]=1;
  //Used[39]=1;
  //Used[41]=1;
  //Used[50]=1;
  //Used[62]=1;
  //Used[63]=1;
  // ----
  //Used[3]=1;
  //Used[6]=1;
  //Used[7]=1;
  //Used[9]=1;
  //Used[10]=1;
  //Used[17]=1;
  //Used[18]=1;
  //Used[20]=1;
  //Used[22]=1;
  //Used[24]=1;
  //Used[26]=1;
  //Used[34]=1;
  //Used[37]=1;
  //Used[38]=1;
  //Used[40]=1;
  //Used[51]=1;
  //Used[52]=1;
  //Used[58]=1;
  //Used[61]=1;
  // ----
  //Used[2]=1;
  //Used[8]=1;
  //Used[11]=1;
  //Used[12]=1;
  //Used[13]=1;
  //Used[14]=1;
  //Used[16]=1;
  //Used[19]=1;
  //Used[23]=1;
  //Used[35]=1;
  //Used[36]=1;
  //Used[53]=1;
  //Used[56]=1;
  //Used[57]=1;
  //Used[59]=1;
  //Used[60]=1;
  // ----
  //Used[1]=1;
  //Used[15]=1;
  //Used[54]=1;
  // ----
  //for(unsigned int i=1;i<=65;++i)  Used[i]=1;
  for(unsigned int i=1,n=0;i<N-1;++i)
    if(Used[i]==1)  UsedID[n++]=i;

  unsigned int NB=NC+N-1,SI;
  int MI;
  double ZT,VT,ZPT;
  double Step=2e-7;
  double TTH=2.;

  cout.precision(20);
  Array2DNumeric<double> MV,GT;
  MV.Imprint(S.Location());
  GT.Imprint(MV);

  BoxMuller<MersenneTwisterDSFMT<19937> > BG;
  MersenneTwisterDSFMT<19937> UG;
  BG.Allocate();
  UG.Allocate();
  BG.InitWithTime();
  UG.InitWithTime();

  ifs.open("GGGG");
  for(unsigned int i=1;i<N-1;++i)
  for(unsigned int k=0;k<3;++k)   ifs>>S.Location()[i][k];
  ifs.close();

  S.Velocity().Fill(0.);
  S.Velocity()[N-1][0]=1;

  GetHessian(S,Hess,N,NB);
  ZT=GetGT(S,Hess,GT,N,NB,Used,UsedID,NUsed);
  cout<<ZT<<endl; //getchar();

  do {
    MI=0;
    for(unsigned int i=0;i<NUsed;++i)
    for(unsigned int k=0;k<3;++k) {
      S.Location()[UsedID[i]][k]+=Step;
      GetHessian(S,Hess,N,NB);
      ZPT=GetGT(S,Hess,GT,N,NB,Used,UsedID,NUsed);
      if(ZPT<ZT)  { ZT=ZPT; ++MI; break; }
      else {
        S.Location()[UsedID[i]][k]-=Step*2;
        GetHessian(S,Hess,N,NB);
        ZPT=GetGT(S,Hess,GT,N,NB,Used,UsedID,NUsed);
        if(ZPT<ZT)  { ZT=ZPT; ++MI; break; }
        else {
          S.Location()[UsedID[i]][k]+=Step;
        }
      }
    }
    cout<<MI<<"\t"<<ZT<<"\t"<<Step<<endl;
    if(ZT<TTH) break;
    if(MI==0) { Step*=0.5; }
    if(Step<1e-10)  break;
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

