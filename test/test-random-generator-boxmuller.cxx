
#include "random-generator-interface.h"
#include "random-generator-boxmuller.h"
#include "random-generator-mt-dsfmt.h"
using namespace std;

int main() {
  typedef RandGenerator<dSFMT<216091>,double> UniformDbRNG;
  typedef RandGenerator<BoxMuller<UniformDbRNG>,double> GaussianRNG;

  return 1;
}

