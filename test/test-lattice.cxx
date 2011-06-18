
#include "lattice/motif/allocate.h"
#include "lattice/motif/copy.h"
#include "lattice/motif/build.h"
#include "lattice/motif-chain/allocate.h"
#include "lattice/motif-chain/io.h"
#include "lattice/motif-chain/convert.h"
#include "lattice/enumerate/square-2d/run-data/allocate.h"
#include "lattice/enumerate/square-2d/run-data/copy.h"
#include "lattice/enumerate/square-2d/check/allocate.h"
#include "lattice/enumerate/square-2d/check/copy.h"
#include "lattice/enumerate/square-2d/process/output-chain/interface.h"
#include "lattice/enumerate/square-2d/act.h"
#include "io/console.h"
#include "io/output/file/copy.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  if(argc!=2) {
    cerr<<"test-lattice.run <Library-Root-Directory>"<<endl;
    return 1;
  }
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
  cout<<"Load Lattice-Library for 2d Square Lattice"<<endl;
  LatticeLibrary<SquareLattice,2>::load(argv[1]);
  cout<<"MaxBondOfMotif is:\t"<<LatticeLibrary<SquareLattice,2>::MaxBondOfMotif<<endl;
  cout<<"NumNeighbors is:\t"<<LatticeLibrary<SquareLattice,2>::NumNeighbors<<endl;
  cout<<"NumShifts is:\t"<<LatticeLibrary<SquareLattice,2>::NumShifts<<endl;
  cout<<"relLocation is:\t"<<LatticeLibrary<SquareLattice,2>::relLocation<<endl;
  cout<<"Size of shiftLoc is:\t";
  cout<<LatticeLibrary<SquareLattice,2>::shiftLoc.ListSize()<<endl;
  cout<<"Size of map is:\t";
  cout<<LatticeLibrary<SquareLattice,2>::map.ListSize()<<endl;

  cout<<endl;
  LatticeMotifChain<SquareLattice,2,5>  MC,MC1;
  cout<<"Before Allocation: the status of motifValue is:\t";
  cout<<IsValid(MC.motifValue)<<endl;
  allocate(MC);
  cout<<"After Allocation: the status of motifValue is:\t";
  cout<<IsValid(MC.motifValue)<<endl;
  imprint(MC1,MC);
  cout<<"After Imprint: the status of motifValue is:\t";
  cout<<IsValid(MC1.motifValue)<<endl;
  release(MC1);
  cout<<"After Release: the status of motifValue is:\t";
  cout<<IsValid(MC1.motifValue)<<endl;
  cout<<"Number of Motifs is:\t"<<MC.NumMotifs<<endl;
  cout<<"Number of Bonds  of Last Motif is:\t"<<MC.NumBondsLastMotif<<endl;
  MC.motifValue[0]=4;
  cout<<"4th Bond of 5th motif is:\t"<<MC.bondValue(3)<<endl;
  COut<<"4th Bond of 5th motif is:\t"<<MC.bondVec(3)<<Endl;

  cout<<endl;
  allocate(MC1);
  copy(MC1,MC);
  cout<<"After Copy:"<<endl;
  cout<<"4th Bond of 5th motif is:\t"<<MC1.bondValue(3)<<endl;
  COut<<"4th Bond of 5th motif is:\t"<<MC1.bondVec(3)<<Endl;

  cout<<endl;
  cout<<"Output MotifChain:"<<endl;
  COut<<"\t"<<MC<<Endl;
  CIn>>MC1;
  cout<<"Input MotifChain:"<<endl;
  COut<<"\t"<<MC1<<Endl;

  cout<<endl;
  Vector<unsigned char> bd(10);
  for(unsigned int i=0;i<10;i++)  bd[i]=0;
  bd[2]=bd[3]=bd[5]=bd[7]=1;
  convert(bd,MC);
  cout<<"Convert bond-chain to motif-chain:"<<endl;
  COut<<"\t"<<MC<<Endl;

  cout<<endl;
  LatticeEnumSquare2DRunData<12> RD,RD2;
  cout<<"Before Allocation: the status of Mesh is:\t";
  cout<<IsValid(RD.Mesh)<<endl;
  allocate(RD);
  cout<<"After Allocation: the status of Mesh is:\t";
  cout<<IsValid(RD.Mesh)<<endl;
  imprint(RD2,RD);
  cout<<"After Imprint: the status of Mesh is:\t";
  cout<<IsValid(RD2.Mesh)<<endl;
  release(RD2);
  cout<<"After Release: the status of Mesh is:\t";
  cout<<IsValid(RD2.Mesh)<<endl;

  cout<<endl;
  allocate(RD2);
  RD.Bc=9;
  copy(RD2,RD);
  cout<<"Copy from another RunData: Bc is:\t";
  cout<<"\t"<<RD2.Bc<<endl;

  cout<<endl;
  LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic> EM,EM1;
  cout<<"Before Allocation: status of this object is:\t";
  cout<<IsValid(EM)<<endl;
  allocate(EM);
  cout<<"After Allocation: status of this object is:\t";
  cout<<IsValid(EM)<<endl;
  imprint(EM1,EM);
  cout<<"After Imprint: status of this object is:\t";
  cout<<IsValid(EM1)<<endl;
  release(EM1);
  cout<<"After Release: status of this object is:\t";
  cout<<IsValid(EM1)<<endl;

  cout<<endl;
  allocate(EM1);
  copy(EM1,EM);
  cout<<"Copy operation for Basic Check do nothing"<<endl;

  cout<<endl;
  LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds> EMF,EMF1;
  cout<<"Before Allocation: status of fixedBond is:\t";
  cout<<IsValid(EMF.fixedBond)<<endl;
  allocate(EMF,5);
  cout<<"After Allocation: status of fixedBond is:\t";
  cout<<IsValid(EMF.fixedBond)<<endl;
  imprint(EMF1,EMF);
  cout<<"After Imprint: status of fixedBond is:\t";
  cout<<IsValid(EMF1.fixedBond)<<endl;
  release(EMF1);
  cout<<"After Release: status of fixedBond is:\t";
  cout<<IsValid(EMF1.fixedBond)<<endl;
  EMF.fixedBond[0][0]=0;    EMF.fixedBond[0][1]=0;
  EMF.fixedBond[1][0]=5;    EMF.fixedBond[1][1]=2;
  EMF.fixedBond[2][0]=6;    EMF.fixedBond[2][1]=0;
  EMF.fixedBond[3][0]=7;    EMF.fixedBond[3][1]=0;
  EMF.fixedBond[4][0]=8;    EMF.fixedBond[4][1]=1;
  EMF.update<12>();
  cout<<"After update, the size of flag is:\t";
  cout<<EMF.flag.ListSize()<<endl;

  cout<<endl;
  imprint(EMF1,EMF);
  EMF1.update<12>();
  copy(EMF1,EMF);
  cout<<"Copy from another Run-Data: Flag is:\t";
  cout<<EMF1.flag[0][0]<<endl;

  cout<<endl;
  cout<<EMF.Act(RD)<<endl;

  LatticeEnumSquare2DProcessOutputChain<12,FileOutput> OP;
  copy(OP.os,COut);
  cout<<endl;
  cout<<enumerate<12>(EM,OP)<<endl;
  cout<<enumerate<12>(EMF,OP)<<endl;

  return 0;
}

