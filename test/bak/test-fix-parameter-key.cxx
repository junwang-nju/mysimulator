
#include "fix-parameter-key.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- init"<<endl;
  fixParameterKey<3> fPK;
  fixParameterKey<3> fPK1;
  cout<<endl;

  cout<<"Test -- assign through index"<<endl;
  fPK.index()[0]=1.;
  fPK.index()[1]=100.;
  fPK.index()[2]=0;
  cout<<endl;

  cout<<"Test -- assign through another key"<<endl;
  fPK1=fPK;
  cout<<fPK1.index()<<endl;
  cout<<endl;

  cout<<"Test -- read hash"<<endl;
  cout<<fPK1.hash()<<endl;
  cout<<endl;

  cout<<"Test -- read from cin"<<endl;
  cin>>fPK;
  fPK1=fPK;
  cout<<fPK1.index()<<endl;
  cout<<fPK1.hash()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  fPK1.clear();
  cout<<fPK1.index().size()<<endl;
  cout<<fPK1.hash().size()<<endl;
  cout<<endl;

  return 1;
}

