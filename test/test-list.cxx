
#include "list/allocate.h"
#include "list/copy.h"
#include "list/io.h"
#include "list/fill.h"
#include "list/swap.h"
#include "list/scale.h"
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

  cout<<endl;
  List<double> LA,LB,LC;
  allocate(sz,3);
  sz[0]=4;    sz[1]=5;    sz[2]=6;
  allocate(LA,sz);
  sz[0]=2;    sz[1]=4;    sz[2]=6;
  allocate(LB,sz);
  sz[0]=5;    sz[1]=3;    sz[2]=2;
  allocate(LC,sz);
  fill(LA,1.2);
  fill(LB,2.5);
  fill(LC,-5.8);
  scale(LA,8);
  cout<<"Scale with a constant:"<<endl;
  COut<<LA<<Endl;
  Vector<float> vf(3);
  vf[0]=1.5;    vf[1]=2.5;    vf[2]=4.5;
  scale(LA,vf);
  cout<<"Scale with a vector:"<<Endl;
  COut<<LA<<Endl;
  scale(LA,LB,0.8);
  cout<<"Scale with constant and List:"<<endl;
  COut<<LA<<Endl;
  scale(LA,LC,vf);
  cout<<"Scale with list and vector:"<<endl;
  COut<<LA<<Endl;
  scale(LA,LB,LC);
  cout<<"Scale with list and list:"<<endl;
  COut<<LA<<Endl;
  return 0;
}

