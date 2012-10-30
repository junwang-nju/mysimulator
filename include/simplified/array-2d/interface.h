
#ifndef _Array_2D_Interface_H_
#define _Array_2D_Interface_H_

#include "array/interface.h"

namespace mysimulator {

  template <typename T>
  class Array2D : public ArrayExpression<Array2D<T>,T>,
                  private Array<T>, public Array<Array<T>> {

    public:

      typedef Array2D<T>    Type;
      typedef Array<T>          ParentTypeA;
      typedef Array<Array<T>>   ParentTypeB;
      typedef unsigned int      size_type;

      Array2D() : ParentTypeA(), ParentTypeB() {}
      ~Array2D() { reset(); }

      Type& operator=(const Type& A) {
        ParentTypeB::operator=((ParentTypeB const&)A);
        return *this;
      }
      Type& operator=(const T& D) {
        ParentTypeB::operator=(D); return *this; }

      void allocate(size_type m,size_type n) {
        size_type nbin=16/sizeof(T);
        size_type rn=(n/nbin)*nbin+(n%nbin>0?1:0);
        ParentTypeA::allocate(m*rn);
        //ParentTypeB::allocate(m);
        //for(size_type i=0;i<m;++i) ParentTypeB::operator[](i).refer((ParentTypeA&)(*this),i*rn,rn); 
      }

      operator bool() const {
        return ParentTypeA::operator bool() && ParentTypeB::operator bool();
      }
      void reset() { ParentTypeB::reset(); ParentTypeA::reset(); }

  };

}

#endif
