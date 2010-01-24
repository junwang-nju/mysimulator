
#ifndef _Vector_Base_Basic_H_
#define _Vector_Base_Basic_H_

#include "error-proc.h"
#include "constant.h"

namespace std {
  template <typename T>
  class VectorBaseBasic {
    protected:
      T* Data;
      unsigned int nData;
      T* headPtr;
      T* tailPtr;
    public:
      typedef T   DataType;
      typedef VectorBaseBasic<T>  Type;
      static const bool IsVector;
      VectorBaseBasic() : Data(NULL), nData(0), headPtr(NULL), tailPtr(NULL) {}
      VectorBaseBasic(const Type& V) {
        myError("Cannot create from VectorBaseBasic");
      }
      virtual ~VectorBaseBasic() { clear(); }
      Type& operator=(const Type& V) { return assign(V); }
      template <typename inputT>
      Type& operator=(const inputT& V) { return assign(V); }
      T* data();
      const T* data() const;
      const T* begin() const;
      const T* end() const;
      const unsigned int& size() const;
      T& operator[](const unsigned int& I);
      const T& operator[](const unsigned int& I) const;
      void clear();
      void SetHeadTail();
      const bool IsAvailable() const;
      Type& assign(const Type& V);
      Type& assign(const T& value);
      Type& assign(const Type& V, long ncopy, int voff=iZero, long vstep=lOne,
                                              int off=iZero, long step=lOne);
      Type& assign(const T& V, long ncopy, int off=iZero, long step=lOne);
      Type& exchange(Type& V);
      Type& exchange(Type& V, long nex, int voff=iZero, long vstep=lOne,
                                        int off=iZero, long step=lOne);
      virtual const char* type() = 0;
  };
  template <typename T>
  const bool VectorBaseBasic<T>::IsVector=true;
}

#endif

