
#include "operation/basic/lapack.h"
#include "operation/basic/vector-io.h"
#include "data/basic/console-output.h"
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
  COut<<info<<Endl;
  COut<<vA<<Endl;
  COut<<tau<<Endl;
  double B[9]={1,2,3,2,4,2,3,2,9};
  char J='V',P='U';
  int iwork[100];
  refer(vA,B,9);
  COut<<vA<<Endl;
  dsyevd_(&J,&P,&N,B,&LDA,tau,work,&LWork,iwork,&LWork,&info);
  COut<<info<<Endl;
  COut<<vA<<Endl;
  refer(vA,tau,3);
  COut<<vA<<Endl;
  return 0;
}

