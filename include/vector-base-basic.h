
#ifndef _Vector_Base_Basic_H_
#define _Vector_Base_Basic_H_

#include "error-proc.h"
#include "constant.h"

namespace std {
  template <typename T>
  class VectorBaseBasic {
    protected:
      bool IsSwappable;
      T* Data;
      unsigned int nData;
      T* headPtr;
      T* tailPtr;
    public:
      typedef T   DataType;
      typedef VectorBaseBasic<T>  Type;
      static const bool IsVector;
      VectorBaseBasic()
        : IsSwappable(false),
          Data(NULL), nData(0), headPtr(NULL), tailPtr(NULL) {}
      VectorBaseBasic(const Type& V) {
        myError("Cannot create from VectorBaseBasic");
      }
      virtual ~VectorBaseBasic() { clear(); }
      Type& operator=(const Type& V) { assign(V); return *this; }
      template <typename inputT>
      Type& operator=(const inputT& V) { assign(V); return *this; }
      T* data();
      const T* data() const;
      const T* begin() const;
      const T* end() const;
      const unsigned int& size() const;
      T& operator[](const unsigned int& I);
      const T& operator[](const unsigned int& I) const;
      void clear();
      void SetSize(const unsigned int N);
      void SetHeadTail();
      void SetSwapFlag(const bool& fg);
      const bool IsAvailable() const;
      void assign(const Type& V);
      void assign(const T& value);
      void assign(const Type& V, long ncopy, int voff=iZero, long vstep=lOne,
                                             int off=iZero, long step=lOne);
      void assign(const T& V, long ncopy, int off=iZero, long step=lOne);
      void exchange(Type& V);
      void exchange(Type& V, long nex, int voff=iZero, long vstep=lOne,
                                       int off=iZero, long step=lOne);
      void swap(Type& V);
      virtual const char* type() const = 0;
  };
  template <typename T>
  const bool VectorBaseBasic<T>::IsVector=true;
  template <typename T>
  istream& operator>>(istream& is, VectorBaseBasic<T>& V);
  template <typename T>
  ostream& operator<<(ostream& os, const VectorBaseBasic<T>& V);
}

#endif

