
#include "minimizer/line/import.h"
#include "minimizer/line/copy.h"

#include "interaction/kernel/allocate.h"
#include "interaction/kernel/copy.h"

#include "interaction/func/generic/allocate.h"
#include "interaction/func/generic/copy.h"

#include "buffer/distance/simple/allocate.h"
#include "buffer/distance/simple/copy.h"

#include "boundary/free/allocate.h"
#include "boundary/free/copy.h"

#include "interaction/parameter/unit/allocate.h"
#include "interaction/parameter/unit/copy.h"

#include "list/allocate.h"
#include "list/copy.h"
#include "list/fill.h"

#include "vector/dot.h"
#include "list/scale.h"
#include "interaction/calc.h"
#include "geometry/distance/dbuffer-simple/calc.h"
#include "geometry/displacement/free/calc.h"

#include "functional/harmonic/parameter/build.h"
#include "vector/norm.h"
#include "minimizer/base/produce.h"
#include "list/io.h"

using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  typedef InteractionFuncGeneric<SimpleDistanceBuffer,FreeSpace,double> IFType;
  typedef InteractionKernel<IFType,SimpleDistanceBuffer,FreeSpace,double>
          IKType;
  typedef Vector<InteractionParameterUnit>  IPType;
  LineMinimizer<TrackingMethod,IKType,List,IPType,double> LM;

  const unsigned int NUnit=4;
  const unsigned int Dim=2;
  const unsigned int NPrm=6;
  List<double> X;
  Vector<unsigned int> sz;
  List<unsigned int> Msk;
  allocate(sz,NUnit);
  fill(sz,Dim);
  allocate(X,sz);
  allocate(Msk,sz);
  fill(X,0.);
  X[1][0]=1.2;
  X[2][0]=2.3;    X[2][1]=1.5;
  X[3][0]=-1.5;   X[3][1]=0.7;
  fill(Msk,1U);

  import(LM,static_cast<const IKType*>(NULL),&X,static_cast<const IPType*>(NULL),&Msk);
  allocate(LM.MinFunc,Harmonic,NUnit,Dim);
  allocate(LM.MinP,NPrm);
  for(unsigned int i=0;i<NPrm;++i)    allocate(LM.MinP[i],Harmonic);
  LM.MinP[0].idx[0]=0;    LM.MinP[0].idx[1]=1;
  LM.MinP[0].prm[HarmonicEqLength].value<double>()=0.8;
  LM.MinP[0].prm[HarmonicEqStrength].value<double>()=100.;
  LM.MinP[1].idx[0]=0;    LM.MinP[1].idx[1]=2;
  LM.MinP[1].prm[HarmonicEqLength].value<double>()=0.5;
  LM.MinP[1].prm[HarmonicEqStrength].value<double>()=100.;
  LM.MinP[2].idx[0]=0;    LM.MinP[2].idx[1]=3;
  LM.MinP[2].prm[HarmonicEqLength].value<double>()=0.9;
  LM.MinP[2].prm[HarmonicEqStrength].value<double>()=10.;
  LM.MinP[3].idx[0]=1;    LM.MinP[3].idx[1]=2;
  LM.MinP[3].prm[HarmonicEqLength].value<double>()=1.2;
  LM.MinP[3].prm[HarmonicEqStrength].value<double>()=20.;
  LM.MinP[4].idx[0]=1;    LM.MinP[4].idx[1]=3;
  LM.MinP[4].prm[HarmonicEqLength].value<double>()=0.7;
  LM.MinP[4].prm[HarmonicEqStrength].value<double>()=200.;
  LM.MinP[5].idx[0]=2;    LM.MinP[5].idx[1]=3;
  LM.MinP[5].prm[HarmonicEqLength].value<double>()=1.2;
  LM.MinP[5].prm[HarmonicEqStrength].value<double>()=50.;
  for(unsigned int i=0;i<NPrm;++i)
    BuildParameterHarmonic<double>(LM.MinP[i].prm);

  LM.LineDirc[0][0]=0;    LM.LineDirc[0][1]=1.;
  LM.LineDirc[1][0]=1;    LM.LineDirc[1][1]=0.;
  LM.LineDirc[2][0]=0;    LM.LineDirc[2][1]=1.;
  LM.LineDirc[3][0]=1;    LM.LineDirc[3][1]=1.;
  double d;
  d=norm(LM.LineDirc);
  scale(LM.LineDirc,-1./d);
  ProduceNew(LM,LM.MinX(),LM.LineDirc,0.,LM.MinX(),LM.MinEnergy,LM.MinG(),LM.MinProject);
  cout<<LM.MinProject<<endl;

  LM.SetCondition(StrongWolfe);
  COut<<LM.MinX()<<Endl;
  COut<<LM.MinEnergy<<Endl;
  cout<<LM.Go(10000)<<endl;
  COut<<LM.MinX()<<Endl;
  COut<<LM.MinEnergy<<Endl;
  return 0;
}

