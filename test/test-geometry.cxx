
#include "geometry/displacement/free/calc.h"
#include "geometry/displacement/periodic-box/calc.h"
#include "geometry/distance/dbuffer-simple/calc.h"
#include "geometry/distance/dbuffer-pair/calc.h"
#include "boundary/periodic-box/allocate.h"
#include "boundary/periodic-box/set.h"
#include "buffer/distance/simple/allocate.h"
#include "buffer/distance/pair/allocate.h"
#include "vector/io.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  cout<<endl;
  Vector<double> va(5),vb(5),v(5);
  for(unsigned int i=0;i<5;++i) {
    va[i]=1+i*i;
    vb[i]=1+i;
  }
  DisplacementCalcDirect(va,vb,v);
  cout<<"Cacculate Displacement of double vector:\t";
  COut<<v<<Endl;
  Vector<float> fa(5),fb(5),f(5);
  for(unsigned int i=0;i<5;++i) {
    fa[i]=1+i*i*i;
    fb[i]=1.-i;
  }
  DisplacementCalcDirect(fa,fb,f);
  cout<<"Cacculate Displacement of float vector:\t";
  COut<<f<<Endl;
  Vector<int> ia(5),ib(5),iv(5);
  for(unsigned int i=0;i<5;++i) {
    ia[i]=7*i+i*i*i;
    ib[i]=5.-i;
  }
  DisplacementCalcDirect(ia,ib,iv);
  cout<<"Cacculate Displacement of int vector:\t";
  COut<<iv<<Endl;

  cout<<endl;
  FreeSpace FS;
  DisplacementCalc(va,vb,v,FS);
  cout<<"Displacement of double vector in FreeSpace:\t";
  COut<<v<<Endl;

  cout<<endl;
  PeriodicBox<double> PB;
  allocate(PB,5);
  for(unsigned int i=0;i<5;++i) {
    v[i]=i+1.;
    iv[i]=1;
  }
  iv[1]=iv[3]=0;
  set(PB,v,iv);
  DisplacementCalc(va,vb,v,PB);
  cout<<"Displacement of double vector in Periodic-Box:\t";
  COut<<v<<Endl;

  cout<<endl;
  cout<<"Distance in FreeSpace is:\t";
  cout<<DistanceSqCalcDirect(va,vb,v,FS)<<endl;
  cout<<"Distance in Periodic-Box (without update) is:\t";
  cout<<DistanceSqCalcDirect(va,vb,v,PB)<<endl;

  cout<<endl;
  SimpleDistanceBuffer<double> SDB;
  allocate(SDB,5,4);
  cout<<"Distance in FreeSpace with simple buffer:\t";
  cout<<DistanceSqCalc(va,vb,0,1,FS,SDB)<<endl;
  cout<<"Distance in Periodic Box with simple buffer:\t";
  cout<<DistanceSqCalc(va,vb,0,1,PB,SDB)<<endl;

  cout<<endl;
  PairDistanceBuffer<double> PDB;
  allocate(PDB,5,4);
  cout<<"Distance in FreeSpace with pair buffer:\t";
  cout<<DistanceSqCalc(va,vb,0,1,FS,PDB)<<endl;
  cout<<"Distance in Periodic Box with pair buffer (without update):\t";
  cout<<DistanceSqCalc(va,vb,0,1,PB,PDB)<<endl;
  PDB.renew();
  cout<<"Distance in Periodic Box with pair buffer (after update):\t";
  cout<<DistanceSqCalc(va,vb,0,1,PB,PDB)<<endl;
  return 0;
}

