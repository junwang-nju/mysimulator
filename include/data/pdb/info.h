
#ifndef _PDB_Information_H_
#define _PDB_Information_H_

#include "operation/unit/composition-op.h"

namespace std {

  struct PDBInfo;
  void release(PDBInfo&);

  struct PDBInfo {

    Vector<unsigned int> AtomID;
    Vector<unsigned int> UnitID;
    Vector<Vector<unsigned int> > UnitAtom;
    Vector<PropertyList<double> > AtomCoordinate;
    PropertyList<unsigned int>    UnitConnect;

    PDBInfo() : AtomID(),UnitID(),UnitAtom(),AtomCoordinate(),UnitConnect() {}
    PDBInfo(const PDBInfo&) { Error("Cannot create PDB Information"); }
    PDBInfo& operator=(const PDBInfo&) {
      Error("Cannot copy PDB Information");
      return *this;
    }
    ~PDBInfo() { release(*this); }

  };

  bool IsAvailable(const PDBInfo& PI) {
    return IsAvailable(PI.AtomID)&&IsAvailable(PI.UnitID)&&
           IsAvailable(PI.UnitAtom)&&IsAvailable(PI.AtomCoordinate)&&
           IsAvailable(UnitConnect);
  }
  void release(PDBInfo& PI) {
    release(PI.AtomID);
    release(PI.UnitID);
    release(PI.UnitAtom);
    release(PI.AtomCoordinate);
    release(PI.UnitConnect);
  }
  void imprint(PDBInfo& PI, const PDBInfo& cPI) {
    assert(IsAvailable(cPI));
    release(PI);
    imprint(PI.AtomID,cPI.AtomID);
    imprint(PI.UnitID,cPI.UnitID);
    imprint(PI.UnitAtom,cPI.UnitAtom);
    for(unsigned int i=0;i<cPI.UnitAtom.size;++i)
      imprint(PI.UnitAtom[i],cPI.UnitAtom[i]);
    imprint(PI.AtomCoordinate,cPI.AtomCoordinate);
    for(unsigned int i=0;i<cPI.AtomCoordinate.size;++i)
      imprint(PI.AtomCoordinate[i],cPI.AtomCoordinate[i]);
    imprint(PI.UnitConnect,cPI.UnitConnect);
  }
  void copy(PDBInfo& PI, const PDBInfo& cPI) {
    imprint(PI,cPI);
    copy(PI.AtomID,cPI.AtomID);
    copy(PI.UnitID,cPI.UnitID);
    copy(PI.UnitAtom,cPI,UnitAtom);
    copy(PI.AtomCoordinate,cPI.AtomCoordinate);
    copy(PI.UnitConnect,cPI.UnitConnect);
  }
  void refer(PDBInfo& PI, const PDBInfo& cPI) {
    assert(IsAvailable(cPI));
    release(PI);
    refer(PI.AtomID,cPI,AtomID);
    refer(PI.UnitID,cPI.UnitID);
    refer(PI.UnitAtom,cPI.UnitAtom);
    refer(PI.AtomCoordinate,cPI.AtomCoordinate);
    refer(PI.UnitConnect,cPI.UnitConnect);
  }

  void allocate(
      PDBInfo& PI, const unsigned int nmodel, const unsigned int natom,
      const Vector<unsigned int>& nuatom, const unsigned int nbond) {
    allocate(PI.AtomID,natom);
    allocate(PI.UnitID,nuatom.size);
    allocate(PI.UnitAtom,nuatom.size);
    for(unsigned int i=0;i<nuatom.size;++i) allocate(PI.UnitAtom[i],nuatom[i]);
    Vector<unsigned int> sz(natom);
    copy(sz,3);
    allocate(PI.AtomCoordinate,nmodel);
    for(unsigned int i=0;i<nmodel;++i)  allocate(PI.AtomCoordinate[i],sz);
    allocate(sz,nbond);
    copy(sz,2);
    allocate(PI.UnitConnect,sz);
  }

}

#endif

