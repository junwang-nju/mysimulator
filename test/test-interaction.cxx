

#include "interaction/func/interface.h"
#include "buffer/distance/simple/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  InteractionFunc<Harmonic,SimpleDistanceBuffer,FreeSpace>::Energy();
  return 0;
}

