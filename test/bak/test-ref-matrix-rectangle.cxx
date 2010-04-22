
#include "ref-matrix-rectangle.h"
#include "var-matrix-rectangle.h"
#include "fix-matrix-rectangle.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- refer various kinds of var rectangle matrix"<<endl;
  refMatrixRectangle<double>::Type rdM;
  varMatrixRectangle<double>::Type vdM(3,5);
  rdM.refer(vdM);
  cout<<rdM.NumRow()<<"\t\t"<<rdM.NumCol()<<endl;
  cout<<rdM.MatrixOrder()<<"\t";
  cout<<rdM.MatrixTransposeState()<<"\t";
  cout<<rdM.MatrixActualOrder()<<endl;
  vdM.allocate(3,5,FortranOrder,WithTranspose);
  rdM.refer(vdM);
  cout<<rdM.NumRow()<<"\t\t"<<rdM.NumCol()<<endl;
  cout<<rdM.MatrixOrder()<<"\t";
  cout<<rdM.MatrixTransposeState()<<"\t";
  cout<<rdM.MatrixActualOrder()<<endl;
  cout<<endl;

  cout<<"Test -- refer fix rectangle matrix"<<endl;
  fixMatrixRectangle<double,3,5,COrder,WithTranspose>::Type fdM;
  refMatrixRectangle<double>::Type rdM2;
  rdM2.refer(fdM);
  cout<<rdM2.NumRow()<<"\t\t"<<rdM2.NumCol()<<endl;
  cout<<rdM2.MatrixOrder()<<"\t";
  cout<<rdM2.MatrixTransposeState()<<"\t";
  cout<<rdM2.MatrixActualOrder()<<endl;
  cout<<endl;

  cout<<"Test -- refer ref rectangle matrix"<<endl;
  refMatrixRectangle<double>::Type rdM3;
  rdM3.refer(rdM);
  cout<<rdM3.NumRow()<<"\t\t"<<rdM3.NumCol()<<endl;
  cout<<rdM3.MatrixOrder()<<"\t";
  cout<<rdM3.MatrixTransposeState()<<"\t";
  cout<<rdM3.MatrixActualOrder()<<endl;
  cout<<endl;

  cout<<"Test -- assign with constant"<<endl;
  rdM=5.;
  cout<<rdM<<endl;
  cout<<endl;

  cout<<"Test -- assign with another matrix"<<endl;
  rdM(1,2)=3;
  rdM2=rdM;
  cout<<rdM2<<endl;
  cout<<endl;

  cout<<"Test -- assign with a vector for various orders of matrix"<<endl;
  varVector<double> dV(15);
  for(unsigned int i=0;i<dV.size();++i) dV[i]=i+1;
  rdM2=dV;
  cout<<rdM2<<endl;
  rdM=dV;
  cout<<rdM<<endl;
  cout<<endl;

  cout<<"Test -- type"<<endl;
  cout<<rdM.type()<<endl;
  cout<<endl;

  cout<<"Test -- access data through () operator"<<endl;
  for(unsigned int i=0;i<rdM.NumRow();++i)
  for(unsigned int j=0;j<rdM.NumCol();++j)
    rdM(i,j)=i+j;
  cout<<rdM<<endl;
  cout<<endl;

  cout<<"Test -- refer part of reference rectangle matrix"<<endl;
  refMatrixRectangle<double>::Type rDM3;
  rDM3.refer(rdM,1,2);
  cout<<rDM3<<endl;
  cout<<endl;

  cout<<"Test -- refer part of storable reference rectangle matrix"<<endl;
  rdM2.refer(fdM,2,2);
  cout<<rdM2<<endl;
  cout<<rdM2.NumRow()<<"\t\t"<<rdM2.NumCol()<<endl;
  cout<<rdM2.MatrixOrder()<<"\t";
  cout<<rdM2.MatrixTransposeState()<<"\t";
  cout<<rdM2.MatrixActualOrder()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  rdM.clear();
  cout<<endl;

  return 1;
}
