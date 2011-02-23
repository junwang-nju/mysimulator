
#ifndef _PDB_Information_H_
#define _PDB_Information_H_

#include "data/basic/property-list.h"

namespace std {

  struct PDBInfo;
  void release(PDBInfo&);

  struct PDBInfo {

    Vector<PropertyList<double> > Coordinate;
    Vector<unsigned int> AtomName;
    Vector<unsigned int> AminoAcidName;
    PropertyList<unsigned int> AminoAcidAtomID;

    PDBInfo() : Coordinate(), AtomName(), AminoAcidName(), AminoAcidAtomID() {}
    PDBInfo(const PDBInfo&) { Error("Cannot create PDB Information"); }
    PDBInfo& operator=(const PDBInfo&) {
      Error("Cannot copy PDB Information");
      return *this;
    }
    ~PDBInfo() { release(*this); }

  };

  bool IsAvailable(const PDBInfo& PI) {
    return IsAvailable(PI.Coordinate)&&IsAvailable(PI.AtomName)&&
           IsAvailable(PI.AminoAcidName)&&IsAvailable(PI.AminoAcidAtomID);
  }
  void release(PDBInfo& PI) {
    release(PI.Coordinate);
    release(PI.AtomName);
    release(PI.AminoAcidName);
    release(PI.AminoAcidAtomID);
  }
  void copy(PDBInfo& PI, const PDBInfo& cPI) {
    assert(IsAvailable(cPI));
    release(PI);
    imprint(PI,cPI);
    copy(PI.Coordinate,cPI.Coordinate);
    copy(PI.AtomName,cPI.AtomName);
    copy(PI.AminoAcidName,cPI.AminoAcidName);
    copy(PI.AminoAcidAtomID,cPI.AminoAcidAtomID);
  }
  void refer(PDBInfo& PI,const PDBInfo& cPI) {
    assert(IsAvailable(cPI));
    release(PI);
    refer(PI.Coordinate,cPI.Coordinate);
    refer(PI.AtomName,cPI.AtomName);
    refer(PI.AminoAcidName,cPI.AminoAcidName);
    refer(PI.AminoAcidAtomID,cPI.AminoAcidAtomID);
  }

}

#endif

