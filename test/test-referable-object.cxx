
#include "referable-object/allocate.h"
#include "referable-object/fill.h"
#include "referable-object/io.h"
#include "referable-object/exchange.h"
#include "referable-object/swap.h"
#include "referable-object/compare.h"
#include "referable-object/mirror.h"
#include "vector/allocate.h"
#include "vector/fill.h"
#include "vector/io.h"
#include "io/console.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  cout<<endl;
  Object<unsigned int> O,O1;
  cout<<"Before Allocation: the flag of object is:\t";
  cout<<O.flag<<endl;
  allocate(O);
  cout<<"After Allocation: the flag of object is:\t";
  cout<<O.flag<<endl;
  imprint(O1,O);
  cout<<"After Imprint: the flag of object is:\t";
  cout<<O1.flag<<endl;
  release(O1);
  cout<<"After Release: the flag of object is:\t";
  cout<<O1.flag<<endl;
  Vector<double> VD;
  Object<Vector<double> > OD;
  allocate(VD,10);
  imprint(OD,VD);
  cout<<"After Imprint: the size of object vector is:\t";
  cout<<OD().size<<endl;
  allocate(OD(),19);
  imprint(VD,OD);
  cout<<"After Imprint: the size of vector is:\t";
  cout<<VD.size<<endl;

  cout<<endl;
  allocate(O1);
  O1()=123213;
  copy(O1,O);
  cout<<"Copy from another Object:\t";
  cout<<O()<<endl;
  copy(O,343497U);
  cout<<"Copy from value:\t";
  cout<<O()<<endl;
  unsigned int i=2332;
  copy(i,O);
  cout<<"Copy to value:\t";
  cout<<i<<endl;
  copy(O,i,Referred);
  i=2342894;
  cout<<"Copy a reference to object:\t";
  cout<<O()<<endl;

  cout<<endl;
  refer(O,O1);
  O1()=777271;
  cout<<"Refer to another object:\t";
  cout<<O()<<endl;
  refer(O,i);
  i=9992;
  cout<<"Refer to a value:\t";
  cout<<O()<<endl;

  cout<<endl;
  fill(OD,O);
  cout<<"Fill object with another object:"<<endl;
  COut<<"\t"<<OD()<<Endl;
  fill(OD,-78.2);
  cout<<"Fill object with value:"<<endl;
  COut<<"\t"<<OD()<<Endl;
  fill<Vector<double> >(VD,O1);
  cout<<"Fill value with object:"<<endl;
  COut<<"\t"<<VD<<Endl;

  cout<<endl;
  cout<<"Output of object:\t";
  COut<<O1<<Endl;
  CIn>>O();
  cout<<"Input of object:\t";
  COut<<O<<Endl;

  cout<<endl;
  Object<unsigned int> O2;
  allocate(O1);
  allocate(O2);
  refer(O,O1);
  O1()=131312;
  O2()=9657965;
  cout<<"Before Exchange: the contents and states of objects are:"<<endl;
  cout<<O1()<<"\t"<<O1.flag<<endl;
  cout<<O2()<<"\t"<<O2.flag<<endl;
  cout<<O()<<"\t"<<O.flag<<endl;
  exchange(O1,O2);
  cout<<"After Exchange: the contents and states of objects are:"<<endl;
  cout<<O1()<<"\t"<<O1.flag<<endl;
  cout<<O2()<<"\t"<<O2.flag<<endl;
  cout<<O()<<"\t"<<O.flag<<endl;
  swap(O,O2);
  cout<<"After Swap: the contents and states of objects are:"<<endl;
  cout<<O1()<<"\t"<<O1.flag<<endl;
  cout<<O2()<<"\t"<<O2.flag<<endl;
  cout<<O()<<"\t"<<O.flag<<endl;

  cout<<endl;
  cout<<"Compare Different Objects:\t"<<IsSameObject(O,OD)<<endl;
  cout<<"Compare same-type Objects:\t"<<IsSameObject(O,O2)<<endl;
  cout<<"Compare referred Objects:\t"<<IsSameObject(O1,O2)<<endl;
  refer(O,i);
  cout<<"Compare Objects and value:\t"<<IsSameObject(O,i)<<endl;
  cout<<"Compare value and Object:\t"<<IsSameObject(i,O)<<endl;
  cout<<"Compare data of two objects:\t"<<compare(O,O1)<<endl;
  cout<<"Compare data of object and value:\t"<<compare(O,i)<<endl;
  cout<<"Compare data of value and object:\t"<<compare(i,O)<<endl;

  cout<<endl;
  mirror(O,O2);
  cout<<"Mirror another object:\t";
  cout<<O()<<"\t"<<O.flag<<endl;

  return 0;
}

