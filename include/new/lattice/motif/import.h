
#ifndef _Lattice_Motif_Import_H_
#define _Lattice_Motif_Import_H_

#include "lattice/motif/allocate.h"
#include "array/1d/copy.h"
#include "lattice/shape/create-neighbor.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void _update_coordinate(LatticeMotif<LSN,Dim>& M) {
    Error("Unknown Shape with Dim!");
  }

  template <>
  void _update_coordinate(LatticeMotif<SquareLattice,2U>& M) {
    Square2DCoordinateType coor;
    coor.us=0;
    for(unsigned int i=0;i<M.bond.size;++i) {
      createNeighbor<SquareLattice,2U>(coor,M.bond[i]);
      M.coordinate[i].us=coor.us;
    }
  }

  template <LatticeShapeName LSN, unsigned int Dim>
  void import(LatticeMotif<LSN,Dim>& M,const Array1DContent<unsigned char>& bd){
    release(M);
    allocate(M,bd.size);
    copy(M.bond,bd);
    _update_coordinate(M);
  }

}

#endif

