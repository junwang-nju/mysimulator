
#include "data/geometry/periodic-box.h"
#include "operation/geometry/displacement-calc-periodicbox.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
using namespace std;

int main() {
  COut<<"Test -- initialize"<<Endl;
  PeriodicBox<double> PB;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(PB,4);
  COut<<Endl;

  COut<<"Test -- set periodic box"<<Endl;
  Vector<double> vd;
  Vector<unsigned int> vi;
  allocate(vd,7);
  allocate(vi,9);
  copy(vd,2.3);   vd[3]=12.7;   vd[4]=8.9;
  copy(vi,1);  vi[5]=0;
  set(PB,vd,vi);
  for(unsigned int i=0;i<PB.size;++i)
    COut<<PB[i]<<"\t\t"<<PB.halfBox[i]<<"\t\t"<<PB.edgeFlag[i]<<Endl;
  COut<<Endl;
  set(PB,vd,0);
  for(unsigned int i=0;i<PB.size;++i)
    COut<<PB[i]<<"\t\t"<<PB.halfBox[i]<<"\t\t"<<PB.edgeFlag[i]<<Endl;
  COut<<Endl;

  COut<<"Test -- compress to main region"<<Endl;
  copy(vd,18.9);   vd[5]=22.7;   vd[4]=-78.9;
  relocateVector(vd(),5,PB,2,1);
  COut<<vd<<Endl;
  COut<<Endl;

  COut <<"Test -- calculate displacement"<<Endl;
  Vector<double> va,vb;
  allocate(va,7);
  allocate(vb,19);
  copy(va,1.);    va[2]=-15.;   va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  Displacement(va(),vb(),vd(),5,PB,0,2,0,3,2,1);
  COut<<vd<<Endl;
  copy(va,1.);    va[2]=-15.;   va[3]=87.9;
  copy(vb,57.63); vb[3]=123.45;
  Displacement(va,vb,vd,PB);
  COut<<vd<<Endl;
  COut<<Endl;

  COut<<"Test - assign from another Periodic Box"<<Endl;
  PeriodicBox<double> PB2;
  allocate(PB2,5);
  copy(PB2,PB);
  for(unsigned int i=0;i<PB2.size;++i)
    COut<<PB2[i]<<"\t\t"<<PB2.halfBox[i]<<"\t\t"<<PB2.edgeFlag[i]<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(PB2);
  COut<<Endl;

  COut<<"Test -- refer operation"<<Endl;
  refer(PB2,PB);
  for(unsigned int i=0;i<PB2.size;++i)
    COut<<PB2[i]<<"\t\t"<<PB2.halfBox[i]<<"\t\t"<<PB2.edgeFlag[i]<<Endl;
  COut<<Endl;

  COut<<"Test -- check whether it is a geometry"<<Endl;
  COut<<IsGeometry(PB)<<Endl;
  COut<<IsGeometry(va)<<Endl;
  COut<<Endl;

  return 1;
}

