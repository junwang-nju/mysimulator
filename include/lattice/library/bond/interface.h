
#ifndef _Lattice_Library_Bond_Base_Interface_H_
#define _Lattice_Library_Bond_Base_Interface_H_

#include "list/allocate.h"
#include "vector/scale.h"
#include "vector/copy.h"
#include "list/io.h"
#include "vector/allocate.h"
#include "io/input/file/interface.h"
#include "lattice/name.h"

namespace mysimulator {

  template <LatticeTypeName LatticeType, unsigned int Dimension>
  struct LatticeBondLib {

    typedef LatticeBondLib<LatticeType,Dimension>   Type;

    static const unsigned int MaxMotifs;
    static const unsigned int NumNeighbors;
    static const unsigned int NumberShifts;
    static List<unsigned int> shiftLoc;
    static Vector<List<unsigned int> >  map;
    static Vector<List<int> > coordinateMap;

    LatticeBondLib() {} 
    LatticeBondLib(const Type&) {
      Error("Copier of LatticeBondLib Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeBondLib Disabled!");
      return *this;
    }
    ~LatticeBondLib() { clearData(); }

    void load(const char* Root) { Error("Lattice Library Loading Disabled!"); }

    void clearData() {
      release(shiftLoc);
      release(map);
      release(coordinateMap);
    }
    void _read(const char* fTemplate) {
      Vector<unsigned int> sz;
      static char nmbuffer[1024];
      allocate(sz,MaxMotifs);
      copy(sz,NumberShifts);
      allocate(shiftLoc,sz);
      allocate(map,MaxMotifs);
      allocate(coordinateMap,MaxMotifs);
      FileInput ifs;
      unsigned int nmotif;
      for(unsigned int i=1;i<=MaxMotifs;++i) {
        sprintf(nmbuffer,"%s%d",fTemplate,i);
        ifs.open(nmbuffer);
        ifs>>shiftLoc[i];
        nmotif=shiftLoc[i][NumberShifts-1];
        allocate(sz,nmotif);
        copy(sz,i);
        allocate(map[i],sz);
        scale(sz,Dimension);
        allocate(coordinateMap[i],sz);
        for(unsigned int j=i-1,k=0;k<nmotif;++k)  ifs>>map[j][k];
        ifs.close();
      }
    }

  };

  template <LatticeTypeName LT, unsigned int Dim>
  const unsigned int LatticeBondLib<LT,Dim>::MaxMotifs=0;

  template <LatticeTypeName LT, unsigned int Dim>
  const unsigned int LatticeBondLib<LT,Dim>::NumNeighbors=0;

  template <LatticeTypeName LT, unsigned int Dim>
  const unsigned int LatticeBondLib<LT,Dim>::NumberShifts=0;

  template <LatticeTypeName LT, unsigned int Dim>
  List<unsigned int> LatticeBondLib<LT,Dim>::shiftLoc;

  template <LatticeTypeName LT, unsigned int Dim>
  Vector<List<unsigned int> > LatticeBondLib<LT,Dim>::map;

  template <LatticeTypeName LT, unsigned int Dim>
  Vector<List<int> > LatticeBondLib<LT,Dim>::coordinateMap;

  template <LatticeTypeName LatticeType, unsigned int Dimension>
  bool IsValid(const LatticeBondLib<LatticeType,Dimension>& L) {
    typedef LatticeBondLib<LatticeType,Dimension> Type;
    return IsValid(Type::shiftLoc)&&IsValid(Type::map)&&
           IsValid(Type::coordinateMap);
  }

  template <LatticeTypeName LatticeType, unsigned int Dimension>
  void release(LatticeBondLib<LatticeType,Dimension>& L) { L.clearData(); }

  template <LatticeTypeName LT, unsigned int Dim>
  const LatticeBondLib<LT,Dim>& RunBondLibrary() {
    Error("This Library is not available");
    static LatticeBondLib<LT,Dim> L;
    return L;
  }

}

#endif

