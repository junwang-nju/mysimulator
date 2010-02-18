
#include "var-parameter-list.h"
#include <iostream>
using namespace std;

int main() {
  varParameterList vPL;

  cout<<"Test -- allocate with a constant"<<endl;
  vPL.allocate(5);
  cout<<endl;

  cout<<"Test -- allocate with two vectors"<<endl;
  varVector<unsigned int> kS(7);
  fixVector<unsigned int,9> vS;
  kS=3;
  vS=2;
  vPL.allocate(kS,vS);
  cout<<endl;

  cout<<"Test -- allocate with part of two vectors"<<endl;
  varParameterList vPL2;
  vPL2.allocate(kS,vS,7);
  cout<<endl;

  cout<<"Test -- assign with another parameter list"<<endl;
  vPL2=vPL;
  cout<<endl;

  cout<<"Test -- access contents through keylist() and valuelist()"<<endl;
  for(unsigned int i=0;i<7;++i) {
    vPL.keylist()[i].index()[0]=i+1;
    vPL.keylist()[i].index()[1]=i+2;
    vPL.keylist()[i].index()[2]=i+3;
    vPL.keylist()[i].BuildHash();
    vPL.valuelist()[i][0]=i*2.5;
    vPL.valuelist()[i][1]=i*3.5+0.5;
  }
  cout<<endl;
  
  cout<<"Test -- update hash tree"<<endl;
  vPL.updateHashTree();
  cout<<endl;

  cout<<"Test -- get value through index"<<endl;
  varVector<unsigned int> idx(3);
  idx[0]=2;
  idx[1]=3;
  idx[2]=4;
  varParameterValue* pvPV=const_cast<varParameterValue*>(vPL.get(idx));
  if(pvPV!=NULL)    cout<<(*pvPV)<<endl;
  cout<<endl;

  cout<<"Test -- access the hash tree"<<endl;
  unsigned int n=vPL.hashtree().size();
  for(unsigned int i=0;i<n;++i)
    if(vPL.hashtree()[i].ptrRoot()!=NULL)  cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- input from istream"<<endl;
  cin>>vPL;
  n=vPL.hashtree().size();
  for(unsigned int i=0;i<n;++i)
    if(vPL.hashtree()[i].ptrRoot()!=NULL)  cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  vPL.clear();
  cout<<endl;
  return 1;
}
