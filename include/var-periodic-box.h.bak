
#ifndef _Variable_Periodic_Box_H_
#define _Variable_Periodic_Box_H_

#include "periodic-box-base.h"
#include "object-with-storage.h"
#include "var-vector.h"

namespace std {

  class varPeriodicBox : public ObjectWStorage<PeriodicBoxBase<varVector> > {

    public:

      typedef varPeriodicBox  Type;

      typedef ObjectWStorage<PeriodicBoxBase<varVector> > ParentType;

      varPeriodicBox() : ParentType() {}

      varPeriodicBox(const Type& vPB) {
        myError("Cannot create from variable periodic box");
      }

      ~varPeriodicBox() {}

      Type& operator=(const Type& vPB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vPB));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const PeriodicBoxBase<iVecType>& PB) {
        static_cast<ParentType*>(this)->operator=(PB);
        return *this;
      }

      void allocate(const unsigned int Dim) {
        Box.allocate(Dim);
        EdgeFlag.allocate(Dim);
        halfBox.allocate(Dim);
      }

  };

}

#endif

