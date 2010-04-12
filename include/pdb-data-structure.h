
#ifndef _PDB_Data_Structure_H_
#define _PDB_Data_Structure_H_

#include <vector>
#include <cstring>
#include "fix-vector.h"

namespace std {

  class PDBID {
    private:
      char name[5];
    public:
      PDBID() { name[4]=0; }
      PDBID(const char* iname) { strncpy(name,iname,4); name[4]=0; }
      PDBID(const PDBID& ipdbid) { myError("Cannot create from PDB ID"); }
      PDBID& operator=(const PDBID& ipdbid) {
        strncpy(name,ipdbid.name,4);
        return *this;
      }
      const char* operator()() const { return name; }
      void SetAs(const char* id) { strncpy(name,id,4); }
  };

  class AminoAcidName {
    private:
      static const char AANameC3[][4];
      static const char AANameC1[];
      char name[4];
      char abname;
      const char convert(const char* aname) const {
        for(unsigned int i=0;i<20;++i)
          if(strncmp(aname,AANameC3[i],3)==0)  return AANameC1[i];
        myError("Unknown 3-char Amino Acid Name");
        return 'X';
      }
      const char* convert(const char aname) const {
        for(unsigned int i=0;i<20;++i)
          if(aname==AANameC1[i])  return AANameC3[i];
        myError("Unknown 1-char Amino Acid Name");
        return "   ";
      };
    public:
      AminoAcidName() { name[3]=0; }
      AminoAcidName(const char* aname) {
        SetAs(aname);   name[3]=0;
      }
      AminoAcidName(const char aname) {
        SetAs(aname);   name[3]=0;
      }
      AminoAcidName(const AminoAcidName& aaname) {
        myError("Cannot create from Amino Acid Name");
      }
      AminoAcidName& operator=(const AminoAcidName& aaname) {
        strncpy(name,aaname.name,3);
        abname=aaname.abname;
        return *this;
      };
      const char* operator()() const { return name; }
      const char simpleName() const { return abname; }
      void SetAs(const char aname) {
        abname=aname;
        strncpy(name,convert(abname),3);
      }
      void SetAs(const char* aname) {
        strncpy(name,aname,3);
        abname=convert(aname);
      }
  };

  ostream& operator<<(ostream& os, AminoAcidName& aaname) {
    os<<aaname();
    return os;
  }

  const char AminoAcidName::AANameC3[][4]={
    "ALA","ARG","ASN","ASP","CYS","GLN","GLU","GLY","HIS","ILE",
    "LEU","LYS","MET","PHE","PRO","SER","THR","TRP","TYR","VAL"
  };

  const char AminoAcidName::AANameC1[]={
    'A','R','N','D','C','Q','E','G','H','I',
    'L','K','M','F','P','S','T','W','Y','V'
  };

  typedef fixVector<double,3>  AtomCoordinateType;

  class AminoAcidCoordinateType {
    public:
      AtomCoordinateType  AtomCoordinate;
      char AtomName[5];
      typedef AminoAcidCoordinateType   Type;
      AminoAcidCoordinateType() : AtomCoordinate() { AtomName[4]=0; }
      AminoAcidCoordinateType(const Type& AACoor) {
        myError("Cannot create from Amino Acid Coordinate Type");
      }
      Type& operator=(const Type& AACoor) {
        AtomCoordinate=AACoor.AtomCoordinate;
        strncpy(AtomName,AACoor.AtomName,4);
        return *this;
      }
      void SetAs(const char* name) { strncpy(AtomName,name,4); }
  };

  typedef vector<AminoAcidCoordinateType>  ModelCoordinateType;

  class PDBDataStructure {
    public:
      PDBID id;
      vector<AminoAcidName> seq;
      vector<ModelCoordinateType> coordinate;
      typedef PDBDataStructure  Type;
      PDBDataStructure() : id(), seq(), coordinate() {}
      PDBDataStructure(const Type& iPDB) {
        myError("Cannot create from PDB Data Structure");
      }
      Type& operator=(const Type& iPDB) {
        id=iPDB.id;
        seq=iPDB.seq;
        coordinate=iPDB.coordinate;
        return *this;
      }
  };

}

#endif

