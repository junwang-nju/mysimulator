
#include "periodic-box.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  PeriodicBox PB;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(PB,4);
  cout<<endl;

  cout<<"Test -- set periodic box"<<endl;
  Vector<double> vd;
  Vector<unsigned int> vi;
  allocate(vd,7);
  allocate(vi,9);
  assign(vd,2.3);   vd[3]=12.7;   vd[4]=8.9;
  assign(vi,HavePeriodic);  vi[5]=NoPeriodic;
  set(PB,vd,vi);
  for(unsigned int i=0;i<PB.size;++i)
    cout<<PB.box[i]<<"\t\t"<<PB.halfbox[i]<<"\t\t"<<PB.edgeflag[i]<<endl;
  cout<<endl;
  set(PB,vd,NoPeriodic);
  for(unsigned int i=0;i<PB.size;++i)
    cout<<PB.box[i]<<"\t\t"<<PB.halfbox[i]<<"\t\t"<<PB.edgeflag[i]<<endl;
  cout<<endl;
  set(PB,vd(),5,HavePeriodic,2,1);
  for(unsigned int i=0;i<PB.size;++i)
    cout<<PB.box[i]<<"\t\t"<<PB.halfbox[i]<<"\t\t"<<PB.edgeflag[i]<<endl;
  cout<<endl;
  set(PB,vd(),vi(),4,0,2,2,1);
  for(unsigned int i=0;i<PB.size;++i)
    cout<<PB.box[i]<<"\t\t"<<PB.halfbox[i]<<"\t\t"<<PB.edgeflag[i]<<endl;
  cout<<endl;

  cout<<"Test -- compress to main region"<<endl;
  assign(vd,18.9);   vd[5]=22.7;   vd[4]=-78.9;
  Compress2MainRegion(PB,vd(),5,2,1);
  cout<<vd<<endl;
  cout<<endl;

  cout <<"Test -- calculate displacement"<<endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  assign(va,1.);    va[2]=-15.;   va[3]=87.9;
  assign(vb,57.63); vb[3]=123.45;
  DisplacementFunc(va(),vb(),5,vd(),PB,0,2,0,3,2,1);
  cout<<vd<<endl;
  assign(va,1.);    va[2]=-15.;   va[3]=87.9;
  assign(vb,57.63); vb[3]=123.45;
  DisplacementFunc(va,vb,vd,PB);
  cout<<vd<<endl;
  cout<<endl;

  cout<<"Test - assign from another Periodic Box"<<endl;
  PeriodicBox PB2;
  allocate(PB2,5);
  assign(PB2,PB);
  for(unsigned int i=0;i<PB2.size;++i)
    cout<<PB2.box[i]<<"\t\t"<<PB2.halfbox[i]<<"\t\t"<<PB2.edgeflag[i]<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(PB2);
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(PB2,PB);
  for(unsigned int i=0;i<PB2.size;++i)
    cout<<PB2.box[i]<<"\t\t"<<PB2.halfbox[i]<<"\t\t"<<PB2.edgeflag[i]<<endl;
  cout<<endl;

  return 1;
}

