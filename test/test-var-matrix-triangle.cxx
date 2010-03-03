
#include "var-matrix-triangle.h"
#include <iostream>
using namespace std;

int main() {
  varMatrixTriangle<double> vTM;

  cout<<"Test -- allocate with dimension"<<endl;
  varVector<double> v(50);
  for(unsigned int i=0;i<v.size();++i)  v[i]=i+1;
  vTM.allocate(4);
  vTM=5.;
  cout<<vTM<<endl;
  vTM=v;
  cout<<vTM<<endl;
  cout<<endl;

  cout<<"Test -- allocate with all parameters"<<endl;
  vTM.allocate(4,COrder,WithTranspose,LowerPart,false,false);
  vTM=5.;
  vTM(2,1)=3;
  cout<<vTM(1,3)<<endl;
  cout<<vTM<<endl;
  vTM=v;
  cout<<vTM<<endl;
  cout<<endl;

  cout<<"Test -- allocate through dimension, order and transpose state"<<endl;
  vTM.allocate(4,COrder,WithTranspose);
  vTM=5.;
  vTM(1,2)=3.;
  cout<<vTM<<endl;
  vTM=v;
  cout<<vTM<<endl;
  cout<<endl;

  cout<<"Test -- initiate with dimension"<<endl;
  varMatrixTriangle<double> vTM2(4);
  vTM2=vTM;
  cout<<vTM2<<endl;
  cout<<endl;

  cout<<"Test -- type"<<endl;
  cout<<vTM.type()<<endl;
  cout<<endl;

  cout<<"Test -- access data through () operator"<<endl;
  for(unsigned int i=0;i<4;++i)
  for(unsigned int j=i;j<4;++j)
    vTM(i,j)=(i+1)*(j+2);
  cout<<vTM<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  vTM.clear();
  cout<<endl;

  return 1;
}

