
#ifndef _Lattice_Motif_Import_H_
#define _Lattice_Motif_Import_H_

#include "lattice/motif/allocate.h"
#include "array/1d/copy.h"
#include "lattice/shape/create-neighbor.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void _update_coordinate(LatticeMotif& M) { Error("Unknown Shape with Dim!"); }

  template <>
  void _update_coordinate<SquareLattice,2U>(LatticeMotif& M) {
    int coor[2];
    coor[0]=coor[1]=0;
    for(unsigned int i=0;i<M.bond.size;++i) {
      createNeighbor<SquareLattice,2>(coor,M.bond[i]);
      M.coordinate[i][0]=coor[0];
      M.coordinate[i][1]=coor[1];
    }
  }

  template <LatticeShapeName LSN, unsigned int Dim>
  void import(LatticeMotif& M, const Array1DContent<unsigned short>& bd) {
    release(M);
    allocate(M,LSN,bd.size,Dim);
    copy(M.bond,bd);
    _update_coordinate<LSN,Dim>(M);
  }

}

#endif

