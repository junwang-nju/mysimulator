
#include "pdb-data-structure-op.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  assert(argc>=2);
  PDBDataStructure pdb;
  ImportPDB("2ci2",PDBFile,pdb,argv[1]);
  for(unsigned int i=0;i<pdb.Model[0].size();++i) {
    cout<<pdb.Model[0][i].Name<<"\t"<<pdb.Model[0][i].Data[0].AtomName<<"\t";
    cout<<pdb.Model[0][i].Data[0].AtomCoordinate<<"\t";
    cout<<pdb.Model[0][i].Data.size()<<"\t";
    cout<<pdb.Model[0][i].Data[0].TempFactor<<endl;
  }
  return 1;
}

