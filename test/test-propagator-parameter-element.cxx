
#include "propagator-parameter-element.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- create a propagator parameter element"<<endl;
  PropagatorDataElementType PD;
  cout<<endl;

  cout<<"Test -- assigned with a double value"<<endl;
  PD=2.34;
  cout<<PD.d<<endl;
  cout<<PD.vptr<<endl;
  cout<<PD.ull<<endl;
  cout<<endl;

  cout<<"Test -- output directly"<<endl;
  cout<<PD<<endl;
  cout<<endl;

  cout<<"Test -- assign with a pointer"<<endl;
  double pd;
  PD=&pd;
  cout<<PD.d<<endl;
  cout<<PD.vptr<<endl;
  cout<<PD.ull<<endl;
  cout<<endl;

  cout<<"Test -- copy to another parameter element"<<endl;
  PropagatorDataElementType PD1;
  PD1=PD;
  cout<<PD1<<endl;
  cout<<endl;
  return 1;
}

