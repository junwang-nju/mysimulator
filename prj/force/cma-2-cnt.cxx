
#include "io/error.h"
#include <cstring>
using namespace mysimulator;

int main(int argc, char** argv) {
  if(argc<2)  Error("cma-2-cnt <cma file>");
  FileInput FI;
  char buff[1024];
  buff[1023]=CharEOF;
  FI.open(argv[1]);
  FI.getline(buff);
  FI.getline(buff);
  char ResA[256], ResB[256];
  int idA,idB;
  while(1) {
    FI>>ResA>>ResA;
    FI>>ResB>>ResB>>buff;
    if(IsFailed(FI))  break;
    ResA[strlen(ResA)-1]='\0';
    ResB[strlen(ResB)-1]='\0';
    idA=atoi(ResA);
    idB=atoi(ResB);
    if(idB>idA+3) COut<<idA<<"\t"<<idB<<Endl;
  }
  FI.close();
  return 0;
}

