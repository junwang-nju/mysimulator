
#ifndef _Lattice_Motif_Interfce_H_
#define _Lattice_Motif_Interfce_H_

#include "array/1d/interface.h"
#include "array/2d/interface.h"

namespace mysimulator {

  struct LatticeMotif {

    public:

      typedef LatticeMotif    Type;

      Array1D<unsigned int> bond;
      Array2D<int>  coordinate;

    private:

      LatticeMotif(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

