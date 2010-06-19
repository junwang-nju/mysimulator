
#ifndef _PDB_Data_Atom_Name_H_
#define _PDB_Data_Atom_Name_H_

#include "vector-impl.h"
#include <cstring>

namespace std {

  struct AtomType;
  
  void assign(AtomType&, const AtomType&);
  
  struct AtomType {
    double coordinate[3];
    char name[5];
    double TempFactor;
    
    typedef AtomType  Type;
    
    AtomType() : TempFactor(0.) { name[4]=0; }
    AtomType(const Type&) { myError("Cannot create from Atom Type"); }
    Type& operator=(const Type& Atm) { assign(*this,Atm); return *this; }
    
  };

  void assign(AtomType& dest, const AtomType& src) {
    assign(dest.coordinate,src.coordinate,3);
    strncpy(dest.name,src.name,4);
    dest.TempFactor=src.TempFactor;
  }

  void Set(AtomType& Atm, const char* name) { strncpy(Atm.name,name,4); }
  
  void Set(AtomType& Atm, const double x, const double y, const double z) {
    Atm.coordinate[0]=x;
    Atm.coordinate[1]=y;
    Atm.coordinate[2]=z;
  }

}

#endif
