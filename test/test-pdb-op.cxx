
#include "pdb-op.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  assert(argc>=2);
  PDBDataStructure pdb;
  ImportPDB("2ci2",PDBFile,pdb,argv[1]);
  for(unsigned int i=0;i<pdb.seq.size();++i)
    cout<<pdb.seq[i]<<" "<<endl;
  return 1;
}

