
#ifndef _Reference_Periodic_Box_
#define _Reference_Periodic_Box_

#include "periodic-box-base.h"
#include "ref-vector.h"
#include "var-vector.h"

namespace std {

  template <template <typename> class VecType=varVector>
  class refPeriodicBox
    : public refObject<PeriodicBoxBase<refVector>,PeriodicBoxBase<VecType> > {

    public:

      typedef refPeriodicBox<VecType>   Type;

      typedef refObject<PeriodicBoxBase<refVector>,PeriodicBoxBase<VecType> >
              ParentType;

      refPeriodicBox() : ParentType() {}

      refPeriodicBox(const Type& rPB) {
        myError("Cannot create from reference periodic box");
      }

      ~refPeriodicBox() {}

      Type& operator=(const Type& rPB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rPB));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const PeriodicBoxBase<iVecType>& PB) {
        static_cast<ParentType*>(this)->operator=(PB);
        return *this;
      }

      virtual void refer(ParentType& rPB) { refer(rPB,0,rPB.runBox().size()); }

      virtual void refer(ObjectWStorage<PeriodicBoxBase<VecType> >& PB) {
        refer(PB,0,PB.runBox().size());
      }

      void refer(ParentType& rPB, unsigned int off, unsigned int sz) {
        assert(off+sz<=rPB.runBox().size());
        if(this->runBox().IsAvailable())  this->RefInfo().remove_self();
        this->runBox().refer(rPB.runBox(),off,sz);
        this->runFlag().refer(rPB.runFlag(),off,sz);
        this->runHfBox().refer(rPB.runHfBox(),off,sz);
        rPB.RefInfo().add_before(this->RefInfo());
      }

      void refer(ObjectWStorage<PeriodicBoxBase<VecType> >& PB,
                 unsigned int off, unsigned int sz) {
        assert(off+sz<=PB.runBox().size());
        if(this->runBox().IsAvailable())  this->RefInfo().remove_self();
        this->runBox().refer(PB.runBox(),off,sz);
        this->runFlag().refer(PB.runFlag(),off,sz);
        this->runHfBox().refer(PB.runHfBox(),off,sz);
        PB.RefList().append(this->RefInfo());
      }

  };
}

#endif

