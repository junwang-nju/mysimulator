
#include "data/basic/simple-data-output.h"
#include "operation/basic/vector-io.h"
#include "data/basic/console-output.h"
using namespace std;

int main() {
  SimpleDataOutput<double> DO;
  allocate(DO,10);
  DO<<2.34<<"\t"<<3.45<<"   "<<-1223.23<<"\t"<<2345<<Endl;
  COut<<DO.buffer<<Endl;
  return 0;
}

