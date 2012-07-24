
#include "system/interface.h"
#include "pdb-file/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  PDBFile PF;
  PDBObject PO;
  PF.Load("2CI2");
  PF.Produce(PO);

  Array2DNumeric<double> X;
  PO.ProduceCAlpha<UseFirstModel>(X);

  return 0;
}
