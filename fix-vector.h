
#ifndef _Fixed_Vector_H_
#define _Fixed_Vector_H_

#include "vector-base.h"

namespace std {

  template <typename T, uint ND>
  class fixVector : public VectorBase<T> {

    private:

      T runData[ND];

    public:

      typedef T                   DataType;

      typedef fixVector<T,ND>     Type;

      typedef VectorBase<T>       ParentType;

      fixVector() : ParentType() {
        this->Data=runData;
        this->nData=ND;
        this->set_HeadTail();
      }

      fixVector(const Type& v) { myError("vector copier is prohibited!"); }

      ~fixVector() {}

      template <typename vType>
      Type& Duplicate(const vType& v) {
        assert(vType::IsVector);
        this->assign(v);
        return *this;
      }

      Type& operator=(const Type& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator=(const inputT& v) { this->assign(v); return *this; }

      template <typename inputT>
      Type& operator*=(const inputT& v) { this->scale(v); return *this; }

      template <typename inputT>
      Type& operator+=(const inputT& v) { this->shift(v); return *this; }

      virtual const char* type() { return "Fixed Vector"; }

  };

  template <typename T, uint N>
  istream& operator>>(istream& is, fixVector<T,N>& v) {
    for(uint i=0;i<N;++i) is>>v[i];
    return is;
  }

}

#endif
