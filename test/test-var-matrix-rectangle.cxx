
#include "var-matrix-rectangle.h"
#include <iostream>
using namespace std;

int main() {
  varRectMatrix<double> dM;

  cout<<"Test -- allocation with dimension and order"<<endl;
  dM.allocate(3,5,FortranOrder);
  cout<<dM.NumRow()<<"\t\t"<<dM.NumCol()<<endl;
  cout<<dM.MatrixOrder()<<"\t";
  cout<<dM.MatrixTransposeState()<<"\t";
  cout<<dM.MatrixActualOrder()<<endl;
  dM.allocate(3,5,FortranOrder,WithTranspose);
  cout<<dM.NumRow()<<"\t\t"<<dM.NumCol()<<endl;
  cout<<dM.MatrixOrder()<<"\t";
  cout<<dM.MatrixTransposeState()<<"\t";
  cout<<dM.MatrixActualOrder()<<endl;
  dM.allocate(3,5,COrder,WithTranspose);
  cout<<dM.NumRow()<<"\t\t"<<dM.NumCol()<<endl;
  cout<<dM.MatrixOrder()<<"\t";
  cout<<dM.MatrixTransposeState()<<"\t";
  cout<<dM.MatrixActualOrder()<<endl;
  dM.allocate(3,5);
  cout<<dM.NumRow()<<"\t\t"<<dM.NumCol()<<endl;
  cout<<dM.MatrixOrder()<<"\t";
  cout<<dM.MatrixTransposeState()<<"\t";
  cout<<dM.MatrixActualOrder()<<endl;
  cout<<endl;

  cout<<"Test -- initiate with dimension and order"<<endl;
  varRectMatrix<double> dMA(3,5);
  cout<<dMA.NumRow()<<"\t\t"<<dMA.NumCol()<<endl;
  cout<<dMA.MatrixOrder()<<"\t";
  cout<<dMA.MatrixTransposeState()<<"\t";
  cout<<dMA.MatrixActualOrder()<<endl;
  varRectMatrix<double> dMB(3,5,FortranOrder);
  cout<<dMB.NumRow()<<"\t\t"<<dMB.NumCol()<<endl;
  cout<<dMB.MatrixOrder()<<"\t";
  cout<<dMB.MatrixTransposeState()<<"\t";
  cout<<dMB.MatrixActualOrder()<<endl;
  varRectMatrix<double> dMC(3,5,COrder,WithTranspose);
  cout<<dMC.NumRow()<<"\t\t"<<dMC.NumCol()<<endl;
  cout<<dMC.MatrixOrder()<<"\t";
  cout<<dMC.MatrixTransposeState()<<"\t";
  cout<<dMC.MatrixActualOrder()<<endl;
  varRectMatrix<double> dMD(3,5,FortranOrder,WithTranspose);
  cout<<dMD.NumRow()<<"\t\t"<<dMD.NumCol()<<endl;
  cout<<dMD.MatrixOrder()<<"\t";
  cout<<dMD.MatrixTransposeState()<<"\t";
  cout<<dMD.MatrixActualOrder()<<endl;
  cout<<endl;

  cout<<"Test -- assign with constant"<<endl;
  dM=5.;
  for(unsigned int i=0;i<dM.NumRow();++i) {
    for(unsigned int j=0;j<dM.NumCol();++j) cout<<dM(i,j)<<"\t";
    cout<<endl;
  }
  cout<<endl;

  cout<<"Test -- assign with another matrix"<<endl;
  varRectMatrix<double> dM2(3,5);
  dM2=dM;
  for(unsigned int i=0;i<dM2.NumRow();++i) {
    for(unsigned int j=0;j<dM2.NumCol();++j) cout<<dM2(i,j)<<"\t";
    cout<<endl;
  }
  cout<<endl;

  cout<<"Test -- assign with a vector"<<endl;
  varVector<double> dV(15);
  for(unsigned int i=0;i<dV.size();++i) dV[i]=i+1;
  dM=dV;
  for(unsigned int i=0;i<dM.NumRow();++i) {
    for(unsigned int j=0;j<dM.NumCol();++j) cout<<dM(i,j)<<"\t";
    cout<<endl;
  }
  cout<<endl;

  cout<<"Test -- type"<<endl;
  cout<<dM.type()<<endl;
  cout<<endl;

  cout<<"Test -- access data through () operator"<<endl;
  for(unsigned int i=0;i<dM.NumRow();++i)
  for(unsigned int j=0;j<dM.NumCol();++j)
    dM(i,j)=i+j;
  for(unsigned int i=0;i<dM.NumRow();++i) {
    for(unsigned int j=0;j<dM.NumCol();++j) cout<<dM(i,j)<<"\t";
    cout<<endl;
  }
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  dM.clear();
  cout<<endl;
  return 1;
}

