
#include "lattice/enumerate/square-2d/act.h"
#include "lattice/enumerate/square-2d/check/allocate.h"
#include "list/fill.h"
#include <cmath>
using namespace mysimulator;

#include <iostream>
using namespace std;

template <unsigned int L, unsigned int NC, unsigned int NW>
struct WallAdsorpOp : public LatticeEnumSquare2DProcessBase<L> {
  List<List<unsigned long long> > Hist;
  static const unsigned int CMin;
  static const unsigned int CMax;
  static const unsigned int NCenter;
  static const unsigned int GMin;
  static const unsigned int GMax;
  static const unsigned int NGyr;
  WallAdsorpOp() : Hist() {
    Vector<unsigned int> sz(NCenter);
    fill(sz,NGyr);
    allocate(Hist,sz);
    allocate(sz,NC+1);
    fill(sz,NW+1);
    for(unsigned int i=0;i<NCenter;++i)
    for(unsigned int j=0;j<NGyr;++j) allocate(Hist[i][j],sz);
    fill(Hist,0ULL);
  }
  virtual void operator()(const LatticeEnumSquare2DRunData<L>& Data) {
    int maxX,minX,maxY,minY;
    unsigned int NmaxX,NmaxY,NminX,NminY;
    unsigned int NmaxXC,NmaxYC,NminXC,NminYC;
    double cX,cY,gX,gY;
    maxX=minX=Data.Loc[0][0];
    maxY=minY=Data.Loc[0][1];
    NmaxX=NmaxY=NminX=NminY=1;
    cX=Data.Loc[0][0];
    cY=Data.Loc[0][1];
    gX=cX*cX;
    gY=cY*cY;
    NmaxXC=NmaxYC=NminXC=NminYC=1;
    for(unsigned int i=1;i<L;++i) {
      if(maxX<Data.Loc[i][0]) { maxX=Data.Loc[i][0]; NmaxX=1; if(i<4) NmaxXC=1; }
      else if(maxX==Data.Loc[i][0]) { NmaxX++; if(i<4) NmaxXC++; }
      if(minX>Data.Loc[i][0]) { minX=Data.Loc[i][0]; NminX=1; if(i<4) NminXC=1; }
      else if(minX==Data.Loc[i][0]) { NminX++; if(i<4) NminXC++; }
      if(maxY<Data.Loc[i][1]) { maxY=Data.Loc[i][1]; NmaxY=1; if(i<4) NmaxYC=1; }
      else if(maxY==Data.Loc[i][1]) { NmaxY++; if(i<4) NmaxYC++; }
      if(minY>Data.Loc[i][1]) { minY=Data.Loc[i][1]; NminY=1; if(i<4) NminYC=1; }
      else if(minY==Data.Loc[i][1]) { NminY++; if(i<4) NminYC++; }
      cX+=Data.Loc[i][0];
      cY+=Data.Loc[i][1];
      gX+=Data.Loc[i][0]*Data.Loc[i][0];
      gY+=Data.Loc[i][1]*Data.Loc[i][1];
    }
    cX/=(L+0.);
    cY/=(L+0.);
    gX/=(L+0.);
    gY/=(L+0.);
    gX-=cX*cX;
    gY-=cY*cY;
    double gR;
    gR=sqrt(gX+gY);
    unsigned int cXI,cYI,gI;
    cXI=static_cast<unsigned int>((cX+0.05)/0.1);
    cYI=static_cast<unsigned int>((cY+0.05)/0.1);
    gI=static_cast<unsigned int>((gR+0.01)/0.02);
    //cout<<cX<<"\t"<<cY<<endl;
    //cout<<maxX<<"\t"<<minX<<endl;
    //cout<<maxY<<"\t"<<minY<<endl;
    //cout<<cXI<<"\t"<<cYI<<endl;getchar();
    static const unsigned int CA[6]={0,1,2,4,5,6};
    static const unsigned int CB[6]={7,6,5,11,10,9};
    unsigned int E;
    E=0;
    for(unsigned int i=0;i<6;++i)
      if(abs(Data.Loc[CA[i]][0]-Data.Loc[CB[i]][0])+abs(Data.Loc[CA[i]][1]-Data.Loc[CB[i]][1])==1)
        E++;
    if((maxX==minX)||(maxY==minY)) {
      Hist[cXI-minX*10][gI][E][NminXC]++;
      for(unsigned int i=1;i<=30U-(maxX-minX);++i) Hist[cXI-minX*10+i*10][gI][E][0]++;
      Hist[maxX*10-cXI][gI][E][NmaxXC]++;
      for(unsigned int i=1;i<=30U-(maxX-minX);++i) Hist[maxX*10-cXI+i*10][gI][E][0]++;
      //cout<<gYI<<"\t"<<E<<"\t"<<NminYC<<endl;
      //cout<<cYI-minY*10<<endl;getchar();
      Hist[cYI-minY*10][gI][E][NminYC]++;
      //cout<<Hist[cYI-minY*10][gYI][E][NminYC]<<endl;getchar();
      for(unsigned int i=1;i<=30U-(maxY-minY);++i) Hist[cYI-minY*10+i*10][gI][E][0]++;
      Hist[maxY*10-cYI][gI][E][NmaxYC]++;
      for(unsigned int i=1;i<=30U-(maxY-minY);++i) Hist[maxY*10-cYI+i*10][gI][E][0]++;
    } else {
      Hist[cXI-minX*10][gI][E][NminXC]+=2;
      for(unsigned int i=1;i<=30U-(maxX-minX);++i) Hist[cXI-minX*10+i*10][gI][E][0]+=2;
      Hist[maxX*10-cXI][gI][E][NmaxXC]+=2;
      for(unsigned int i=1;i<=30U-(maxX-minX);++i) Hist[maxX*10-cXI+i*10][gI][E][0]+=2;
      Hist[cYI-minY*10][gI][E][NminYC]+=2;
      for(unsigned int i=1;i<=30U-(maxY-minY);++i) Hist[cYI-minY*10+i*10][gI][E][0]+=2;
      Hist[maxY*10-cYI][gI][E][NmaxYC]+=2;
      for(unsigned int i=1;i<=30U-(maxY-minY);++i) Hist[maxY*10-cYI+i*10][gI][E][0]+=2;
    }
  }
};

