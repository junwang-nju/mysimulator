
#include "pdb-data-structure-op.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  assert(argc>=2);

  cout<<"Test -- declare a pdb data structure"<<endl;
  PDBDataStructure pdb;
  cout<<endl;

  cout<<"Test -- import with a pdb code"<<endl;
  ImportPDB("2ci2",PDBFile,pdb,argv[1]);
  for(unsigned int i=0;i<pdb.Model[0].size();++i) {
    cout<<pdb.Model[0][i].Name<<"\t"<<pdb.Model[0][i].Data[0].AtomName<<"\t";
    cout<<pdb.Model[0][i].Data[0].AtomCoordinate<<"\t";
    cout<<pdb.Model[0][i].Data.size()<<"\t";
    cout<<pdb.Model[0][i].Data[0].TempFactor<<endl;
  }
  cout<<endl;

  cout<<"Test -- calculate contact based on C-Alpha atoms"<<endl;
  varMatrixTriangle<unsigned int>::Type cm;
  CalcContactMap(pdb,cm,CAlphaType);
  for(unsigned int i=0;i<cm.Dimension();++i)
  for(unsigned int j=i+4;j<cm.Dimension();++j)
    if(cm(i,j)>0) cout<<i<<"\t"<<j<<endl;
  cout<<endl;

  cout<<"Test -- calculate contact based on heavy atoms"<<endl;
  CalcContactMap(pdb,cm,HeavyAtomType);
  for(unsigned int i=0;i<cm.Dimension();++i)
  for(unsigned int j=i+4;j<cm.Dimension();++j)
    if(cm(i,j)>0) cout<<i<<"\t"<<j<<endl;
  cout<<endl;
  return 1;
}

