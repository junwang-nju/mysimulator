
#include <iostream>
#include <cmath>
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

int main() {
  double * Hess;
  double * A;
  double * X, * V, *G;
  double * K, * D;
  int    * bID, *eID;

  int N=6;
  int TN=N*3;
  int NB=8;

  X=new double[TN];
  V=new double[TN];
  G=new double[TN];

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

  double T;
  T=sqrt(0.5);
  X[0]=0;       X[1]=0;         X[2]=0;
  X[3]=1;       X[4]=0;         X[5]=0;
  X[6]=1.5;     X[7]=0.5;       X[8]=T;
  X[9]=1.5;     X[10]=-0.5;     X[11]=T;
  X[12]=2;      X[13]=0;        X[14]=0;
  X[15]=3;      X[16]=1;        X[17]=0;

  GetG(X,G,K,D,bID,eID,NB,N,TN);

  GetHessian(X,Hess,K,D,bID,eID,NB,N,TN);

  for(int k=0;k<3;++k) {
    for(int l=0;l<3;++l)  cout<<"\t"<<Hess[(15+k)*TN+15+l]; cout<<endl;
  }

  return 0;
}

