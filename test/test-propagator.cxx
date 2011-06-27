
#include "propagator/monomer/allocate.h"
#include "propagator/subsystem/allocate.h"
#include "propagator/base/allocate.h"
#include "propagator/md/allocate.h"
#include "propagator/run.h"

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
#include "geometry/distance/dbuffer-simple/calc.h"
#include "geometry/displacement/free/calc.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  typedef InteractionFuncGeneric<SimpleDistanceBuffer,FreeSpace,double> IFType;
  MDPropagator<double,SimpleDistanceBuffer,FreeSpace,IFType,
               Vector<InteractionParameterUnit> > P;
  return 0;
}

