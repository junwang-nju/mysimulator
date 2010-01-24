
#ifndef _Pool_H_
#define _Pool_H_

#include "vector-base.h"

namespace std {

  template <typename T>
  class Pool : public VectorBase<T> {
    protected:
      unsigned int nUsed;
    public:
      typedef Pool<T>   Type;
      typedef VectorBase<T> ParentType;
      Pool() : ParentType(), nUsed(0) {}
      Pool(const Type& P) { myError("Cannot create from pool"); }
      ~Pool() { nUsed=0; }
      Type& operator=(const Type& P) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(P));
        nUsed=P.nUsed;
        return *this;
      }
  };

}

#endif

