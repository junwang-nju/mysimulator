
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
    PropertyList<int> AminoAcidAtomID;
    PropertyList<unsigned int> BondID;

    PDBInfo()
      : Coordinate(), AtomName(), AminoAcidName(), AminoAcidAtomID(), BondID(){
    }
    PDBInfo(const PDBInfo&) { Error("Cannot create PDB Information"); }
    PDBInfo& operator=(const PDBInfo&) {
      Error("Cannot copy PDB Information");
      return *this;
    }
    ~PDBInfo() { release(*this); }

  };

  bool IsAvailable(const PDBInfo& PI) {
    return IsAvailable(PI.Coordinate)&&IsAvailable(PI.AtomName)&&
           IsAvailable(PI.AminoAcidName)&&IsAvailable(PI.AminoAcidAtomID)&&
           IsAvailable(PI.BondID);
  }
  void release(PDBInfo& PI) {
    release(PI.Coordinate);
    release(PI.AtomName);
    release(PI.AminoAcidName);
    release(PI.AminoAcidAtomID);
    release(PI.BondID);
  }
  void imprint(PDBInfo& PI, const PDBInfo& cPI) {
    assert(IsAvailable(cPI));
    release(PI);
    imprint(PI.Coordinate,cPI.Coordinate);
    for(unsigned int i=0;i<PI.Coordinate.size;++i)
      imprint(PI.Coordinate[i],cPI.Coordinate[i]);
    imprint(PI.AtomName,cPI.AtomName);
    imprint(PI.AminoAcidName,cPI.AminoAcidName);
    imprint(PI.AminoAcidAtomID,cPI.AminoAcidAtomID);
    imprint(PI.BondID,cPI.BondID);
  }
  void copy(PDBInfo& PI, const PDBInfo& cPI) {
    imprint(PI,cPI);
    copy(PI.Coordinate,cPI.Coordinate);
    copy(PI.AtomName,cPI.AtomName);
    copy(PI.AminoAcidName,cPI.AminoAcidName);
    copy(PI.AminoAcidAtomID,cPI.AminoAcidAtomID);
    copy(PI.BondID,cPI.BondID);
  }
  void refer(PDBInfo& PI,const PDBInfo& cPI) {
    assert(IsAvailable(cPI));
    release(PI);
    refer(PI.Coordinate,cPI.Coordinate);
    refer(PI.AtomName,cPI.AtomName);
    refer(PI.AminoAcidName,cPI.AminoAcidName);
    refer(PI.AminoAcidAtomID,cPI.AminoAcidAtomID);
    refer(PI.BondID,cPI.BondID);
  }
  void allocate(PDBInfo& PI,
                const unsigned int& nmodel, const unsigned int& natom,
                const Vector<unsigned int>& AminoAcidSeq,
                const unsigned int& nbond) {
    allocate(PI.Coordinate,nmodel);
    Vector<unsigned int> sz;
    allocate(sz,natom);
    copy(sz,3);
    for(unsigned int i=0;i<nmodel;++i)  allocate(PI.Coordinate[i],sz);
    allocate(PI.AtomName,natom);
    allocate(PI.AminoAcidName,naminoacid);
    allocate(sz,nbond);
    copy(sz,2);
    allocate(PI.BondID,sz);
  }

}

#endif

