
#include "fix-parameter-list.h"
#include <iostream>
using namespace std;

int main() {
  fixParameterList<7> fPL;

  cout<<"Test -- allocate with two vectors"<<endl;
  varVector<unsigned int> kS(7);
  fixVector<unsigned int,9> vS;
  kS=3;
  vS=2;
  fPL.initAs(kS,vS);
  cout<<endl;

  cout<<"Test -- allocate with two constants"<<endl;
  fixParameterList<7> fPL2;
  fPL2.initAs(3,2);
  cout<<endl;

  cout<<"Test -- assign with another parameter list"<<endl;
  fPL2=fPL;
  cout<<endl;

  cout<<"Test -- access contents through keylist() and valuelist()"<<endl;
  for(unsigned int i=0;i<7;++i) {
    fPL.keylist()[i].index()[0]=i+1;
    fPL.keylist()[i].index()[1]=i+2;
    fPL.keylist()[i].index()[2]=i+3;
    fPL.keylist()[i].BuildHash();
    fPL.valuelist()[i][0]=i*2.5;
    fPL.valuelist()[i][1]=i*3.5+0.5;
  }
  cout<<endl;
  
  cout<<"Test -- update hash tree"<<endl;
  fPL.updateHashTree();
  cout<<endl;

  cout<<"Test -- get value through index"<<endl;
  varVector<unsigned int> idx(3);
  idx[0]=2;
  idx[1]=3;
  idx[2]=4;
  varParameterValue* pvPV=const_cast<varParameterValue*>(fPL.get(idx));
  if(pvPV!=NULL)    cout<<(*pvPV)<<endl;
  cout<<endl;

  cout<<"Test -- access the hash tree"<<endl;
  unsigned int n=fPL.ptrhashtree()->size();
  for(unsigned int i=0;i<n;++i)
    if((*fPL.ptrhashtree())[i].ptrRoot()!=NULL)  cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- input from istream"<<endl;
  cin>>fPL;
  n=fPL.ptrhashtree()->size();
  for(unsigned int i=0;i<n;++i)
    if((*fPL.ptrhashtree())[i].ptrRoot()!=NULL)  cout<<i<<endl;
  cout<<endl;

  return 1;
}
