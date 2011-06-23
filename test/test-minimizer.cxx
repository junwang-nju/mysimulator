
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

#include "list/copy.h"
#include "list/fill.h"

#include "vector/dot.h"
#include "list/allocate.h"
#include "interaction/calc.h"
#include "geometry/distance/dbuffer-simple/calc.h"
#include "geometry/displacement/free/calc.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  typedef InteractionFuncGeneric<SimpleDistanceBuffer,FreeSpace,double> IFType;
  typedef InteractionKernel<IFType,SimpleDistanceBuffer,FreeSpace,double>
          IKType;
  typedef Vector<InteractionParameterUnit>  IPType;
  LineMinimizer<TrackingMethod,IKType,List,IPType,double> LM;
  List<double> X;
  Vector<unsigned int> sz;
  List<unsigned int> Msk;
  allocate(sz,4);
  fill(sz,2U);
  allocate(X,sz);
  allocate(Msk,sz);
  fill(X,0.);
  fill(Msk,0U);
  import(LM,static_cast<const IKType*>(NULL),&X,static_cast<const IPType*>(NULL),&Msk);
  return 0;
}

