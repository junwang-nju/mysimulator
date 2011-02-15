
#include "data/basic/simple-data-input.h"
#include "data/basic/console-output.h"
using namespace std;

int main() {
  SimpleDataInput<double> SI;
  Vector<double> vD(10);
  for(unsigned int i=0;i<vD.size;++i) vD[i]=934.32-i;
  refer(SI,vD);
  double a=-1271.;
  int g=23123;
  char str[10]="asafd";
  COut<<a<<Endl;
  COut<<g<<Endl;
  COut<<str<<Endl;
  SI>>a>>g>>str;
  COut<<a<<Endl;
  COut<<g<<Endl;
  COut<<str<<Endl;
  return 0;
}