template <unsigned int L, unsigned int NC, unsigned int NW>
const unsigned int WallAdsorpOp<L,NC,NW>::CMin=0;
template <unsigned int L, unsigned int NC, unsigned int NW>
const unsigned int WallAdsorpOp<L,NC,NW>::CMax=30;
template <unsigned int L, unsigned int NC, unsigned int NW>
const unsigned int WallAdsorpOp<L,NC,NW>::NCenter=static_cast<unsigned int>((WallAdsorpOp<L,NC,NW>::CMax-WallAdsorpOp<L,NC,NW>::CMin)/0.1)+1;
template <unsigned int L, unsigned int NC, unsigned int NW>
const unsigned int WallAdsorpOp<L,NC,NW>::GMin=0;
template <unsigned int L, unsigned int NC, unsigned int NW>
const unsigned int WallAdsorpOp<L,NC,NW>::GMax=(L+1)/2;
template <unsigned int L, unsigned int NC, unsigned int NW>
const unsigned int WallAdsorpOp<L,NC,NW>::NGyr=static_cast<unsigned int>((WallAdsorpOp<L,NC,NW>::GMax-WallAdsorpOp<L,NC,NW>::GMin)/0.02)+1;

int main() {
  const unsigned int L=24;
  LatticeLibrary<SquareLattice,2>::load("../../..");
  LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic> LEC;
  allocate(LEC);
  WallAdsorpOp<L,6,4> OP;
  enumerate<L>(LEC,OP);
  /*
  for(unsigned int i=0;i<OP.NCenter;++i)
  for(unsigned int j=0;j<OP.NGyr;++j)
  for(unsigned int k=0;k<6+1;++k)
  for(unsigned int l=0;l<4+1;++l)
    if(OP.Hist[i][j][k][l]!=0)
      cout<<i*0.1<<"\t"<<j*0.02<<"\t"<<k<<"\t"<<l<<"\t"<<OP.Hist[i][j][k][l]<<endl;
  */
  double EW=1,EC=1,F;
  for(unsigned int i=0;i<OP.NCenter;++i) {
    F=0;
    for(unsigned int j=0;j<OP.NGyr;++j)
    for(unsigned int k=0;k<6+1;++k)
    for(unsigned int l=0;l<4+1;++l)
      F+=exp(k*EC+l*EW)*OP.Hist[i][j][k][l];
    if(F>1e-8)
      cout<<i*0.1<<"\t"<<log(F)<<endl;
      //cout<<i*0.1<<"\t"<<j*0.02<<"\t"<<log(F)<<endl;
  }
  return 0;
}

