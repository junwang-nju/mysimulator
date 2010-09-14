
#include "vector.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
  Vector<double> bl,bh;
  Vector<unsigned int> bI,bJ;

  const unsigned int Np=20768;
  allocate(bl,Np);
  allocate(bh,Np);
  allocate(bI,20768);
  allocate(bJ,20768);

  ifstream ifs;
  ifs.open("r1");
  for(unsigned int i=0;i<Np;++i)
    ifs>>bI[i]>>bJ[i]>>bl[i]>>bh[i];
  ifs.close();
  unsigned int Nc;
  Nc=0;
  for(unsigned int i=0;i<Np;++i) {
    if(bI[i]>Nc) { Nc=bI[i]; }
    if(bJ[i]>Nc) { Nc=bJ[i]; }
  }

  Vector<unsigned int> gstate;
  allocate(gstate,Nc);
  for(unsigned int i=0;i<Nc;++i)  gstate[i]=i;
  unsigned int minI,minJ,minop;
  double minBL,tBL;

  do{
    minI=minJ=0;
    minBL=1e10;
    minop=0;
    for(unsigned int i=0;i<Np;++i) {
      if(gstate[bI[i]]==gstate[bJ[i]])  continue;
      tBL=bl[i];
      if(minBL>tBL) {
        minBL=tBL;
        minI=gstate[bI[i]];
        minJ=gstate[bJ[i]];
        minop++;
      }
    }
    if(minop>0) {
      cout<<minI<<"\t"<<minJ<<"\t"<<minBL<<endl;
      if(minI>minJ) swap(minI,minJ);
      for(unsigned int u=0;u<Nc;++u)
        if(gstate[u]==minJ) { gstate[u]=minI; }
    }
  } while(minop>0);
  return 0;
}

