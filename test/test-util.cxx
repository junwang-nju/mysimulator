
#include "util.h"
#include <iostream>
using namespace std;

int main() {
  int I=9;
  unsigned int UI=8u;
  double D=90.1;

  cout<<"Test -- nollify<int>"<<endl;
  Nullify(I);
  cout<<I<<endl;
  cout<<endl;

  cout<<"Test -- nollify<unsigned int>"<<endl;
  Nullify(UI);
  cout<<UI<<endl;
  cout<<endl;

  cout<<"Test -- nollify<double>"<<endl;
  Nullify(D);
  cout<<D<<endl;
  cout<<endl;

  cout<<"Test -- compare<int>"<<endl;
  cout<<"1"<<"\t\t"<<2<<"\t:\t"<<compare(1,2)<<endl;
  cout<<"3"<<"\t\t"<<2<<"\t:\t"<<compare(3,2)<<endl;
  cout<<"2"<<"\t\t"<<2<<"\t:\t"<<compare(2,2)<<endl;
  cout<<endl;

  return 1;
}

