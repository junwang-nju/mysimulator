
#include "operation/parameter/interaction-parameter-neighbor-list-op.h"
#include "operation/interaction/calc.h"
#include "operation/parameter/build-param-lj612cut.h"
#include "operation/geometry/displacement-calc-freespace.h"
using namespace std;

int main() {
  ParameterWNeighborList<Vector,double> P;
  allocate(P.possibleParameter,15);
  for(unsigned int i=0;i<15;++i) {
    allocate(P.possibleParameter[i],LJ612Cut);
    P.possibleParameter[i].prm[LJ612CutEqRadius].d=1.;
    P.possibleParameter[i].prm[LJ612CutEqEnergyDepth].d=1.;
    P.possibleParameter[i].prm[LJ612CutCutR].d=2.;
    BuildParameterLJ612Cut<double>(P.possibleParameter[i].prm);
  }
  for(unsigned int i=0,n=0;i<6;++i)
  for(unsigned int j=i+1;j<6;++j,++n) {
    P.possibleParameter[n].idx[0]=i;
    P.possibleParameter[n].idx[1]=j;
  }
  
  PropertyList<double> X,G;
  Vector<unsigned int> sz;
  allocate(sz,6);
  copy(sz,2);
  allocate(X,sz);
  allocate(G,sz);

  X[0][0]=0;      X[0][1]=0;
  X[1][0]=0;      X[1][1]=2.5;
  X[2][0]=0;      X[2][1]=5;
  X[3][0]=1.5;    X[3][1]=0;
  X[4][0]=1.5;    X[4][1]=2.5;
  X[5][0]=1.5;    X[5][1]=5;

  FreeSpace FS;

  init(P,X,2.,1.,FS);
  cout<<P.size<<endl;
  for(unsigned int i=0;i<P.size;++i)
    cout<<P[i].idx[0]<<"\t"<<P[i].idx[1]<<endl;

  cout<<endl;
  X[1][0]=3.;
  update(P,X.structure,FS);
  cout<<P.size<<endl;
  for(unsigned int i=0;i<P.size;++i)
    cout<<P[i].idx[0]<<"\t"<<P[i].idx[1]<<endl;

  return 1;
}

