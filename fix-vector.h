
#ifndef _Fixed_Vector_H_
#define _Fixed_Vector_H_

#include "vector-impl.cc"

namespace std {

  template <typename T>
  class varVector;

  template <typename T, uint ND>
  class fixVector {
    public:
      typedef T                 DataType;
      typedef fixVector<T,ND>   Type;
      static long nData=ND;
    private:
      T Data[ND];
      T* head_ptr;
      T* tail_ptr;
    public:
      fixVector() : Data(), head_ptr(Data), tail_ptr(Data+ND) {}

      T& operator[](const uint i) {
        assert(i<ND);
        return *(Data+i);
      }

      const T& operator[](const uint i) const {
        assert(i<ND);
        return *(Data+i);
      }

      const uint& size() const { return nData; }
  };

}

#endif
