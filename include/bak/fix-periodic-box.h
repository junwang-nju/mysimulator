
#ifndef _Fixed_Periodic_Box_H_
#define _Fixed_Periodic_Box_H_

#include "periodic-box.h"
#include "fix-vector.h"
#include "ref-vector.h"

namespace std {

  template <unsigned int Dim>
  class fixPeriodicBox : public PeriodicBox<refVector> {

    public:

      typedef fixPeriodicBox<Dim>   Type;

      typedef PeriodicBox<refVector>  ParentType;

    protected:

      fixVector<double,Dim> inBox;

      fixVector<double,Dim> inHfBox;

      fixVector<unsigned int,Dim> inFlag;

    public:

      fixPeriodicBox() : ParentType() {
        this->box().refer(inBox);
        this->hfbox().refer(inHfBox);
        this->flag().refer(inFlag);
      }

      fixPeriodicBox(const Type&) {
        myError("Cannot create from fixed Periodic Box");
      }

      ~fixPeriodicBox() {}

      Type& operator=(const Type& fPB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fPB));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const PeriodicBox<VecType>& PB) {
        static_cast<ParentType*>(this)->operator=(PB);
        return *this;
      }

      void clear() {}

  };

}

#endif

