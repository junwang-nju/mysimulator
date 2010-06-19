
#ifndef _PDB_Data_Amino_Acid_Name_H_
#define _PDB_Data_Amino_Acid_Name_H_

#include "error-proc.h"
#include <cstring>

namespace std {

  struct AminoAcidName;

  void assign(AminoAcidName&, const AminoAcidName&);  

  struct AminoAcidName {
    char name[4];
    char shortname;

    typedef AminoAcidName Type;

    AminoAcidName() { name[3]=0; }
    AminoAcidName(const AminoAcidName&) {
      myError("Cannot create from Amino Acid Name");
    }
    Type& operator=(const Type& AA) { assign(*this,AA); return *this; }
    const char* operator()() const { return name; }
    const char ShortName() const { return shortname; }
  };

  void assign(AminoAcidName& dest, const AminoAcidName& src) {
    strncpy(dest.name,src.name,3);
    dest.shortname=src.shortname;
  }
  static const char AminoAcidNameLibrary[][4]={
    "ALA","ARG","ASN","ASP","CYS","GLN","GLU","GLY","HIS","ILE",
    "LEU","LYS","MET","PHE","PRO","SER","THR","TRP","TYR","VAL"
  };
  static const char AminoAcidShortNameLibrary[]={
    'A','R','N','D','C','Q','E','G','H','I',
    'L','K','M','F','P','S','T','W','Y','V'
  };
  const char* tolong(const char aaname) {
    for(unsigned int i=0;i<20;++i)
      if(aaname==AminoAcidShortNameLibrary[i])  return AminoAcidNameLibrary[i];
    myError("Unknown Short Name of Amino Acid");
    return "   ";
  }
  const char toshort(const char* aaname) {
    for(unsigned int i=0;i<20;++i)
      if(strncmp(aaname,AminoAcidNameLibrary[i],3)==0)
        return AminoAcidShortNameLibrary[i];
    myError("Unknown Name of Amino Acid");
    return ' ';
  }
  void Set(AminoAcidName& AA, const char* aaname) {
    strncpy(AA.name,aaname,3);
    AA.shortname=toshort(aaname);
  }
  void Set(AminoAcidName& AA, const char aaname) {
    AA.shortname=aaname;
    strncpy(AA.name,tolong(aaname),3);
  }

  ostream& operator<<(ostream& os, AminoAcidName& aaname) {
    os<<aaname();
    return os;
  }

}

#endif

