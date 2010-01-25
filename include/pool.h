
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
      template <typename inputT>
      Type& operator=(const inputT& P) {
        myError("Cannot assigned for Pool");
        return *this;
      }
      T& operator[](const unsigned int& I);
      const T& operator[](const unsigned int& I) const;
      const unsigned int& capacity() const;
      const unsigned int& used() const;
      void allocate(const unsigned int& Max);
      void clear();
      void add(const T& mer);
      void del(const unsigned int& I);
      void swap(Type& P);
      virtual const char* type() const;
  };

}

#endif

