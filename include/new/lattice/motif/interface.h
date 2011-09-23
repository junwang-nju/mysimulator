
#ifndef _Lattice_Motif_Interfce_H_
#define _Lattice_Motif_Interfce_H_

#include "array/1d/interface.h"
#include "lattice/shape/coordinate-type.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeMotif {

    public:

      typedef LatticeMotif<LSN,Dim>   Type;

      static const LatticeShapeName   Name;
      static const unsigned int Dimension;

      Array1D<unsigned char> bond;
      Array1D<typename LatticeCoordinate<LSN,Dim>::Type>  coordinate;

      LatticeMotif() : bond(), coordinate() {}
      ~LatticeMotif() { clearData(); }

      void clearData(){ release(coordinate); release(bond); }
      bool isvalid() const { return IsValid(bond)&&IsValid(coordinate); }

    private:

      LatticeMotif(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LatticeShapeName LSN, unsigned int Dim>
  const LatticeShapeName LatticeMotif<LSN,Dim>::Name=LSN;

  template <LatticeShapeName LSN, unsigned int Dim>
  const unsigned int LatticeMotif<LSN,Dim>::Dimension=Dim;

  template <LatticeShapeName LSN, unsigned int Dim>
  bool IsValid(const LatticeMotif<LSN,Dim>& M) { return M.isvalid(); }

  template <LatticeShapeName LSN, unsigned int Dim>
  void release(LatticeMotif<LSN,Dim>& M) { M.clearData(); }

}

#endif

