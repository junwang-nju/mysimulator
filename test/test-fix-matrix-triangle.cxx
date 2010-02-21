
#include "fix-matrix-triangle.h"
#include "var-matrix-triangle.h"
#include <iostream>
using namespace std;

int main() {
  fixTriangMatrix<double,4> fTM;

  cout<<"Test -- set structure with dimension"<<endl;
  varVector<double> v(50);
  for(unsigned int i=0;i<v.size();++i)  v[i]=i+1;
  fTM.SetStructure();
  fTM=5.;
  cout<<fTM<<endl;
  fTM=v;
  cout<<fTM<<endl;
  cout<<endl;

  cout<<"Test -- set structure with all parameters"<<endl;
  fTM.SetStructure(COrder,WithTranspose,LowerPart,false);
  fTM=5.;
  fTM(2,1)=3;
  cout<<fTM<<endl;
  fTM=v;
  cout<<fTM<<endl;
  cout<<endl;

  cout<<"Test -- set structure through dimension, various parameters"<<endl;
  fTM.SetStructure(COrder,WithTranspose);
  fTM=5.;
  fTM(1,2)=3.;
  cout<<fTM<<endl;
  fTM=v;
  cout<<fTM<<endl;
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  fixTriangMatrix<double,4> fTM2;
  fTM2.SetStructure(COrder,WithTranspose);
  fTM2=fTM;
  cout<<fTM2<<endl;
  cout<<endl;

  varTriangMatrix<double> vTM;
  vTM.allocate(4,COrder,WithTranspose);
  vTM=9;
  fTM2=vTM;
  cout<<fTM2<<endl;
  cout<<endl;

  cout<<"Test -- type"<<endl;
  cout<<fTM.type()<<endl;
  cout<<endl;

  cout<<"Test -- access data through () operator"<<endl;
  for(unsigned int i=0;i<4;++i)
  for(unsigned int j=i;j<4;++j)
    fTM(i,j)=(i+1)*(j+2);
  cout<<fTM<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  fTM.clear();
  cout<<endl;

  return 1;
}

