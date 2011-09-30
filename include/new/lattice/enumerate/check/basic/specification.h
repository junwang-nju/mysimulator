
#ifndef _Lattice_Enumerate_Check_Basic_Specification_H_
#define _Lattice_Enumerate_Check_Basic_Specification_H_

#include "lattice/enumerate/check/base/interface.h"
#include "lattice/enumerate/check/interface.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeEnumCheck<LSN,Dim,LatticeEnumCheckMethodBasic>
    : public LatticeEnumCheckBase<LSN,Dim,LatticeEnumCheckMethodBasic> {

    public:

      typedef LatticeEnumCheck<LSN,Dim,LatticeEnumCheckMethodBasic> Type;
      typedef LatticeEnumCheckBase<LSN,Dim,LatticeEnumCheckMethodBasic>
              ParentType;

      LatticeEnumCheck() : ParentType() {}
      ~LatticeEnumCheck() { clearData(); }

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid();
      }

      template <unsigned int Len>
      bool operator()(LatticeEnumRunData<LSN,Dim,Len>& D) {
        Error("This Check is not Available!");
        return false;
      }

    private:

      LatticeEnumCheck(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

