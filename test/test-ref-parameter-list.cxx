
#include "ref-parameter-list.h"
#include "var-parameter-list.h"
#include <iostream>
using namespace std;

int main() {
  refParameterList rPL;
  varParameterList vPL;
  varVector<unsigned int> kS(5),vS(5);
  kS=3;
  vS=2;
  vPL.allocate(kS,vS);
  cin>>vPL;

  cout<<"Test -- refer to variable parameter list"<<endl;
  rPL.refer(vPL);
  cout<<endl;

  cout<<"Test -- refer to reference parameter list"<<endl;
  refParameterList rPL2;
  rPL2.refer(rPL);
  cout<<endl;

  cout<<"Test -- assign from another reference parameter list"<<endl;
  varParameterList vPL2;
  vPL2.allocate(kS,vS);
  rPL2.refer(vPL2);
  rPL2=rPL;
  cout<<endl;

  cout<<"Test -- access contents through keylist() and valuelist()"<<endl;
  for(unsigned int i=0;i<5;++i) {
    rPL.keylist()[i].index()[0]=i+1;
    rPL.keylist()[i].index()[1]=i+2;
    rPL.keylist()[i].index()[2]=i+3;
    rPL.keylist()[i].BuildHash();
    rPL.valuelist()[i][0]=i*2.5;
    rPL.valuelist()[i][1]=i*3.5+0.5;
  }
  cout<<endl;
  
  cout<<"Test -- update hash tree"<<endl;
  rPL.updateHashTree();
  cout<<endl;

  cout<<"Test -- get value through index"<<endl;
  varVector<unsigned int> idx(3);
  idx[0]=1;
  idx[1]=2;
  idx[2]=3;
  varParameterValue* pvPV=const_cast<varParameterValue*>(rPL.get(idx));
  if(pvPV!=NULL)    cout<<(*pvPV)<<endl;
  cout<<endl;

  cout<<"Test -- access the hash tree"<<endl;
  unsigned int n=rPL.ptrhashtree()->size();
  for(unsigned int i=0;i<n;++i)
    if((*rPL.ptrhashtree())[i].ptrRoot()!=NULL)  cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- input from istream"<<endl;
  cin>>rPL;
  n=rPL.ptrhashtree()->size();
  for(unsigned int i=0;i<n;++i)
    if((*rPL.ptrhashtree())[i].ptrRoot()!=NULL)  cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  rPL2.refer(rPL);
  rPL.clear();
  cout<<rPL2.keylist().IsAvailable()<<endl;
  vPL.clear();
  cout<<rPL2.keylist().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}
