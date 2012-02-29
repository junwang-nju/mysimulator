
#ifndef _PDB_Interface_H_
#define _PDB_Interface_H_

#include "pdb/model/interface.h"
#include "array/1d/interface.h"
#include "array/2d/interface.h"
#include <cstring>

namespace mysimulator {

  struct PDBObject {

    public:

      typedef PDBObject   Type;

      char Code[5];
      Array1D<PDBModel> Model;
      unsigned int NResidues;
      Array2D<unsigned int> SequentialIdx;

      PDBObject() : Code(), Model(), NResidues(0), SequentialIdx() {
        strncpy(Code,"    ",5);
      }
      ~PDBObject() { clearData(); }

      void clearData() {
        strncpy(Code,"    ",5); release(Model);
        NResidues=0;  release(SequentialIdx);
      }
      bool isvalid() const {
        return IsValid(Model)&&(strncmp(Code,"    ",4)!=0)&&(NResidues>0)&&
               IsValid(SequentialIdx);
      }

    private:

      PDBObject(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBObject& O) { O.clearData(); }
  bool IsValid(const PDBObject& O) { return O.isvalid(); }

}

#endif

