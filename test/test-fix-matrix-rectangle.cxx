
#include "fix-matrix-rectangle.h"
#include "var-vector.h"
#include <iostream>
using namespace std;

int main() {

  fixRectMatrix<double,3,5> dM;

  cout<<"Test -- initiate with dimension and order"<<endl;
  fixRectMatrix<double,3,5> dMA;
  cout<<dMA.NumRow()<<"\t\t"<<dMA.NumCol()<<endl;
  cout<<dMA.MatrixOrder()<<"\t";
  cout<<dMA.MatrixTransposeState()<<"\t";
  cout<<dMA.MatrixActualOrder()<<endl;
  fixRectMatrix<double,3,5,FortranOrder> dMB;
  cout<<dMB.NumRow()<<"\t\t"<<dMB.NumCol()<<endl;
  cout<<dMB.MatrixOrder()<<"\t";
  cout<<dMB.MatrixTransposeState()<<"\t";
  cout<<dMB.MatrixActualOrder()<<endl;
  fixRectMatrix<double,3,5,COrder,WithTranspose> dMC;
  cout<<dMC.NumRow()<<"\t\t"<<dMC.NumCol()<<endl;
  cout<<dMC.MatrixOrder()<<"\t";
  cout<<dMC.MatrixTransposeState()<<"\t";
  cout<<dMC.MatrixActualOrder()<<endl;
  fixRectMatrix<double,3,5,FortranOrder,WithTranspose> dMD;
  cout<<dMD.NumRow()<<"\t\t"<<dMD.NumCol()<<endl;
  cout<<dMD.MatrixOrder()<<"\t";
  cout<<dMD.MatrixTransposeState()<<"\t";
  cout<<dMD.MatrixActualOrder()<<endl;
  cout<<endl;

  cout<<"Test -- assign with constant"<<endl;
  dM=5.;
  cout<<dM<<endl;
  cout<<endl;

  cout<<"Test -- assign with another matrix"<<endl;
  fixRectMatrix<double,3,5> dM2;
  dM2=dM;
  cout<<dM2<<endl;
  cout<<endl;

  cout<<"Test -- assign with a vector"<<endl;
  varVector<double> dV(15);
  for(unsigned int i=0;i<dV.size();++i) dV[i]=i+1;
  dM=dV;
  cout<<dM<<endl;
  cout<<endl;

  cout<<"Test -- type"<<endl;
  cout<<dM.type()<<endl;
  cout<<endl;

  cout<<"Test -- access data through () operator"<<endl;
  for(unsigned int i=0;i<dM.NumRow();++i)
  for(unsigned int j=0;j<dM.NumCol();++j)
    dM(i,j)=i+j;
  cout<<dM<<endl;
  cout<<endl;

  return 1;
}

