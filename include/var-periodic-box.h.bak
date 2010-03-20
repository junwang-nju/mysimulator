
#ifndef _Variable_Periodic_Box_H_
#define _Variable_Periodic_Box_H_

#include "periodic-box-base.h"
#include "var-vector.h"

namespace std {

  class varPeriodicBox : public PeriodicBoxBase<varVector> {

    public:

      typedef varPeriodicBox  Type;

      typedef PeriodicBoxBase<varVector>  ParentType;

      varPeriodicBox() : ParentType() {}

      varPeriodicBox(const unsigned int Dim) : ParentType() { allocate(Dim); }

      varPeriodicBox(const Type&) {
        myError("Cannot create from variable Periodic Box");
      }

      ~varPeriodicBox() {}

      Type& operator=(const Type& vPB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vPB));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const PeriodicBoxBase<VecType>& PB) {
        static_cast<ParentType*>(this)->operator=(PB);
        return *this;
      }

      void allocate(const unsigned int Dim) {
        this->box().allocate(Dim);
        this->flag().allocate(Dim);
        this->hfbox().allocate(Dim);
      }

  };

}

#endif

