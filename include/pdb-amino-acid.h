
#ifndef _PDB_Data_Amino_Acid_H_
#define _PDB_Data_Amino_Acid_H_

#include "pdb-amino-acid-name.h"
#include "pdb-atom.h"
#include <vector>

namespace std {

  struct AminoAcidType;
  
  void assign(AminoAcidType&, const AminoAcidType&);

  struct AminoAcidType {
    AminoAcidName name;
    vector<AtomType> data;
    
    typedef AminoAcidType   Type;
    
    AminoAcidType() : name(), data() {}
    AminoAcidType(const Type&) {
      myError("Cannot create from Amino Acid Type");
    }
    Type& operator=(const Type& AA) { assign(*this,AA); return *this; }
    
    double* Atom(const char* atmname) {
      for(unsigned int i=0;i<data.size();++i)
        if(strncmp(atmname,data[i].name,4)==0) return data[i].coordinate;
      myError("Unknown Atom Name");
      return NULL;
    }
    const double* Atom(const char* atmname) const {
      for(unsigned int i=0;i<data.size();++i)
        if(strncmp(atmname,data[i].name,4)==0) return data[i].coordinate;
      myError("Unknown Atom Name");
      return NULL;
    }

  };

  void assign(AminoAcidType& dest, const AminoAcidType& src) {
    dest.name=src.name;
    dest.data=src.data;
  }

}

#endif
