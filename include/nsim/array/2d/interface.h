
#ifndef _Array_2D_Interface_H_
#define _Array_2D_Interface_H_

#include "array/1d/sum.h"

namespace mysimulator {

  template <typename T>
  struct Array2D : public Array1D<Array1D<T> > {

    public:

      typedef Array2D<T>  Type;
      typedef Array1D<Array1D<T> > ParentType;

      Array1D<T> _ldata;

      Array2D() : ParentType(), _ldata() {}
      ~Array2D() { Clear(); }

      void Clear() {
        static_cast<ParentType*>(this)->Clear();
        _ldata.Clear();
      }
      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               _ldata.IsValid();
      }

      void Allocate(const Array1D<unsigned int>& sz) {
        Clear();
        static_cast<ParentType*>(this)->Allocate(sz.Size());
        _ldata.Allocate(Sum(sz));
        for(unsigned int i=0,m=0;i<sz.Size();m+=sz[i],++i)
          static_cast<ParentType*>(this)->operator[](i).Refer(_ldata,m,sz[i]);
      }
      void Refer(Type& V, unsigned int b, unsigned int n) {
        Clear();
        static_cast<ParentType*>(this)->Refer(static_cast<ParentType&>(V),b,n);
        unsigned int bl,nl;
        T* ptr=V[b]._data;
        bl=static_cast<unsigned int>(ptr-V[0]._data);
        nl=(b+n<this->_size?static_cast<unsigned int>(V[b+n]._data-ptr):
                            _ldata._size-bl);
        _ldata.Refer(V._ldata,bl,nl);
      }
      void Refer(Type& V) {
        static_cast<ParentType*>(this)->Refer(static_cast<ParentType&>(V));
        _ldata.Refer(V._ldata);
      }

    private:

      Array2D(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

