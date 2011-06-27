
#include "lattice/enumerate/square-2d/act.h"
#include "lattice/enumerate/square-2d/check/allocate.h"
#include "list/fill.h"
#include <cmath>
using namespace mysimulator;

#include <iostream>
using namespace std;

template <unsigned int L>
struct WallAdsorpOp : public LatticeEnumSquare2DProcessBase<L> {
  List<unsigned long long> Hist;
  static const double DMax;
  static const double DMin;
  WallAdsorpOp() : Hist() {
    Vector<unsigned int> sz;
    allocate(sz,9+1);
    fill(sz,5U);
    allocate(Hist,sz);
    fill(Hist,0ULL);
  }
  virtual void operator()(const LatticeEnumSquare2DRunData<L>& Data) {
    int maxX,minX,maxY,minY;
    unsigned int NmaxX,NmaxY,NminX,NminY;
    unsigned int NmaxXC,NmaxYC,NminXC,NminYC;
    double cX,cY;
    maxX=minX=Data.Loc[0][0];
    maxY=minY=Data.Loc[0][1];
    NmaxX=NmaxY=NminX=NminY=1;
    NmaxXC=NmaxYC=NminXC=NminYC=1;
    cX=Data.Loc[0][0];
    cY=Data.Loc[0][1];
    for(unsigned int i=1;i<L;++i) {
      if(maxX<Data.Loc[i][0]){ maxX=Data.Loc[i][0]; NmaxX=1; if(i<4) NmaxXC=1; }
      else if(maxX==Data.Loc[i][0]) { NmaxX++; if(i<5) NmaxXC++; }
      if(minX>Data.Loc[i][0]){ minX=Data.Loc[i][0]; NminX=1; if(i<4) NminXC=1; }
      else if(minX==Data.Loc[i][0]) { NminX++; if(i<5) NminXC++; }
      if(maxY<Data.Loc[i][1]){ maxY=Data.Loc[i][1]; NmaxY=1; if(i<4) NmaxYC=1; }
      else if(maxY==Data.Loc[i][1]) { NmaxY++; if(i<5) NmaxYC++; }
      if(minY>Data.Loc[i][1]){ minY=Data.Loc[i][1]; NminY=1; if(i<4) NminYC=1; }
      else if(minY==Data.Loc[i][1]) { NminY++; if(i<5) NminYC++; }
      cX+=Data.Loc[i][0];
      cY+=Data.Loc[i][1];
    }
    cX/=(L+0.);
    cY/=(L+0.);
    static const unsigned int CA[9]={0,1,2, 4, 5,6, 8, 9,10};
    static const unsigned int CB[9]={7,6,5,11,10,9,15,14,13};
    unsigned int E,nAdd;
    double nF;
    E=0;
    for(unsigned int i=0;i<9;++i)
      if(abs(Data.Loc[CA[i]][0]-Data.Loc[CB[i]][0])+
         abs(Data.Loc[CA[i]][1]-Data.Loc[CB[i]][1])==1)   E++;
    if((maxX==minX)||(maxY==minY))  nAdd=1;
    else                            nAdd=2;
    if(cX-minX>DMin-1e-8)  { Hist[E][NminXC]+=nAdd; nF=cX-minX+1; }
    else nF=DMin;
    nF=DMax+1e-8-nF;
    if(nF<0)  nF=0;
    Hist[E][0]+=static_cast<unsigned long long>(nF)*nAdd;
    if(maxX-cX>DMin-1e-8)  { Hist[E][NmaxXC]+=nAdd; nF=maxX-cX+1; }
    else nF=DMin;
    nF=DMax+1e-8-nF;
    if(nF<0)  nF=0;
    Hist[E][0]+=static_cast<unsigned long long>(nF)*nAdd;
  }
};

template <unsigned int L>
const double WallAdsorpOp<L>::DMin=5;
template <unsigned int L>
const double WallAdsorpOp<L>::DMax=7;

int main() {
  const unsigned int L=16;
  LatticeLibrary<SquareLattice,2>::load("../../..");
  LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic> LEC;
  allocate(LEC);
  WallAdsorpOp<L> OP;
  enumerate<L>(LEC,OP);
  for(unsigned int i=0;i<=9;++i)
    cout<<i<<"\t"<<OP.Hist[i][0]<<endl;
  return 0;
}

