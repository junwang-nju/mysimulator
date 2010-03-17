
#include "interaction-4list.h"
#include "var-property-list.h"
#include "interaction-method-op.h"
#include "var-distance-evaluate-direct.h"
#include "var-free-space.h"
#include <iostream>
using namespace std;

int main() {
  varPropertyList<double> CoorSeq;
  varVector<unsigned int> Sz(4);
  Sz=2;
  CoorSeq.allocate(Sz);
  InteractionMethod<DistanceEvalDirectBase,FreeSpaceBase> runIM;
  SetInteractionMethod(runIM,ParticleParticle_Harmonic);
  varPropertyList<double> IdxLst;
  Sz.allocate(6);
  Sz=2;
  IdxLst.allocate(Sz);
  IdxLst[0][0]=0;   IdxLst[0][1]=1;
  IdxLst[1][0]=0;   IdxLst[1][1]=2;
  IdxLst[2][0]=0;   IdxLst[2][1]=3;
  IdxLst[3][0]=1;   IdxLst[3][1]=2;
  IdxLst[4][0]=1;   IdxLst[4][1]=3;
  IdxLst[5][0]=2;   IdxLst[5][1]=3;
  varVector<unsigned int> KindSeq(4);
  KindSeq[0]=0;
  KindSeq[1]=1;
  KindSeq[2]=0;
  KindSeq[3]=2;
  return 1;
}

