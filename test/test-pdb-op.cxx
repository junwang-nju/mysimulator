
#include "pdb-op.h"
#include "var-property-list.h"
#include <iostream>
using namespace std;

int main() {
  varPropertyList<double>::Type vPL;
  pdb2coordinate("2ci2",vPL,PDBFile,CAlphaType);
  for(unsigned int i=0;i<vPL.size();++i)    cout<<vPL[i]<<endl;
  return 1;
}

