
#ifndef _PDB_Interface_H_
#define _PDB_Interface_H_

#include "pdb/model/interface.h"
#include <cstring>

namespace mysimulator {

  struct PDBObject {

    public:

      typedef PDBObject   Type;

      char Code[5];
      Array1D<PDBModel> Model;

      PDBObject() : Code(), Model() { strncpy(Code,"    ",5); }
      ~PDBObject() { clearData(); }

      void clearData() { strncpy(Code,"    ",5); release(Model); }
      bool isvalid() const {
        return IsValid(Model)&&(strncmp(Code,"    ",4)!=0);
      }

    private:

      PDBObject(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBObject& O) { O.clearData(); }
  bool IsValid(const PDBObject& O) { return O.isvalid(); }

}

#endif

