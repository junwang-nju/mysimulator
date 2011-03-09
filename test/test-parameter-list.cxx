
//#include "operation/derived/parameter-list-io.h"
#include "operation/basic/map-op.h"
#include "operation/basic/build-hash.h"
#include "data/basic/unique-parameter.h"
#include "data/basic/console-output.h"
#include "data/basic/console-input.h"
using namespace std;

int main() {
  COut<<"Test -- initiate"<<Endl;
  //ParameterList PL;
  Map<Vector<unsigned int>,Vector<UniqueParameter> > M;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(M);
  /*
  allocate(PL,3,2,7);
  Vector<unsigned int> ksize, vsize;
  allocate(ksize,9);
  allocate(vsize,8);
  copy(ksize,3);
  copy(vsize,2);
  allocate(PL,ksize.data,vsize.data,8);
  allocate(PL,ksize.data,5,6);
  allocate(PL,4,vsize.data,5);
  release(ksize);
  release(vsize);
  */
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

  /*
  COut<<"Test -- input from istream"<<Endl;
  CIn>>PL;
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(PL[i])) COut<<i<<Endl;
  COut<<Endl;

  COut<<"Test -- assign from another parameter list"<<Endl;
  ParameterList PL2;
  allocate(PL2,5,3,4);
  copy(PL2,PL);
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(PL2[i])) COut<<i<<Endl;
  COut<<Endl;

  COut<<"Test -- refer operation"<<Endl;
  refer(PL2,PL);
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(PL2[i])) COut<<i<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(PL2);
  COut<<Endl;

  COut<<"Test -- availability check"<<Endl;
  COut<<IsAvailable(PL)<<Endl;
  release(PL);
  COut<<IsAvailable(PL)<<Endl;
  COut<<Endl;
  */

  return 1;
}

