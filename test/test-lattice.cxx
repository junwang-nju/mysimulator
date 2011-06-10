
#include "lattice/motif/allocate.h"
#include "lattice/motif/copy.h"
#include "lattice/motif/build.h"
#include "lattice/motif-chain/allocate.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  cout<<endl;
  LatticeMotif M,M1;
  cout<<"Before Allocation: the size of bonds is:\t";
  cout<<M.bond.size<<endl;
  allocate(M,5,2);
  cout<<"After Allocation: the size of bonds is:\t";
  cout<<M.bond.size<<endl;
  imprint(M1,M);
  cout<<"After Imprint: the size of bonds is:\t";
  cout<<M1.bond.size<<endl;
  release(M1);
  cout<<"After Release: the size of bonds is:\t";
  cout<<M1.bond.size<<endl;
  cout<<"Dimension is:\t"<<M.Dimension()<<endl;

  cout<<endl;
  imprint(M1,M);
  for(unsigned int i=0;i<M.bond.size;i++) {
    M.bond[i]=0;
    M.coordinate[i][0]=M.coordinate[i][1]=i+3;
  }
  copy(M1,M);
  cout<<"The copy Motif is"<<endl;
  for(unsigned int i=0;i<M.bond.size;i++)
    cout<<"\t"<<M.bond[i]<<"\t"<<M.coordinate[i][0]<<"\t"<<M.coordinate[i][1]<<endl;

  cout<<endl;
  build<SquareLattice,2>(M);
  cout<<"The buit Motif is"<<endl;
  for(unsigned int i=0;i<M.bond.size;i++)
    cout<<"\t"<<M.bond[i]<<"\t"<<M.coordinate[i][0]<<"\t"<<M.coordinate[i][1]<<endl;

  cout<<endl;
  LatticeMotifChain<SquareLattice,2,5>  MC,MC1;
  allocate(MC);
  imprint(MC1,MC);

  return 0;
}

