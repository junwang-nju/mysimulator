
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
  *(dM.PtrOtherElement)=0;
  Matrix<double> dM2;
  refer(dM2,dM);
  assign(dM2.data,3,5);
  cout<<dM<<endl;

  Matrix<double> dM3;
  allocate(dM3,RectangleMatrix,4,3,COrder,NoTranspose);
  dM3=dM;
  cout<<dM3<<endl;

  return 1;
}

