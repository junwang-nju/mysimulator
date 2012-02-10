
#ifndef _PDB_Property_Atom_Position_Interface_H_
#define _PDB_Property_Atom_Position_Interface_H_

namespace mysimulator {

  struct PDBAtomPosition {

    public:

      typedef PDBAtomPosition Type;

      double X,Y,Z;

      PDBAtomPosition() : X(0), Y(0), Z(0) {}
      ~PDBAtomPosition() { clearData(); }

      void clearData() { X=0; Y=0; Z=0; }
      bool isvalid() const { return true; }

    private:

      PDBAtomPosition(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBAtomPosition& P) { P.clearData(); }
  bool IsValid(const PDBAtomPosition& P) { return P.isvalid(); }

}

#endif

