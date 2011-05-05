
#include "buffer/distance/pair/copy.h"
#include "buffer/distance/pair/allocate.h"

#include "buffer/distance/simple/copy.h"
#include "buffer/distance/simple/allocate.h"

#include "geometry/distance/calc.h"
#include "geometry/displacement/base/calc.h"

#include "matrix/storage/copy.h"
#include "matrix/storage/allocate.h"

#include "io/output/string/interface.h"
#include "io/input/string/interface.h"

#include "random/mt-standard/io.h"
#include "random/mt-standard/allocate.h"
#include "random/mt-dsfmt/io.h"

#include "vector/allocate.h"

#include "btree/interface.h"
#include "btree/copy.h"

#include "chain/allocate.h"
#include "chain/copy.h"

#include "unique-parameter/64bit/io.h"
#include "unique-parameter/128bit/io.h"

using namespace mysimulator;

int main() {
  Chain<int> C;
  allocate(C);
  COut<<"===============1============"<<Endl;
  int I=1;
  C.append(I,Referred);
  COut<<C.IsContained(1)<<Endl;
  COut<<"===============2============"<<Endl;
  C.append(45);
  COut<<C.IsContained(1)<<Endl;
  COut<<"===============3============"<<Endl;
  ChainNode<int> *pN;
  pN=C.root.child().child.pdata;
  COut<<(*pN).content()<<Endl;
  C.append(*pN);
  COut<<C.root.child().content()<<Endl;
  COut<<C.root.child().child().content()<<Endl;
  COut<<C.root.child().child().child().content()<<Endl;
  COut<<"===============5============"<<Endl;
  C.remove(1);
  COut<<C.IsContained(1)<<Endl;
  COut<<"===============5============"<<Endl;
  Chain<int> C1;
  copy(C1,C);
  COut<<C1.root.child().content()<<Endl;
  COut<<C1.root.child().child().content()<<Endl;
  release(C);
  COut<<"===============4============"<<Endl;

  BTree<int,double> bt;
  bt.insert(5,6.5);
  bt.insert(3,3.5);
  bt.insert(1,1.5);
  bt.insert(4,4.5);
  bt.insert(9,9.5);

  COut<<bt.root().key()<<"\t"<<bt.root().value()<<Endl;
  COut<<bt.root().left().key()<<"\t"<<bt.root().left().value()<<Endl;
  COut<<bt.root().left().left().key()<<"\t"<<bt.root().left().left().value()<<Endl;
  COut<<bt.root().right().key()<<"\t"<<bt.root().right().value()<<Endl;

  COut<<*(bt.getValue(1))<<Endl;
  COut<<bt.getValue(8)<<Endl;

  COut<<"================"<<Endl;
  bt.remove(3);
  COut<<bt.root().key()<<"\t"<<bt.root().value()<<Endl;
  COut<<"========1======="<<Endl;
  COut<<bt.root().left().key()<<"\t"<<bt.root().left().value()<<Endl;
  COut<<"========2======="<<Endl;
  COut<<bt.root().left().left().key()<<"\t"<<bt.root().left().left().value()<<Endl;
  COut<<"========3======="<<Endl;
  COut<<bt.root().right().key()<<"\t"<<bt.root().right().value()<<Endl;
  COut<<"========4======="<<Endl;

  release(bt);
  COut<<"================"<<Endl;

  Vector<double> v;

  MT_Standard MS;
  allocate(MS);
  MS.init(122378);
  Vector<unsigned int> iv;
  allocate(iv,100);
  for(unsigned int i=0;i<100;++i) iv[i]=(1+i)*(2+i);
  MS.init(iv);

  COut.precision(20);
  COut<<MS.rand<unsigned int>()<<Endl;
  COut<<MS.rand<double>()<<Endl;
  COut<<MS.rand<int>()<<Endl;
  COut<<MS.doubleClose0Close1()<<Endl;
  COut<<MS.doubleClose0Open1()<<Endl;
  COut<<MS.doubleOpen0Open1()<<Endl;

  allocate(iv,1000);
  MS.fill(iv);

  const unsigned int nbuff=4096000;
  char buff[nbuff];
  StringOutput SO(buff,nbuff);
  StringInput SI(buff,nbuff);
  Vector<unsigned int> vb,ve;
  unsigned int ncmp=10;
  allocate(vb,ncmp);
  allocate(ve,ncmp);
  SO<<MS;
  MS.fill(vb);
  SI>>MS;
  MS.fill(ve);
  for(unsigned int i=0;i<ncmp;++i)
    if(vb[i]!=ve[i]) COut<<i<<"\tNot Equal"<<Endl;
  COut<<Endl;

  SimpleDistanceBuffer<double> SDB;

  return 0;
}

