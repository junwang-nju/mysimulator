
#ifndef _PDB_File_Residue_Name_Map_H_
#define _PDB_File_Residue_Name_Map_H_

#include "pdb-residue/name.h"

namespace mysimulator {

  class PDBResidueNameMapping {

    public:

      typedef PDBResidueNameMapping   Type;
      friend void Clear(PDBResidueNameMapping&);

      PDBResidueNameMapping() : _str(NULL), _name(UnknownResidue) {}
      PDBResidueNameMapping(const char* c, PDBResidueName RN)
        : _str(const_cast<char*>(c)), _name(RN) {}
      PDBResidueNameMapping(const Type& M) : _str(M._str),_name(M._name) {}
      ~PDBResidueNameMapping() { Clear(*this); }

      bool IsValid() const { return (_str!=NULL)&&(_name!=UnknownResidue); }

      const char* NameString() const { return _str; }
      const PDBResidueName Name() const { return _name; }

    protected:

      char* _str;
      PDBResidueName _name;

    private:

      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBResidueNameMapping& M) { M._str=NULL; M._name=UnknownResidue; }

  const unsigned int PDBResidueMappingSize=20;
  const PDBResidueNameMapping ResidueMapping[PDBResidueMappingSize] = {
    PDBResidueNameMapping("ALA",Ala),
    PDBResidueNameMapping("ARG",Arg),
    PDBResidueNameMapping("ASN",Asn),
    PDBResidueNameMapping("ASP",Asp),
    PDBResidueNameMapping("CYS",Cys),
    PDBResidueNameMapping("GLN",Gln),
    PDBResidueNameMapping("GLU",Glu),
    PDBResidueNameMapping("GLY",Gly),
    PDBResidueNameMapping("HIS",His),
    PDBResidueNameMapping("ILE",Ile),
    PDBResidueNameMapping("LEU",Leu),
    PDBResidueNameMapping("LYS",Lys),
    PDBResidueNameMapping("MET",Met),
    PDBResidueNameMapping("PHE",Phe),
    PDBResidueNameMapping("PRO",Pro),
    PDBResidueNameMapping("SER",Ser),
    PDBResidueNameMapping("THR",Thr),
    PDBResidueNameMapping("TRP",Trp),
    PDBResidueNameMapping("TYR",Tyr),
    PDBResidueNameMapping("VAL",Val)
  };

}

#endif

