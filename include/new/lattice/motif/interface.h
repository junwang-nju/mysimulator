
#ifndef _Lattice_Motif_Interfce_H_
#define _Lattice_Motif_Interfce_H_

#include "array/1d/interface.h"
#include "array/2d/interface.h"
#include "lattice/shape/name.h"

namespace mysimulator {

  struct LatticeMotif {

    public:

      typedef LatticeMotif    Type;

      LatticeShapeName  name;
      Array1D<unsigned short> bond;
      Array2D<int>  coordinate;

      LatticeMotif() : name(UnknownShape), bond(), coordinate() {}
      ~LatticeMotif() { clearData(); }

      void clearData(){ name=UnknownShape; release(bond); release(coordinate); }
      bool isvalid() const {
        return (name!=UnknownShape)&&IsValid(bond)&&IsValid(coordinate);
      }

      const unsigned int Dimension() const {
        assert(IsValid(coordinate));
        return coordinate[0].size;
      }

    private:

      LatticeMotif(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const LatticeMotif& M) { return M.isvalid(); }
  void release(LatticeMotif& M) { M.clearData(); }

}

#endif

