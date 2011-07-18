
#include "lattice/enumerate/square-2d/act.h"
#include "lattice/enumerate/square-2d/check/allocate.h"
#include "lattice/enumerate/square-2d/process/interface.h"
#include "list/copy.h"
#include <cmath>
using namespace mysimulator;

#include <iostream>
using namespace std;

template <unsigned int L>
struct WallAdsorpOp : public LatticeEnumSquare2DProcessBase<L> {
  typedef WallAdsorpOp<L>   Type;
  typedef LatticeEnumSquare2DProcessBase<L> ParentType;

  unsigned long long NE[L+1][100];
  List<int> Pos;
  WallAdsorpOp() {
    for(unsigned int i=0;i<=L;++i)
    for(unsigned int k=0;k<100;++k)
      NE[i][k]=0;
    Vector<unsigned int> sz;
    allocate(sz,L);
    fill(sz,2U);
    allocate(Pos,sz);
  }
  ~WallAdsorpOp() { release(Pos); }

  virtual void operator()(const LatticeEnumSquare2DRunData<L>& Data) {
    for(unsigned int i=0;i<8U;++i) {
      for(unsigned int k=0;k<L;++k) {
        if(i<4) {
          copy(Pos[k],Data.Loc[k]);
          if(i==0) {}
          else if(i==1)  Pos[k][1]*=-1;
          else {
            Pos[k][0]*=-1;
            if(i==3) Pos[k][1]*=-1;
          }
        } else {
          Pos[k][0]=Data.Loc[k][1];
          Pos[k][1]=Data.Loc[k][0];
          if(i==4) {}
          else if(i==5)  Pos[k][1]*=-1;
          else {
            Pos[k][0]*=-1;
            if(i==7)  Pos[k][1]*=-1;
          }
        }
      }
      double cx,cy,cd;
      cx=cy=0.;
      for(unsigned int k=0;k<L;++k) {
        cx+=Pos[k][0];
        cy+=Pos[k][1];
      }
      cx/=L;
      cy/=L;
      int px,py,e;
      bool fg;
      for(int gx=-30;gx<=31;++gx)
      for(int gy=-30;gy<=31;++gy) {
        e=0;
        fg=true;
        for(unsigned int k=0;k<L;++k) {
          px=Pos[k][0]+gx;
          py=Pos[k][1]+gy;
          if(px==0) {
            if((py==0)||(py==1))  { fg=false; break; }
            else if((py==-1)||(py==2))  e++;
          } else if(px==1) {
            if((py==0)||(py==1))  { fg=false; break; }
            else if((py==-1)||(py==2))  e++;
          } else if((px==-1)||(px==2)) {
            if((py==0)||(py==1))  e++;
          }
        }
        if(fg) {
          cd=sqrt((cx+gx-0.5)*(cx+gx-0.5)+(cy+gy-0.5)*(cy+gy-0.5));
          NE[e][(int)(cd)]++;
        }
      }
    }
  }

};

int main() {
  const unsigned int L=12;
  LatticeLibrary<SquareLattice,2>::load("../../..");
  LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic> LEC;
  allocate(LEC);
  WallAdsorpOp<L> OP;
  enumerate<L>(LEC,OP);
  for(unsigned int i=0;i<=L;++i)
  for(unsigned int k=0;k<100;++k)
    if(OP.NE[i][k]!=0)
      cout<<i<<"\t"<<k<<"\t"<<OP.NE[i][k]<<endl;
  return 0;
}

