
#include "unique-parameter.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- create"<<endl;
  UniqueParameter up;
  cout<<endl;

  cout<<"Test -- assign and read"<<endl;
  copy(up,1.5);
  cout<<up.d<<"\t\t"<<up.ull<<endl;
  copy(up,1U);
  cout<<up.u<<"\t\t"<<up.ull<<endl;
  copy(up,-1);
  cout<<up.i<<"\t\t"<<up.ull<<endl;
  double p=9.6;
  cout<<&p<<endl;
  copy(up,&p);
  cout<<up.ptr<<"\t\t"<<up.ull<<endl;
  cout<<endl;

  cout<<"Test - assign from another unique parameter"<<endl;
  UniqueParameter up2;
  copy(up2,up);
  cout<<up2.ull<<endl;
  cout<<endl;

  cout<<"Test -- read from istream"<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d<<endl;
  cout<<"\t"<<up.u<<endl;
  cout<<"\t"<<up.i<<endl;
  cout<<"\t"<<up.ptr<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d<<endl;
  cout<<"\t"<<up.u<<endl;
  cout<<"\t"<<up.i<<endl;
  cout<<"\t"<<up.ptr<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d<<endl;
  cout<<"\t"<<up.u<<endl;
  cout<<"\t"<<up.i<<endl;
  cout<<"\t"<<up.ptr<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d<<endl;
  cout<<"\t"<<up.u<<endl;
  cout<<"\t"<<up.i<<endl;
  cout<<"\t"<<up.ptr<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d<<endl;
  cout<<"\t"<<up.u<<endl;
  cout<<"\t"<<up.i<<endl;
  cout<<"\t"<<up.ptr<<endl;
  cout<<endl;

  return 1;
}

