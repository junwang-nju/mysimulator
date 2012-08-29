
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

extern "C" {
  void dgesv_(int*,int*,double*,int*,int*,double*,int*,int*);
}

void GetG(double* X, double* G, double* K, double* D,int* bID, int* eID,
          int NB, int N, int TN) {
  for(int i=0;i<TN;++i) G[i]=0;
  double TM;
  double V[3];
  for(int i=0;i<NB;++i) {
    for(int k=0;k<3;++k) V[k]=X[bID[i]*3+k]-X[eID[i]*3+k];
    TM=1.-D[i]/sqrt(V[0]*V[0]+V[1]*V[1]+V[2]*V[2]);
    TM*=2*K[i];
    for(int k=0;k<3;++k) {
      V[k]*=TM;
      G[bID[i]*3+k]+=V[k];
      G[eID[i]*3+k]-=V[k];
    }
  }
}

void GetHessian(double* X,double* Hess,double* K,double* D,int* bID,int* eID,
                int NB,int N,int TN) {
  for(int i=0;i<TN;++i)
  for(int j=0;j<TN;++j) Hess[i*TN+j]=0;
  double TM,TM1,TM2;
  int I,J;
  double V[3];
  for(int i=0;i<NB;++i) {
    TM1=2*K[i];
    TM2=TM1*D[i];
    for(int k=0;k<3;++k)  V[k]=X[bID[i]*3+k]-X[eID[i]*3+k];
    TM=1./sqrt(V[0]*V[0]+V[1]*V[1]+V[2]*V[2]);
    for(int k=0;k<3;++k)  V[k]*=TM;
    TM2*=TM;
    TM1-=TM2;
    I=bID[i]*3;
    J=eID[i]*3;
    for(int k=0;k<3;++k)
    for(int l=0;l<3;++l) {
      TM=TM2*V[k]*V[l];
      if(k==l)  TM+=TM1;
      Hess[(I+k)*TN+(I+l)]+=TM;
      Hess[(I+k)*TN+(J+l)]-=TM;
      Hess[(J+k)*TN+(I+l)]-=TM;
      Hess[(J+k)*TN+(J+l)]+=TM;
    }
  }
}

double GetDV(double* X,double* Hess,double *G,
             double* K,double *D,int* bID,int* eID,
             double* V,double* A,double* B,int *IP,
             int NB,int N,int TN,int NS,int NH,
             double iGamma,int& Inf) {
  double T;
  GetHessian(X,Hess,K,D,bID,eID,NB,N,TN);
  for(int k=0;k<NS;++k)
  for(int l=0;l<NS;++l) A[k*NS+l]=Hess[(3+k)*TN+3+l];
  for(int k=0;k<NS;++k) {
    T=0;
    for(int i=0;i<3;++i) T+=Hess[(3+k+1)*TN-3+i]*V[TN-3+i];
    B[k]=-T;
  }
  dgesv_(&NS,&NH,A,&NS,IP,B,&NS,&Inf);

  GetG(X,G,K,D,bID,eID,NB,N,TN);
  for(int k=0;k<NS;++k)  V[3+k]=-iGamma*G[3+k];
  for(int k=0;k<NS;++k)  B[k]=V[3+k]-B[k];
  T=0;
  for(int k=0;k<NS;++k)  T+=B[k]*B[k];
  T=sqrt(T);
  if(T>10) {
    for(int i=0;i<4;++i) {
      for(int k=0;k<3;++k) cout<<"\t"<<B[i*3+k]; cout<<endl;
    }
    cout<<endl;
    for(int i=0;i<4;++i) {
      for(int k=0;k<3;++k) cout<<"\t"<<V[3+3*i+k]-B[i*3+k]; cout<<endl;
    }
    cout<<Inf<<endl;
    getchar();
  }
  //for(int k=0;k<NS;++k)  B[k]/=T;
  return T;
}

