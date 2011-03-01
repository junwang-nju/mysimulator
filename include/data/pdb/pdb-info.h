
#ifndef _PDB_Information_H_
#define _PDB_Information_H_

#include "data/name/pdb-unit-name.h"
#include "data/derived/dual-vector.h"

namespace std {

  struct PDBInfo;
  void release(PDBInfo&);

  struct PDBInfo {

    Vector<PropertyList<double> > Coordinate;
    Vector<unsigned int> AtomName;
    Vector<unsigned int> UnitName;
    DualVector<int> UnitAtomID;
    ParameterList UnitBond;

    PDBInfo()
      : Coordinate(), AtomName(), UnitName(), UnitAtomID(), UnitBond() {}
    PDBInfo(const PDBInfo&) { Error("Cannot create PDB Information"); }
    PDBInfo& operator=(const PDBInfo&) {
      Error("Cannot copy PDB Information");
      return *this;
    }
    ~PDBInfo() { release(*this); }

  };

  bool IsAvailable(const PDBInfo& PI) {
    return IsAvailable(PI.Coordinate)&&IsAvailable(PI.AtomName)&&
           IsAvailable(PI.UnitName)&&IsAvailable(PI.UnitAtomID)&&
           IsAvailable(PI.UnitBond);
  }
  void release(PDBInfo& PI) {
    release(PI.Coordinate);
    release(PI.AtomName);
    release(PI.UnitName);
    release(PI.UnitAtomID);
    release(PI.UnitBond);
  }
  void imprint(PDBInfo& PI, const PDBInfo& cPI) {
    assert(IsAvailable(cPI));
    release(PI);
    imprint(PI.Coordinate,cPI.Coordinate);
    for(unsigned int i=0;i<PI.Coordinate.size;++i)
      imprint(PI.Coordinate[i],cPI.Coordinate[i]);
    imprint(PI.AtomName,cPI.AtomName);
    imprint(PI.UnitName,cPI.UnitName);
    imprint(PI.UnitAtomID,cPI.UnitAtomID);
    imprint(PI.UnitBond,cPI.UnitBond);
  }
  void copy(PDBInfo& PI, const PDBInfo& cPI) {
    imprint(PI,cPI);
    copy(PI.Coordinate,cPI.Coordinate);
    copy(PI.AtomName,cPI.AtomName);
    copy(PI.UnitName,cPI.UnitName);
    copy(PI.UnitAtomID,cPI.UnitAtomID);
    copy(PI.UnitBond,cPI.UnitBond);
  }
  void refer(PDBInfo& PI,const PDBInfo& cPI) {
    assert(IsAvailable(cPI));
    release(PI);
    refer(PI.Coordinate,cPI.Coordinate);
    refer(PI.AtomName,cPI.AtomName);
    refer(PI.UnitName,cPI.UnitName);
    refer(PI.UnitAtomID,cPI.UnitAtomID);
    refer(PI.UnitBond,cPI.UnitBond);
  }
  void allocate(PDBInfo& PI,
                const unsigned int& nmodel, const unsigned int natom,
                const Vector<unsigned int>& UnitSeq,const unsigned int& nbond){
    allocate(PI.Coordinate,nmodel);
    Vector<unsigned int> usize,sz;
    allocate(usize,UnitSeq.size);
    for(unsigned int i=0;i<usize.size;++i)
      usize[i]=AminoAcidNumberAtoms[UnitSeq[i]];
    allocate(sz,natom);
    copy(sz,3);
    for(unsigned int i=0;i<nmodel;++i)  allocate(PI.Coordinate[i],sz);
    allocate(PI.AtomName,natom);
    allocate(PI.UnitName,UnitSeq.size);
    allocate(PI.UnitAtomID,usize);
    allocate(PI.UnitBond,2,1,nbond*2);
  }

}

#endif

