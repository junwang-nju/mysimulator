
#ifndef _PDB_File_Atom_Name_Map_H_
#define _PDB_File_Atom_Name_Map_H_

#include "pdb-atom/name.h"

namespace mysimulator {

  class PDBAtomNameMapping {

    public:

      typedef PDBAtomNameMapping  Type;
      friend void Clear(PDBAtomNameMapping&);

      PDBAtomNameMapping() : _str(NULL), _name(UnknownAtom) {}
      PDBAtomNameMapping(const char* c,PDBAtomName AN)
        : _str(const_cast<char*>(c)), _name(AN) {}
      PDBAtomNameMapping(const Type& M) : _str(M._str), _name(M._name) {}
      ~PDBAtomNameMapping() { Clear(*this); }

      bool IsValid() const { return (_str!=NULL)&&(_name!=UnknownAtom); }

      const char* NameString() const { return _str; }
      const PDBAtomName Name() const { return _name; }

    protected:

      char* _str;
      PDBAtomName _name;

    private:

      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBAtomNameMapping& M) { M._str=NULL; M._name=UnknownAtom; }

  const PDBAtomNameMapping AtomMapping[] = {
    PDBAtomNameMapping(" CA ",AtomCA),
    PDBAtomNameMapping(" N  ",AtomN),
    PDBAtomNameMapping(" C  ",AtomC),
    PDBAtomNameMapping(" O  ",AtomO),
    PDBAtomNameMapping(" OXT",AtomOXT),
    PDBAtomNameMapping(" CB ",AtomCB),
    PDBAtomNameMapping(" CG ",AtomCG),
    PDBAtomNameMapping(" CG1",AtomCG1),
    PDBAtomNameMapping(" CG2",AtomCG2),
    PDBAtomNameMapping(" OG ",AtomOG),
    PDBAtomNameMapping(" OG1",AtomOG1),
    PDBAtomNameMapping(" SG ",AtomSG),
    PDBAtomNameMapping(" CD ",AtomCD),
    PDBAtomNameMapping(" CD1",AtomCD1),
    PDBAtomNameMapping(" CD2",AtomCD2),
    PDBAtomNameMapping(" ND1",AtomND1),
    PDBAtomNameMapping(" ND2",AtomND2),
    PDBAtomNameMapping(" OD1",AtomOD1),
    PDBAtomNameMapping(" OD2",AtomOD2),
    PDBAtomNameMapping(" SD ",AtomSD),
    PDBAtomNameMapping(" CE ",AtomCE),
    PDBAtomNameMapping(" CE1",AtomCE1),
    PDBAtomNameMapping(" CE2",AtomCE2),
    PDBAtomNameMapping(" CE3",AtomCE3),
    PDBAtomNameMapping(" NE ",AtomNE),
    PDBAtomNameMapping(" NE1",AtomNE1),
    PDBAtomNameMapping(" NE2",AtomNE2),
    PDBAtomNameMapping(" OE1",AtomOE1),
    PDBAtomNameMapping(" OE2",AtomOE2),
    PDBAtomNameMapping(" CZ ",AtomCZ),
    PDBAtomNameMapping(" CZ2",AtomCZ2),
    PDBAtomNameMapping(" CZ3",AtomCZ3),
    PDBAtomNameMapping(" NZ ",AtomNZ),
    PDBAtomNameMapping(" CH2",AtomCH2),
    PDBAtomNameMapping(" NH1",AtomNH1),
    PDBAtomNameMapping(" NH2",AtomNH2),
    PDBAtomNameMapping(" OH ",AtomOH),
    PDBAtomNameMapping(" H  ",AtomH),
    PDBAtomNameMapping(" H1 ",AtomH1),
    PDBAtomNameMapping(" H2 ",AtomH2),
    PDBAtomNameMapping(" H3 ",AtomH3),
    PDBAtomNameMapping(" HA ",AtomHA),
    PDBAtomNameMapping(" HA2",AtomHA2),
    PDBAtomNameMapping(" HA3",AtomHA3),
    PDBAtomNameMapping(" HB ",AtomHB),
    PDBAtomNameMapping(" HB1",AtomHB1),
    PDBAtomNameMapping(" HB2",AtomHB2),
    PDBAtomNameMapping(" HB3",AtomHB3),
    PDBAtomNameMapping(" HG ",AtomHG),
    PDBAtomNameMapping(" HG1",AtomHG1),
    PDBAtomNameMapping("HG11",AtomHG11),
    PDBAtomNameMapping("HG12",AtomHG12),
    PDBAtomNameMapping("HG13",AtomHG13),
    PDBAtomNameMapping(" HG2",AtomHG2),
    PDBAtomNameMapping("HG21",AtomHG21),
    PDBAtomNameMapping("HG22",AtomHG22),
    PDBAtomNameMapping("HG23",AtomHG23),
    PDBAtomNameMapping(" HG3",AtomHG3),
    PDBAtomNameMapping(" HD1",AtomHD1),
    PDBAtomNameMapping("HD11",AtomHD11),
    PDBAtomNameMapping("HD12",AtomHD12),
    PDBAtomNameMapping("HD13",AtomHD13),
    PDBAtomNameMapping(" HD2",AtomHD2),
    PDBAtomNameMapping("HD21",AtomHD21),
    PDBAtomNameMapping("HD22",AtomHD22),
    PDBAtomNameMapping("HD23",AtomHD23),
    PDBAtomNameMapping(" HD3",AtomHD3),
    PDBAtomNameMapping(" HE ",AtomHE),
    PDBAtomNameMapping(" HE1",AtomHE1),
    PDBAtomNameMapping(" HE2",AtomHE2),
    PDBAtomNameMapping("HE21",AtomHE21),
    PDBAtomNameMapping("HE22",AtomHE22),
    PDBAtomNameMapping(" HE3",AtomHE3),
    PDBAtomNameMapping(" HZ ",AtomHZ),
    PDBAtomNameMapping(" HZ1",AtomHZ1),
    PDBAtomNameMapping(" HZ2",AtomHZ2),
    PDBAtomNameMapping(" HZ3",AtomHZ3),
    PDBAtomNameMapping(" HH ",AtomHH),
    PDBAtomNameMapping("HH11",AtomHH11),
    PDBAtomNameMapping("HH12",AtomHH12),
    PDBAtomNameMapping(" HH2",AtomHH2),
    PDBAtomNameMapping("HH21",AtomHH21),
    PDBAtomNameMapping("HH22",AtomHH22)
  };

}

#endif

