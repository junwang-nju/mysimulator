
#include "matrix/allocate.h"
#include "matrix/io.h"
#include "matrix/copy.h"
#include "matrix/fill.h"
#include "matrix/swap.h"
#include "matrix/storage/item/copy.h"
#include "matrix/storage/allocate.h"
#include "list/io.h"
#include "io/console.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {

  cout<<endl;
  Matrix<unsigned int>  M,M1,MT;
  cout<<"Before Allocation: size of Matrix property is:\t";
  cout<<M.property.size<<endl;
  allocate(M,MatrixRectangle,3,5,OrderC,Transposed);
  cout<<"After Allocation: size of Matrix property is:\t";
  cout<<M.property.size<<endl;
  imprint(M1,M);
  cout<<"After Imprint: size of Matrix property is:\t";
  cout<<M1.property.size<<endl;
  release(M1);
  cout<<"After Release: size of Matrix property is:\t";
  cout<<M1.property.size<<endl;
  allocate(MT,MatrixTriangle,4,OrderDiagonal,NoTranspose,UpperTriangle,false,true);
  cout<<"After Allocation of Triangle: size of Matrix property is:\t";
  cout<<MT.property.size<<endl;
  allocate(MT,MatrixTriangle,4,OrderDiagonal,NoTranspose,UpperTriangle,false,false);
  cout<<"After Allocation of Triangle: size of Matrix property is:\t";
  cout<<MT.property.size<<endl;
  allocate(MT,MatrixTriangle,4,OrderDiagonal,NoTranspose,UpperTriangle,true,false);
  cout<<"After Allocation of Triangle: size of Matrix property is:\t";
  cout<<MT.property.size<<endl;
  allocate(MT,MatrixTriangle,4,OrderC,Transposed,LowerTriangle,true,false);
  MT.other()=0;
  cout<<"After Allocation of Triangle: size of Matrix property is:\t";
  cout<<MT.property.size<<endl;

  cout<<endl;
  cout<<"Validity of allocated Matrix:\t"<<IsValid(M)<<endl;
  cout<<"Validity of un-allocated Matrix:\t"<<IsValid(M1)<<endl;

  cout<<endl;
  M(2,3)=7;
  cout<<"Output of Matrix:"<<endl;
  COut<<M<<Endl;
  cout<<"Actual List of Data of Matrix:"<<endl;
  COut<<static_cast<List<unsigned int>&>(M)<<Endl;
  for(unsigned int i=0;i<4;i++)
  for(unsigned int j=i+1;j<4;j++) MT(i,j)=0;
  MT(2,3)=9;
  cout<<"Output of Matrix:"<<endl;
  COut<<MT<<Endl;
  cout<<"Actual List of Data of Matrix:"<<endl;
  COut<<static_cast<List<unsigned int>&>(MT)<<Endl;

  cout<<endl;
  MT(1,2)=3;
  copy(M,MT);
  cout<<"Copy Triangle to Rectangle:"<<endl;
  COut<<M<<Endl;

  cout<<endl;
  fill(MT,12U);
  cout<<"Fill Triangle Matrix:"<<endl;
  COut<<MT<<Endl;

  cout<<endl;
  cout<<"Compare different-type Matrix:\t"<<IsPropertySame(M,MT)<<endl;
  imprint(M1,MT);
  cout<<"Compare Matrix with same structure:\t"<<IsPropertySame(M1,MT)<<endl;

  cout<<endl;
  swap(M,MT);
  cout<<"Matrix After swap:"<<endl;
  COut<<MT<<Endl;

  cout<<endl;
  MatrixStorageItem<unsigned int> MSI,MSI1;
  cout<<"Before Allocation: the status is:\t";
  cout<<MSI.status<<endl;
  allocate(MSI);
  cout<<"After Allocation: the status is:\t";
  cout<<MSI.status<<endl;
  imprint(MSI1,MSI);
  cout<<"After Imprint: the status is:\t";
  cout<<MSI1.status<<endl;
  release(MSI1);
  cout<<"After Release: the status is:\t";
  cout<<MSI1.status<<endl;

  cout<<endl;
  allocate(MSI1);
  MSI.content=109;
  copy(MSI1,MSI);
  cout<<"Content of Item in MatrixStorage After Copy is:\t";
  cout<<MSI1.content<<endl;

  cout<<endl;
  MatrixStorage<unsigned int> MS,MS1;
  cout<<"Before Allocation: the status of MatrixStorage is:\t";
  cout<<MS.status()<<endl;
  allocate(MS,6);
  cout<<"After Allocation: the status of MatrixStorage is:\t";
  cout<<MS.status()<<endl;
  imprint(MS1,MS);
  cout<<"After Imprint: the status of MatrixStorage is:\t";
  cout<<MS.status()<<endl;
  release(MS1);
  cout<<"After Release: the status of MatrixStorage is:\t";
  cout<<MS.status()<<endl;

  cout<<endl;
  cout<<"Status before renew:\t"<<MS.status(3,4)<<endl;
  cout<<"Global Status before renew:\t"<<MS.status()<<endl;
  MS.renew(3,4,207U);
  cout<<"Value after renew:\t"<<MS.value(3,4)<<endl;
  cout<<"Status after renew:\t"<<MS.status(3,4)<<endl;
  cout<<"Global Status after renew:\t"<<MS.status()<<endl;
  MS.unlock(3,4);
  cout<<"Status after unlock:\t"<<MS.status(3,4)<<endl;
  cout<<"Global Status after unlock:\t"<<MS.status()<<endl;
  MS.unlock(3);
  cout<<"Status after line unlock:"<<endl;
  for(unsigned int i=0;i<6;i++) cout<<"\t"<<MS.status(3,4);
  cout<<endl;
  cout<<"Global Status after line unlock:\t"<<MS.status()<<endl;
  MS.unlock();
  cout<<"Global Status after global unlock:\t"<<MS.status()<<endl;

  return 0;
}

