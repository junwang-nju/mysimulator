
#ifndef _PDB_Residue_With_Alternative_H_
#define _PDB_Residue_With_Alternative_H_

#include "pdb/residue/interface.h"

namespace mysimulator {

  class __PDB_Residue_wAlt : public Array<__PDB_Residue> {

    public:

      typedef __PDB_Residue_wAlt          Type;
      typedef Array<__PDB_Residue>  ParentType;

      __PDB_Residue_wAlt() : ParentType() {}
      __PDB_Residue_wAlt(const Type& R) : ParentType((ParentType const&)R) {}
      __PDB_Residue_wAlt(Type&& R) : __PDB_Residue_wAlt() {
        ParentType::swap(R);
      }
      ~__PDB_Residue_wAlt() { ParentType::reset(); }

      Type& operator=(const Type& R) {
        assert((bool)(*this));
        assert((bool)R);
        ParentType::operator=((ParentType const&)R);
        return *this;
      }

      void imprint(const Type&) {
        fprintf(stderr,"Residue With-Alterntive Cannot be imprinted!\n");
      }

  };

}

#endif

