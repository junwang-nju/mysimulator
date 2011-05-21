
#ifndef _Lattice_Library_Interface_H_
#define _Lattice_Library_Interface_H_

#include "lattice/motif/build.h"
#include "lattice/motif/allocate.h"
#include "list/allocate.h"
#include "vector/scale.h"
#include "vector/fill.h"
#include "io/input/file/interface.h"
#include "vector/io.h"
#include "lattice/shape-name.h"

namespace mysimulator {

  template <LatticeShapeName LShape, unsigned int Dimension>
  struct LatticeLibrary {

    typedef LatticeLibrary<LShape,Dimension> Type;

    static const unsigned int MaxBondOfMotif;
    static const unsigned int NumNeighbors;
    static const unsigned int NumShifts;
    static const char         relLocation[1024];

    static List<unsigned short> shiftLoc;
    static List<LatticeMotif> map;

    LatticeLibrary() {}
    LatticeLibrary(const Type&) { Error("Copier of LatticeLibrary Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeLibrary Disabled!");
      return *this;
    }
    ~LatticeLibrary() { clearData(); }

    void clearData() { release(shiftLoc); release(map); }
    static void load(const char* Root) {
      if(IsValid(shiftLoc)&&IsValid(map))   return;
      static char tmbuffer[1024];
      sprintf(tmbuffer,"%s/%s/",Root,relLocation);
      _read(tmbuffer);
    }

    static void _read(const char* fnTemplate) {
      static char nmbuffer[1024],nmbuffer1[1024];
      Vector<unsigned int> sz;
      allocate(sz,MaxBondOfMotif);
      fill(sz,NumShifts);
      allocate(shiftLoc,sz);
      FileInput ifs;
      sprintf(nmbuffer,"%s-library",fnTemplate);
      ifs.open(nmbuffer);
      for(unsigned int i=0;i<MaxBondOfMotif;++i) {
        ifs>>shiftLoc[i]>>nmbuffer;
        sz[i]=shiftLoc[i][NumShifts-1];
      }
      ifs.close();
      allocate(map,sz);
      for(unsigned int i=0;i<MaxBondOfMotif;++i)
      for(unsigned int k=0;k<map[i].size;++k)
        allocate(map[i][k],i+1,Dimension);
      FileInput ifs1;
      sprintf(nmbuffer,"%s-library",fnTemplate);
      ifs.open(nmbuffer);
      for(unsigned int i=0;i<MaxBondOfMotif;++i) {
        ifs>>shiftLoc[i]>>nmbuffer1;
        sprintf(nmbuffer,"%s%s",fnTemplate,nmbuffer1);
        ifs1.open(nmbuffer);
        for(unsigned int k=0;k<map[i].size;++k) {
          ifs1>>map[i][k].bond;
          build<LShape,Dimension>(map[i][k]);
        }
        ifs1.close();
      }
      ifs.close();
    }

  };

  template <LatticeShapeName LS, unsigned int Dim>
  const unsigned int LatticeLibrary<LS,Dim>::MaxBondOfMotif=0;
  template <LatticeShapeName LS, unsigned int Dim>
  const unsigned int LatticeLibrary<LS,Dim>::NumNeighbors=0;
  template <LatticeShapeName LS, unsigned int Dim>
  const unsigned int LatticeLibrary<LS,Dim>::NumShifts=0;
  template <LatticeShapeName LS, unsigned int Dim>
  const char LatticeLibrary<LS,Dim>::relLocation[1024]="";

  template <LatticeShapeName LS, unsigned int Dim>
  List<unsigned short> LatticeLibrary<LS,Dim>::shiftLoc;
  template <LatticeShapeName LS, unsigned int Dim>
  List<LatticeMotif> LatticeLibrary<LS,Dim>::map;

  template <LatticeShapeName LS, unsigned int Dim>
  bool IsValid(const LatticeLibrary<LS,Dim>& L) {
    return IsValid(L.shiftLoc)&&IsValid(L.map);
  }

  template <LatticeShapeName LS, unsigned int Dim>
  void release(LatticeLibrary<LS,Dim>& L) { L.clearData(); }

}

#include "lattice/library/square-2d/specification.h"

#endif

