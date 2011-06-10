
#include "map/allocate.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {

  cout<<endl;
  MapHash<3> MH,MH1;
  cout<<"Before Allocation: value of hash is:\t"<<MH(2)<<endl;
  allocate(MH);
  cout<<"After Allocation: value of hash is:\t"<<MH(2)<<endl;
  imprint(MH1,MH);
  cout<<"After Imprint: value of hash is:\t"<<MH1(2)<<endl;
  release(MH1);
  cout<<"After Release: value of hash is:\t"<<MH1(2)<<endl;

  MH(1)=5;
  cout<<"Access through () operator:"<<endl;
  for(unsigned int i=0;i<3;i++) cout<<"\t"<<MH(i);
  cout<<endl;

  cout<<endl;
  allocate(MH1);
  copy(MH1,MH);
  cout<<"After COpy: data in hash is:"<<endl;
  for(unsigned int i=0;i<3;i++) cout<<"\t"<<MH(i);
  cout<<endl;

  cout<<endl;
  cout<<"Compare Hash:\t"<<compare(MH,MH1)<<endl;

  cout<<endl;
  MapElement<unsigned int,double> ME,ME1;
  cout<<"Before Allocation: value of hash is:\t";
  cout<<ME.hash(2)<<endl;
  allocate(ME);
  cout<<"After Allocation: value of hash is:\t";
  cout<<ME.hash(2)<<endl;
  allocate(ME.key());
  allocate(ME.value());
  imprint(ME1,ME);
  cout<<"After Imprint: value of hash is:\t";
  cout<<ME.hash(2)<<endl;
  release(ME1);
  cout<<"After Release: value of hash is:\t";
  cout<<ME.hash(2)<<endl;
  ME.key()=23489;
  ME.update();
  cout<<"After Update: data of hash is:";
  for(unsigned int i=0;i<3;++i) cout<<"\t"<<ME.hash(i);
  cout<<endl;

  cout<<endl;
  imprint(ME1,ME);
  copy(ME1,ME);
  cout<<"After Copy: data of hash is:";
  for(unsigned int i=0;i<3;++i) cout<<"\t"<<ME1.hash(i);
  cout<<endl;
  
  cout<<endl;
  Map<unsigned int,double> M,M1;
  cout<<"Before Allocation: the validity of data is:\t";
  cout<<IsValid(M.data)<<endl;
  allocate(M);
  cout<<"After Allocation: the validity of data is:\t";
  cout<<IsValid(M.data)<<endl;
  imprint(M1,M);
  cout<<"After Imprint: the validity of data is:\t";
  cout<<IsValid(M1.data)<<endl;
  release(M1);
  cout<<"After Release: the validity of data is:\t";
  cout<<IsValid(M1.data)<<endl;

  cout<<endl;
  ME.key()=5;
  ME.value()=5.5;
  ME.update();
  M.add(ME);
  cout<<"After Add a Element: mesh and data are"<<endl;
  for(unsigned int i=0;i<0xFFFFU;i++) if(IsValid(M.mesh[i]))  cout<<"\t"<<i;
  cout<<endl;
  cout<<"\t"<<M.data.root.child().content().key();
  cout<<"\t"<<M.data.root.child().content().value()<<endl;
  M.add(4U,4.5,Allocated,Allocated);
  cout<<"After Add a key and value: mesh and data are"<<endl;
  for(unsigned int i=0;i<0xFFFFU;i++) if(IsValid(M.mesh[i]))  cout<<"\t"<<i;
  cout<<endl;
  cout<<"\t"<<M.data.root.child().content().key();
  cout<<"\t"<<M.data.root.child().content().value()<<endl;
  cout<<"\t"<<M.data.root.child().child().content().key();
  cout<<"\t"<<M.data.root.child().child().content().value()<<endl;
  unsigned int g=0;
  double dg=0.5;
  M.add(g,dg);
  cout<<"After Add a key and value: mesh and data are"<<endl;
  for(unsigned int i=0;i<0xFFFFU;i++) if(IsValid(M.mesh[i]))  cout<<"\t"<<i;
  cout<<endl;
  cout<<"\t"<<M.data.root.child().content().key();
  cout<<"\t"<<M.data.root.child().content().value()<<endl;
  cout<<"\t"<<M.data.root.child().child().content().key();
  cout<<"\t"<<M.data.root.child().child().content().value()<<endl;
  cout<<"\t"<<M.data.root.child().child().child().content().key();
  cout<<"\t"<<M.data.root.child().child().child().content().value()<<endl;
  M.remove(5);
  cout<<"After remove a key and value: mesh and data are"<<endl;
  for(unsigned int i=0;i<0xFFFFU;i++) if(IsValid(M.mesh[i]))  cout<<"\t"<<i;
  cout<<endl;
  cout<<"\t"<<M.data.root.child().content().key();
  cout<<"\t"<<M.data.root.child().content().value()<<endl;
  cout<<"\t"<<M.data.root.child().child().content().key();
  cout<<"\t"<<M.data.root.child().child().content().value()<<endl;
  return 0;
}