int main() {
  double * Hess;
  double * A, * B, * RB;
  double * X, * XP, * V, *G, *GT;
  double * K, * D;
  int    * bID, * eID, * IP;

  int N=6;
  int TN=N*3;
  int NB=8;
  int NS=12;
  int NH=1;

  X=new double[TN];
  XP=new double[TN];
  V=new double[TN];
  G=new double[TN];
  GT=new double[TN];

  K=new double[NB];
  D=new double[NB];
  bID=new int[NB];
  eID=new int[NB];

  Hess=new double[TN*TN];

  bID[0]=0; eID[0]=1;   D[0]=1;   K[0]=20;
  bID[1]=1; eID[1]=2;   D[1]=1;   K[1]=100;
  bID[2]=1; eID[2]=3;   D[2]=1;   K[2]=20;
  bID[3]=1; eID[3]=4;   D[3]=1;   K[3]=20;
  bID[4]=2; eID[4]=3;   D[4]=1;   K[4]=100;
  bID[5]=2; eID[5]=4;   D[5]=1;   K[5]=20;
  bID[6]=3; eID[6]=4;   D[6]=1;   K[6]=100;
  bID[7]=4; eID[7]=5;   D[7]=1;   K[7]=20;

  for(int i=0;i<TN;++i) V[i]=0;
  V[15]=0.1;

  double T;
  T=sqrt(0.5);
  X[0]=0;       X[1]=0;         X[2]=0;
  X[3]=1;       X[4]=0;         X[5]=0;
  X[6]=1.5;     X[7]=0.5;       X[8]=T;
  X[9]=1.5;     X[10]=-0.5;     X[11]=T;
  X[12]=2;      X[13]=0;        X[14]=0;
  X[15]=3;      X[16]=0;        X[17]=0;

  double Gamma=10;
  double iGamma=1./Gamma;

  A=new double[NS*NS];
  B=new double[NS];
  RB=new double[NS];
  IP=new int[NS];
  int Inf;
  double Step,PT;

  T=GetDV(X,Hess,G,K,D,bID,eID,V,A,B,IP,NB,N,TN,NS,NH,iGamma,Inf);
  for(int k=0;k<NS;++k)  RB[k]=B[k];
  cout<<T<<endl;
  Step=1e-5;
  while(true) {
    //for(int k=0;k<NS;++k)  XP[3+k]=X[3+k]+RB[k]*Step*0.5;
    //PT=GetDV(XP,Hess,G,K,D,bID,eID,V,A,B,IP,NB,N,TN,NS,NH,iGamma,Inf);
    //for(int k=0;k<NS;++k)  RB[k]=B[k];
    for(int k=0;k<NS;++k)  X[3+k]+=RB[k]*Step;
    PT=GetDV(X,Hess,G,K,D,bID,eID,V,A,B,IP,NB,N,TN,NS,NH,iGamma,Inf);
    /*
    if(PT<T) {
      T=PT; for(int k=0;k<NS;++k) RB[k]=B[k]; Step=0.01; //cout<<T<<endl;
    } else { for(int k=0;k<NS;++k) X[3+k]-=RB[k]*Step;  Step*=0.5; }
    */
    T=PT; for(int k=0;k<NS;++k) RB[k]=B[k];
    cout<<T<<endl;
    if(T<1e-3)  break;
  }
  cout<<endl;
  cout<<X[3]<<"\t"<<X[4]<<"\t"<<X[5]<<endl;
  cout<<X[6]<<"\t"<<X[7]<<"\t"<<X[8]<<endl;
  cout<<X[9]<<"\t"<<X[10]<<"\t"<<X[11]<<endl;
  cout<<X[12]<<"\t"<<X[13]<<"\t"<<X[14]<<endl;
  GetHessian(X,Hess,K,D,bID,eID,NB,N,TN);
  GetG(X,G,K,D,bID,eID,NB,N,TN);
  for(int k=0;k<NS;++k) V[3+k]=-iGamma*G[3+k];
  T=0;
  for(int i=0;i<NS;++i) {
    T=0;
    for(int k=0;k<TN-3;++k) T+=Hess[(3+i)*TN+3+k]*V[3+k];
    GT[3+i]=T;
  }
  T=0;
  for(int k=0;k<NS;++k) T+=GT[3+k]*GT[3+k];
  cout<<sqrt(T)<<endl;

  return 0;
}

