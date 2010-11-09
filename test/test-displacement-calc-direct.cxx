
#include "operation/geometry/displacement-calc-direct.h"
using namespace std;

int main() {
  Vector<double> Va,Vb,Vc;
  allocate(Va,10);
  allocate(Vb,10);
  allocate(Vc,10);
  copy(Va,3);
  for(int i=0;i<10;++i) Vb[i]=i;
  Displacement(Va,Vb,Vc);
  cout<<Va<<endl;
  cout<<Vb<<endl;
  cout<<Vc<<endl;

  Vector<int> Vi;
  allocate(Vi,10);
  copy(Vi,3);
  Displacement(Vi,Vb,Vc);
  cout<<Vc<<endl;

  Displacement(Vi.data,Vb.data,Vc.data,4,1,1,1,2,2,2);
  cout<<Vi<<endl;
  cout<<Vb<<endl;
  cout<<Vc<<endl;

  return 0;
}

