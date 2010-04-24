
#include "var-parameter-key.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- init"<<endl;
  varParameterKey vPK;
  varParameterKey vPK1;
  cout<<endl;

  cout<<"Test -- Set size of index"<<endl;
  vPK.allocate(3);
  vPK1.allocate(3);
  cout<<endl;

  cout<<"Test -- assign through index"<<endl;
  vPK.index()[0]=1.;
  vPK.index()[1]=100.;
  vPK.index()[2]=0;
  cout<<endl;

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

  return 1;
}

