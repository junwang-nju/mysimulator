
#include "ref-matrix-triangle.h"
#include "var-matrix-triangle.h"
#include <iostream>
using namespace std;

int main() {
  refMatrixTriangle<double>::Type rTM;
  varMatrixTriangle<double>::Type vTM;

  cout<<"Test -- refer to varMatrixTriangle"<<endl;
  varVector<double> v(50);
  for(unsigned int i=0;i<v.size();++i)  v[i]=i+1;
  vTM.allocate(4);
  rTM.refer(vTM);
  rTM=5.;
  cout<<rTM<<endl;
  rTM=v;
  cout<<rTM<<endl;
  cout<<endl;

  cout<<"Test -- allocate with all parameters"<<endl;
  vTM.allocate(4,COrder,WithTranspose,LowerPart,false,false);
  rTM.refer(vTM);
  rTM=5.;
  rTM(2,1)=3;
  cout<<rTM<<endl;
  rTM=v;
  cout<<rTM<<endl;
  cout<<endl;

  cout<<"Test -- allocate through dimension, order and transpose state"<<endl;
  vTM.allocate(4,COrder,WithTranspose);
  rTM.refer(vTM);
  rTM=5.;
  rTM(1,2)=3.;
  cout<<rTM<<endl;
  rTM=v;
  cout<<rTM<<endl;
  cout<<endl;

  cout<<"Test -- type"<<endl;
  cout<<rTM.type()<<endl;
  cout<<endl;

  cout<<"Test -- assign with variable triangle matrix"<<endl;
  rTM=vTM;
  cout<<endl;

  cout<<"Test -- access data through () operator"<<endl;
  for(unsigned int i=0;i<4;++i)
  for(unsigned int j=i;j<4;++j)
    rTM(i,j)=(i+1)*(j+2);
  cout<<rTM<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  rTM.clear();
  cout<<endl;

  return 1;
}

