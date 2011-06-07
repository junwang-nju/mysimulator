
#include "list/allocate.h"
#include "list/copy.h"
#include "list/io.h"
#include "list/fill.h"
#include "list/swap.h"
#include "io/console.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  List<int> LI;
  List<double> LD;
  Vector<unsigned int> sz;
  allocate(sz,5);
  for(unsigned int i=0;i<sz.size;i++) sz[i]=i+5;
  cout<<"Before Allocation:\t"<<IsValid(LI.infra)<<endl;
  allocate(LI,sz);
  cout<<"After Allocation:\t"<<IsValid(LI.infra)<<endl;
  allocate(LD,sz.pdata,4);
  cout<<"After Allocation with array:\t"<<IsValid(LI.infra)<<endl;
  List<int> LI2;
  imprint(LI2,LI);
  cout<<"List After Imprint operation has the size:";
  cout<<"\t"<<LI2.ListSize()<<"\t"<<LI2.NumElements()<<endl;
  release(LI2);
  cout<<"List after release:\t"<<IsValid(LI2.infra)<<endl;
  cout<<"State of List After Allocation:\t"<<IsValid(LD)<<endl;
  cout<<"State of List After Release:\t"<<IsValid(LI2)<<endl;

  cout<<endl;
  LI[2][4]=8;
  cout<<"Assign a certain element through [] operator:"<<endl;
  COut<<"\t"<<LI[2]<<Endl;
  for(unsigned int i=0;i<LI.ListSize();++i)
  for(unsigned int j=0;j<LI[i].size;j++)  LI[i][j]=i+j+3;
  cout<<"Output the whole List:"<<endl;
  COut<<LI<<Endl;
  allocate(LI2,sz.pdata+1,4);
  copy(LI2,LI);
  cout<<"List After Copy:"<<endl;
  COut<<LI2<<Endl;
  imprint(LI2,LI);
  ecopy(LI2,LI);
  cout<<"List After Efficient Copy:"<<endl;
  COut<<LI2<<Endl;

  cout<<endl;
  cout<<"Compare Two different Lists:\t"<<IsSameStructure(LI,LD)<<endl;
  cout<<"Compare Two Lists with same structure:\t"<<IsSameStructure(LI,LI2)<<endl;

  cout<<endl;
  fill(LD,5.5);
  cout<<"List filled with constant:"<<endl;
  COut<<LD<<Endl;

  cout<<endl;
  allocate(LI2,sz.pdata+1,2);
  fill(LI2,3);
  swap(LI,LI2);
  cout<<"Lists After Swap:"<<endl;
  cout<<"List 1:"<<endl;
  COut<<LI<<Endl;
  cout<<"List 2:"<<endl;
  COut<<LI2<<Endl;
  return 0;
}

