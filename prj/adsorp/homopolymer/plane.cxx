
#include "lattice/enumerate/square-2d/act.h"
#include "lattice/enumerate/square-2d/check/allocate.h"
#include "lattice/enumerate/square-2d/process/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

template <unsigned int L>
struct WallAdsorpOp : public LatticeEnumSquare2DProcessBase<L> {
  typedef WallAdsorpOp<L>   Type;
  typedef LatticeEnumSquare2DProcessBase<L> ParentType;

  unsigned long long NE[L+1];
  WallAdsorpOp() {
    for(unsigned int i=0;i<=L;++i)  NE[i]=0;
  }
  virtual void operator()(const LatticeEnumSquare2DRunData<L>& Data) {
    int maxX,minX,maxY,minY;
    unsigned int NmaxX,NmaxY,NminX,NminY;
    maxX=minX=Data.Loc[0][0];
    maxY=minY=Data.Loc[0][1];
    NmaxX=NmaxY=NminX=NminY=1;
    for(unsigned int i=1;i<L;++i) {
      if(maxX<Data.Loc[i][0]) { maxX=Data.Loc[i][0]; NmaxX=1; }
      else if(maxX==Data.Loc[i][0]) NmaxX++;
      if(minX>Data.Loc[i][0]) { minX=Data.Loc[i][0]; NminX=1; }
      else if(minX==Data.Loc[i][0]) NminX++;
      if(maxY<Data.Loc[i][1]) { maxY=Data.Loc[i][1]; NmaxY=1; }
      else if(maxY==Data.Loc[i][1]) NmaxY++;
      if(minY>Data.Loc[i][1]) { minY=Data.Loc[i][1]; NminY=1; }
      else if(minY==Data.Loc[i][1]) NminY++;
    }
    if((maxX==minX)||(maxY==minY)) {
      NE[NmaxX]++; NE[NminX]++;
      NE[NmaxY]++; NE[NminY]++;
    } else {
      NE[NmaxX]+=2;    NE[NminX]+=2;
      NE[NmaxY]+=2;    NE[NminY]+=2;
    }
  }

};

int main() {
  const unsigned int L=20;
  LatticeLibrary<SquareLattice,2>::load("../../..");
  LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic> LEC;
  allocate(LEC);
  WallAdsorpOp<L> OP;
  enumerate<L>(LEC,OP);
  for(unsigned int i=0;i<=L;++i)
    cout<<i<<"\t"<<OP.NE[i]<<endl;
  return 0;
}

