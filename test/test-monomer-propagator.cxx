
#include "monomer-propagator.h"
#include <iostream>
using namespace std;

void move(double* x, double* v, const double* g, 
          const double* dm, const unsigned int n,
          const UniqueParameter* gp, UniqueParameter* p) {
}

void seti(UniqueParameter*, const void* i) { cout<<"Set I"<<endl; }

void setd(UniqueParameter*, const void* d) { cout<<"Set D"<<endl; }

void sync(const Vector<double>& v,
          const UniqueParameter* gp, UniqueParameter* p) {
  cout<<"In Sync"<<endl;
}

int main() {
  cout<<"Test -- initialize"<<endl;
  MonomerPropagator MP;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(MP);
  *(MP.UnitKind)=1;
  *(MP.MoveMode)=2;
  allocate(MP.Move,3);
  for(unsigned int i=0;i<3;++i) MP.Move[i]=move;
  allocate(MP.MSet,2);
  MP.MSet[0]=seti;
  MP.MSet[1]=setd;
  allocate(MP.MParam,5);
  for(unsigned int i=0;i<3;++i) MP.MParam[i]=i;
  for(unsigned int i=3;i<5;++i) MP.MParam[i]=(i*1.);
  MP.MSync=sync;
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  MonomerPropagator MP2;
  allocate(MP2);
  *(MP2.UnitKind)=2;
  *(MP2.MoveMode)=1;
  assign(MP2,MP);
  cout<<MP2.Move.size<<endl;
  cout<<MP2.MSet.size<<endl;
  cout<<MP2.MParam.size<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(MP2);
  cout<<endl;

  cout<<"Test -- check availability"<<endl;
  cout<<IsAvailable(MP)<<endl;
  cout<<IsAvailable(MP2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(MP2,MP);
  cout<<endl;

  cout<<"Test -- synchronize"<<endl;
  Vector<double> iM;
  UniqueParameter* gp=NULL;
  synchronize(MP2,iM,gp);
  cout<<endl;

  cout<<"Test -- set parameter"<<endl;
  setparameter(MP,0,1);
  setparameter(MP2,1,1.2);
  cout<<endl;

  return 0;
}

