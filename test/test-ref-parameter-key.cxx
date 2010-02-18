
#include "ref-parameter-key.h"
#include "var-parameter-key.h"
#include <iostream>
using namespace std;

int main() {
  refParameterKey rPK;
  varParameterKey vPK;
  vPK.SetIndexSize(3);
  rPK.refer(vPK);
  cout<<rPK.index().size()<<endl;
  refParameterKey rPK2;
  rPK2.refer(rPK);
  cout<<rPK2.index().size()<<endl;

  cout<<"Test -- assign through index"<<endl;
  rPK.index()[0]=1.;
  rPK.index()[1]=100.;
  rPK.index()[2]=0;
  cout<<endl;

  varParameterKey vPK2;
  vPK2.SetIndexSize(3);
  vPK2.BuildHash();
  rPK2.refer(vPK2);
  rPK2=rPK;

  cout<<"Test -- read hash"<<endl;
  cout<<rPK2.hash()<<endl;
  cout<<endl;

  cout<<"Test -- read from cin"<<endl;
  cin>>rPK;
  cout<<rPK.index()<<endl;
  cout<<rPK.hash()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  rPK.clear();
  cout<<rPK.index().size()<<endl;
  cout<<rPK.hash().size()<<endl;
  cout<<endl;

  return 1;
}


/*
  */

