
#ifndef _Fixed_Periodic_Box_H_
#define _Fixed_Periodic_Box_H_

#include "periodic-box-base.h"
#include "object-with-storage.h"
#include "fix-vector.h"
#include "ref-vector.h"

namespace std {

  template <unsigned int Dim>
  class fixPeriodicBox : public ObjectWStorage<PeriodicBoxBase<refVector> > {

    public:

      typedef fixPeriodicBox<Dim>   Type;

      typedef ObjectWStorage<PeriodicBoxBase<refVector> > ParentType;

    protected:

      fixVector<double,Dim> BoxData;

      fixVector<unsigned int,Dim> FlagData;

      fixVector<double,Dim> halfBoxData;

    public:

      fixPeriodicBox() : ParentType() {
        runBox().refer(BoxData);
        runFlag().refer(FlagData);
        runHfBox().refer(halfBoxData);
      }

      fixPeriodicBox(const Type& fPB) {
        myError("Cannot create from fixed periodic box");
      }

      ~fixPeriodicBox() {}

      Type& operator=(const Type& fPB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fPB));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const PeriodicBoxBase<iVecType>& PB) {
        static_cast<ParentType*>(this)->operator=(PB);
        return *this;
      }

  };

}

#endif

