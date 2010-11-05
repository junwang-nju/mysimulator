
#include "matrix.h"
#include <iostream>
using namespace std;

int main() {
  Matrix<double> dM;
  allocate(dM,RectangleMatrix,4,5,COrder,NoTranspose);
  cout<<IsAvailable(dM)<<endl;
  release(dM);
  cout<<IsAvailable(dM)<<endl;
  allocate(dM,TriangleMatrix,5,COrder,NoTranspose,UpperTriangle,true,false);
  cout<<"========="<<endl;
  *(dM.ptrOther)=0;
  cout<<"========="<<endl;
  Matrix<double> dM2;
  refer(dM2,dM);
  long n=5;
  double d=3;
  dcopy_(&n,&d,const_cast<long*>(&lZero),dM2.data,const_cast<long*>(&lOne));
  cout<<dM<<endl;
  cout<<dM(2,2)<<endl;

  Matrix<double> dM3;
  allocate(dM3,RectangleMatrix,4,3,COrder,NoTranspose);
  copy(dM3,dM);
  cout<<dM3<<endl;

  return 1;
}

