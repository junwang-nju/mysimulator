
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
  cout<<"=============================="<<endl;
  rPK2.refer(vPK2);
  cout<<"=============================="<<endl;
  //rPK2=rPK;

  return 1;
}


/*
  cout<<"Test -- assign through another key"<<endl;
  vPK1=vPK;
  cout<<vPK1.index()<<endl;
  cout<<endl;

  cout<<"Test -- read hash"<<endl;
  cout<<vPK1.hash()<<endl;
  cout<<endl;

  cout<<"Test -- read from cin"<<endl;
  cin>>vPK;
  vPK1=vPK;
  cout<<vPK1.index()<<endl;
  cout<<vPK1.hash()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  vPK1.clear();
  cout<<vPK1.index().size()<<endl;
  cout<<vPK1.hash().size()<<endl;
  cout<<endl;
  */

