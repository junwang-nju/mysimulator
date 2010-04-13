
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
      PDBID(const PDBID& ipdbid) { operator=(ipdbid); name[4]=0; }
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
      typedef AminoAcidName Type;
      AminoAcidName() { name[3]=0; }
      AminoAcidName(const char* aname) {
        SetAs(aname);   name[3]=0;
      }
      AminoAcidName(const char aname) {
        SetAs(aname);   name[3]=0;
      }
      AminoAcidName(const Type& aaname) { operator=(aaname);  name[3]=0; }
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

  class AtomType {
    public:
      fixVector<double,3> AtomCoordinate;
      char AtomName[5];
      double TempFactor;
      typedef AtomType Type;
      AtomType() : AtomCoordinate(), TempFactor(0.) { AtomName[4]=0; }
      AtomType(const Type& Atm) : AtomCoordinate(), TempFactor(0.) {
        operator=(Atm);
        AtomName[4]=0;
      }
      Type& operator=(const Type& Atm) {
        AtomCoordinate=Atm.AtomCoordinate;
        strncpy(AtomName,Atm.AtomName,4);
        TempFactor=Atm.TempFactor;
        return *this;
      }
      void SetNameAs(const char* name) { strncpy(AtomName,name,4); }
      void SetCoordinateAs(const double x, const double y, const double z) {
        AtomCoordinate[0]=x;
        AtomCoordinate[1]=y;
        AtomCoordinate[2]=z;
      }
  };

  class AminoAcidType {
    public:
      AminoAcidName Name;
      vector<AtomType>  Data;
      typedef AminoAcidType Type;
      AminoAcidType() : Name(), Data() {}
      AminoAcidType(const Type& AA) { operator=(AA); }
      Type& operator=(const Type& AA) {
        Name=AA.Name;
        Data=AA.Data;
        return *this;
      }
      fixVector<double,3>& Atom(const char* name) {
        for(unsigned int i=0;i<Data.size();++i)
          if(strncmp(name,Data[i].AtomName,4)==0)
            return Data[i].AtomCoordinate;
        myError("Unknown Atom Name");
        return Data[0].AtomCoordinate;
      }
      const fixVector<double,3>& Atom(const char* name) const {
        for(unsigned int i=0;i<Data.size();++i)
          if(strncmp(name,Data[i].AtomName,4)==0)
            return Data[i].AtomCoordinate;
        myError("Unknown Atom Name");
        return Data[0].AtomCoordinate;
      }
  };

  typedef vector<AminoAcidType>  ModelType;

  class PDBDataStructure {
    public:
      PDBID Id;
      vector<ModelType> Model;
      typedef PDBDataStructure  Type;
      PDBDataStructure() : Id(), Model() {}
      PDBDataStructure(const Type& iPDB) {
        myError("Cannot create from PDB Data Structure");
      }
      Type& operator=(const Type& iPDB) {
        Id=iPDB.Id;
        Model=iPDB.Model;
        return *this;
      }
  };

}

#endif

