
//#include "operation/derived/parameter-list-io.h"
#include "operation/basic/map-op.h"
#include "operation/basic/build-hash.h"
#include "data/basic/unique-parameter.h"
#include "data/basic/console-output.h"
#include "data/basic/console-input.h"
#include "operation/basic/vector-io.h"
#include "operation/basic/unique-parameter-io.h"
using namespace std;

int main() {
  COut<<"Test -- initiate"<<Endl;
  //ParameterList PL;
  Map<Vector<unsigned int>,Vector<UniqueParameter> > M;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(M);
  COut<<Endl;


  COut<<"Test -- input data by direct access"<<Endl;
  Vector<unsigned int> key(4);
  Vector<UniqueParameter> value(2);
  for(unsigned int i=0;i<5;++i) {
    key[0]=0;
    key[1]=i;
    key[2]=i+1;
    key[3]=i+1;
    value[0].d=123.45*i+34.789;
    value[1].u=12345+i*87;
    add(M,key,value,Allocated,Allocated);
  }
  COut<<Endl;

  COut<<"Test -- access tree through []"<<Endl;
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(M[i])) COut<<i<<Endl;
  COut<<Endl;

  COut<<"Test -- get value"<<Endl;
  Vector<unsigned int> idx;
  allocate(idx,4);
  idx[0]=0;
  idx[1]=1;
  idx[2]=2;
  idx[3]=2;
  const Vector<UniqueParameter> *pVU=get(M,idx);
  COut<<(*pVU)[0].d<<Endl;
  COut<<(*pVU)[1].u<<Endl;
  release(idx);
  COut<<Endl;

  COut<<"Test -- input from istream"<<Endl;
  allocate(M);
  unsigned int n;
  CIn>>n;
  for(unsigned int i=0;i<n;++i) {
    CIn>>key>>value;
    add(M,key,value,Allocated,Allocated);
  }
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(M[i])) COut<<i<<Endl;
  COut<<Endl;

  COut<<"Test -- assign from another parameter list"<<Endl;
  Map<Vector<unsigned int>,Vector<UniqueParameter> > M2;
  allocate(M2);
  copy(M2,M);
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(M2[i])) COut<<i<<Endl;
  COut<<Endl;

  COut<<"Test -- refer operation"<<Endl;
  Map<Vector<unsigned int>,Vector<UniqueParameter> > M3;
  refer(M3,M);
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(M3[i])) COut<<i<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(M3);
  release(M2);
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(M[i])) COut<<i<<Endl;
  COut<<Endl;

  COut<<"Test -- availability check"<<Endl;
  COut<<IsAvailable(M)<<Endl;
  release(M);
  COut<<IsAvailable(M)<<Endl;
  COut<<Endl;

  return 1;
}

