
#include "boundary/free/allocate.h"
#include "boundary/free/copy.h"
#include "boundary/periodic-box/allocate.h"
#include "boundary/periodic-box/copy.h"
#include "boundary/periodic-box/set.h"
#include "vector/fill.h"
#include "vector/io.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {

  cout<<endl;
  FreeSpace FS,FS1;
  cout<<"Before Allocation: Status of object is:\t"<<IsValid(FS)<<endl;
  allocate(FS,3);
  cout<<"After Allocation: Status of object is:\t"<<IsValid(FS)<<endl;
  imprint(FS1,FS);
  cout<<"After Imprint: Status of object is:\t"<<IsValid(FS1)<<endl;
  release(FS1);
  cout<<"After Release: Status of object is:\t"<<IsValid(FS1)<<endl;

  cout<<endl;
  imprint(FS1,FS);
  copy(FS1,FS);
  cout<<"Copy of FreeSpace do nothing"<<endl;

  cout<<endl;
  PeriodicBox<double> PB,PB1;
  cout<<"Before Allocation: Status of box is:\t"<<IsValid(PB.box)<<endl;
  allocate(PB,3);
  cout<<"After Allocation: Status of box is:\t"<<IsValid(PB.box)<<endl;
  imprint(PB1,PB);
  cout<<"After Imprint: Status of box is:\t"<<IsValid(PB1.box)<<endl;
  release(PB1);
  cout<<"After Release: Status of box is:\t"<<IsValid(PB1.box)<<endl;

  cout<<endl;
  allocate(PB1,3);
  fill(PB.box,3.);
  copy(PB1,PB);
  cout<<"Box size after Copy:"<<endl;
  COut<<PB1.box<<Endl;

  cout<<endl;
  Vector<double> bx(3);
  bx[0]=1;    bx[1]=2;    bx[2]=3;
  set(PB,bx);
  cout<<"Periodic Box After set:"<<endl;
  COut<<"\t"<<PB.box<<Endl;
  COut<<"\t"<<PB.hbox<<Endl;
  COut<<"\t"<<PB.flag<<Endl;
  Vector<unsigned int> fg(3);
  bx[0]=1;    bx[1]=5;    bx[2]=3;
  fg[0]=1;    fg[1]=0;    fg[2]=1;
  set(PB,bx,fg);
  cout<<"Periodic Box After set:"<<endl;
  COut<<"\t"<<PB.box<<Endl;
  COut<<"\t"<<PB.hbox<<Endl;
  COut<<"\t"<<PB.flag<<Endl;

  cout<<endl;
  bx[0]=12.3;
  bx[1]=-5.7;
  bx[2]=7.8;
  PB.vectorNormalize(bx);
  cout<<"Vector After Normalization with Periodic Box Boundary:"<<endl;
  COut<<"\t"<<bx<<Endl;
  return 0;
}

