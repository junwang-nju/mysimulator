
#include "lattice/enumerate/square-2d/act.h"
#include "lattice/enumerate/square-2d/check/allocate.h"
#include "vector/copy.h"
#include "vector/fill.h"
#include "vector/shift.h"
#include "io/output/file/interface.h"
#include "io/input/file/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  const unsigned int L=20;
  LatticeLibrary<SquareLattice,2>::load("../../..");
  LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic> LEC;
  allocate(LEC);
  FileOutput FO;
  FO.open("plane.tmp");
  enumerate<L>(LEC,FO);
  FO.close();
  unsigned int n,m;
  int maxX,minX,maxY,minY;
  double mcX,mcY;
  Vector<unsigned long long> NE,NC;
  allocate(NE,L+1);
  allocate(NC,L+1);
  fill(NE,0ULL);
  fill(NC,0ULL);
  unsigned int cntMaxX,cntMinX,cntMaxY,cntMinY;
  List<int> coor;
  Vector<unsigned int> sz(L);
  fill(sz,2U);
  allocate(coor,sz);
  FileInput FI;
  LatticeMotifChain<SquareLattice,2,L>  C;
  allocate(C);
  FI.open("plane.tmp");
  while(true) {
    FI>>C;
    if(IsFailed(FI))  break;
    coor[0][0]=coor[0][1]=0;
    n=0;
    for(unsigned int i=0;i<C.NumMotifs-1;++i) {
      m=n+LatticeLibrary<SquareLattice,2>::MaxBondOfMotif;
      for(unsigned int k=n+1;k<=m;++k){
        copy(coor[k],coor[n]);
        shift(coor[k],C.bondVec(k-1));
      }
      n=m;
    }
    m=n+C.NumBondsLastMotif;
    for(unsigned int k=n+1;k<=m;++k) {
        copy(coor[k],coor[n]);
        shift(coor[k],C.bondVec(k-1));
    }
    maxX=maxY=minX=minY=0;
    cntMaxX=cntMinX=cntMaxY=cntMinY=1;
    mcX=mcY=0;
    for(unsigned int i=1;i<L;++i) {
      if(maxX<coor[i][0]) { maxX=coor[i][0]; cntMaxX=1; }
      else if(maxX==coor[i][0]) cntMaxX++;
      if(minX>coor[i][0]) { minX=coor[i][0]; cntMinX=1; }
      else if(minX==coor[i][0]) cntMinX++;
      if(maxY<coor[i][1]) { maxY=coor[i][1]; cntMaxY=1; }
      else if(maxY==coor[i][1]) cntMaxY++;
      if(minY>coor[i][1]) { minY=coor[i][1]; cntMinY=1; }
      else if(minY==coor[i][1]) cntMinY++;
      mcX+=coor[i][0];
      mcY+=coor[i][1];
    }
    mcX/=(L+0.);
    mcY/=(L+0.);
    if((maxX==minX)||(maxY==minY)) {
      NE[cntMaxX]++; NE[cntMinX]++;
      NE[cntMaxY]++; NE[cntMinY]++;
      NC[(int)(mcX-minX)]++;
      NC[(int)(maxX-mcX)]++;
      NC[(int)(mcY-minY)]++;
      NC[(int)(maxY-mcY)]++;
    } else {
      NE[cntMaxX]+=2;    NE[cntMinX]+=2;
      NE[cntMaxY]+=2;    NE[cntMinY]+=2;
      NC[(int)(mcX-minX)]+=2;
      NC[(int)(maxX-mcX)]+=2;
      NC[(int)(mcY-minY)]+=2;
      NC[(int)(maxY-mcY)]+=2;
    }
  }
  FI.close();
  for(unsigned int i=0;i<NE.size;++i)
    cout<<i<<"\t"<<NE[i]<<"\t"<<NC[i]<<endl;
  return 0;
}
