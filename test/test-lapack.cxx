
#include "operation/basic/lapack.h"
#include "data/basic/vector.h"
#include <iostream>
using namespace std;

int main() {
  double A[20]={12,6,-4,-51,167,24,4,-68,-41};
  Vector<double> vA;
  refer(vA,A,20);
  int M=3;
  int N=3;
  int LDA=3;
  double tau[5];
  double work[100];
  int LWork=100;
  int info=0;
  dgeqrf_(&M,&N,A,&LDA,tau,work,&LWork,&info);
  cout<<info<<endl;
  cout<<vA<<endl;
  cout<<tau<<endl;
  double B[9]={1,2,3,2,4,2,3,2,9};
  char J='V',P='U';
  int iwork[100];
  refer(vA,B,9);
  cout<<vA<<endl;
  dsyevd_(&J,&P,&N,B,&LDA,tau,work,&LWork,iwork,&LWork,&info);
  cout<<info<<endl;
  cout<<vA<<endl;
  refer(vA,tau,3);
  cout<<vA<<endl;
  return 0;
}

