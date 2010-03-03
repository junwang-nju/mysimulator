
#ifndef _Reference_Periodic_Box_H_
#define _Reference_Periodic_Box_H_

#include "periodic-box-base.h"
#include "ref-vector.h"

namespace std {

  class refPeriodicBox : public PeriodicBoxBase<refVector> {

    public:

      typedef refPeriodicBox    Type;

      typedef PeriodicBoxBase<refVector>  ParentType;

      refPeriodicBox() : ParentType() {}

      refPeriodicBox(const Type&) {
        myError("Cannot create from reference Periodic Box");
      }

      ~refPeriodicBox() {}

      Type& operator=(const Type& rPB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rPB));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const PeriodicBoxBase<VecType>& PB) {
        static_cast<ParentType*>(this)->operator=(PB);
        return *this;
      }

      template <template <typename> class VecType>
      void refer(const PeriodicBoxBase<VecType>& PB) {
        refer(PB,0U,PB.box().size());
      }

      template <template <typename> class VecType>
      void refer(const PeriodicBoxBase<VecType>& PB,
                 const unsigned int off, const unsigned int size) {
        assert(off+size<=PB.box().size());
        this->box().refer(PB.box(),off,size);
        this->flag().refer(PB.flag(),off,size);
        this->hfbox().refer(PB.hfbox(),off,size);
      }

  };

}

#endif

