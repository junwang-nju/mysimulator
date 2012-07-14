
#ifndef _PDB_Atom_Position_Interface_H_
#define _PDB_Atom_Position_Interface_H_

namespace mysimulator {

  class PDBAtomPosition {

    public:

      typedef PDBAtomPosition Type;
      friend void Clear(PDBAtomPosition&);

      PDBAtomPosition() : X(0), Y(0), Z(0) {}
      ~PDBAtomPosition() { Clear(*this); }

    protected:

      double X,Y,Z;

    private:

      PDBAtomPosition(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

