
#include "operation/derived/parameter-key-io.h"
#include "data/basic/console-output.h"
#include "data/basic/console-input.h"
using namespace std;

int main() {
  COut<<"Test -- create a key"<<Endl;
  ParameterKey K;
  COut<<Endl;

  COut<<"Test -- allocate a key"<<Endl;
  allocate(K,3);
  COut<<Endl;

  COut<<"Test -- build hash"<<Endl;
  K[0]=1;
  K[1]=100;
  K[2]=0;
  K.update();
  COut<<K.hash[0]<<"\t"<<K.hash[1]<<"\t"<<K.hash[2]<<Endl;
  COut<<Endl;

  COut<<"Test -- assign"<<Endl;
  ParameterKey K2;
  allocate(K2,4);
  copy(K2,K);
  COut<<K2<<Endl;
  //for(unsigned int i=0;i<K2.size;++i) COut<<K2[i]<<"  "; COut<<Endl;
  COut<<K2.hash[0]<<"\t"<<K2.hash[1]<<"\t"<<K2.hash[2]<<Endl;
  COut<<Endl;

  COut<<"Test -- input from stream"<<Endl;
  COut<<K.hsize<<Endl;
  CIn>>K;
  COut<<K<<Endl;
  //for(unsigned int i=0;i<K.size;++i) COut<<K.index[i]<<"  "; COut<<Endl;
  COut<<K.hash[0]<<"\t"<<K.hash[1]<<"\t"<<K.hash[2]<<Endl;
  COut<<Endl;

  COut<<"Test -- compare"<<Endl;
  COut<<compare(K,K2)<<Endl;
  COut<<compare(K2,K)<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(K2);
  COut<<Endl;

  COut<<"Test - availability check"<<Endl;
  COut<<IsAvailable(K)<<Endl;
  release(K);
  COut<<IsAvailable(K)<<Endl;
  COut<<Endl;

  return 1;
}

