
#include "operation/parameter/build-param-propagator-vverlet.h"
#include "operation/parameter/propagator-op.h"
#include "operation/interaction/calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
using namespace std;

int main() {
  Propagator<double> P;
  Vector<unsigned int> enstype;
  Vector<Vector<unsigned int> > mtype;
  allocate(enstype,1);
  allocate(mtype,1);
  allocate(mtype[0],4);
  enstype[0]=ConstantE;
  copy(mtype,ParticleType);
  allocate<Vector<InteractionParameterUnit>,ListInteraction,
           DistanceBufferSimple,FreeSpace>(P,VelocityVerlet,enstype,mtype);
  return 1;
}

