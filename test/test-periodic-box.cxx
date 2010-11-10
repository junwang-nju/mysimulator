
#include "data/geometry/periodic-box.h"
#include "operation/geometry/displacement-calc-periodicbox.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  PeriodicBox<double> PB;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(PB,4);
  cout<<endl;

  cout<<"Test -- set periodic box"<<endl;
  Vector<double> vd;
  Vector<unsigned int> vi;
  allocate(vd,7);
  allocate(vi,9);
  copy(vd,2.3);   vd[3]=12.7;   vd[4]=8.9;
  copy(vi,1);  vi[5]=0;
  set(PB,vd,vi);
  for(unsigned int i=0;i<PB.size;++i)
    cout<<PB[i]<<"\t\t"<<PB.halfBox[i]<<"\t\t"<<PB.edgeFlag[i]<<endl;
  cout<<endl;
  set(PB,vd,0);
  for(unsigned int i=0;i<PB.size;++i)
    cout<<PB[i]<<"\t\t"<<PB.halfBox[i]<<"\t\t"<<PB.edgeFlag[i]<<endl;
  cout<<endl;

  cout<<"Test -- compress to main region"<<endl;
  copy(vd,18.9);   vd[5]=22.7;   vd[4]=-78.9;
  relocateVector(vd(),5,PB,2,1);
  cout<<vd<<endl;
  cout<<endl;

  cout <<"Test -- calculate displacement"<<endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  copy(va,1.);    va[2]=-15.;   va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  Displacement(va(),vb(),vd(),5,PB,0,2,0,3,2,1);
  cout<<vd<<endl;
  copy(va,1.);    va[2]=-15.;   va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  Displacement(va,vb,vd,PB);
  cout<<vd<<endl;
  cout<<endl;

  cout<<"Test - assign from another Periodic Box"<<endl;
  PeriodicBox<double> PB2;
  allocate(PB2,5);
  copy(PB2,PB);
  for(unsigned int i=0;i<PB2.size;++i)
    cout<<PB2[i]<<"\t\t"<<PB2.halfBox[i]<<"\t\t"<<PB2.edgeFlag[i]<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(PB2);
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(PB2,PB);
  for(unsigned int i=0;i<PB2.size;++i)
    cout<<PB2[i]<<"\t\t"<<PB2.halfBox[i]<<"\t\t"<<PB2.edgeFlag[i]<<endl;
  cout<<endl;

  cout<<"Test -- check whether it is a geometry"<<endl;
  cout<<IsGeometry(PB)<<endl;
  cout<<IsGeometry(va)<<endl;
  cout<<endl;

  return 1;
}

