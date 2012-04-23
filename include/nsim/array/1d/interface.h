
#ifndef _Array_1D_Interface_H_
#define _Array_1D_Interface_H_

#include <cstdio>
#include <cstdlib>
#include <cassert>

namespace mysimulator {

  template <typename T>
  struct Array1D {

    public:

      typedef Array1D<T>  Type;

      T* _data;
      unsigned int _size;
      unsigned int *_refCount;
      unsigned int *_partUsed;
      bool _partFlag;

      Array1D() : _data(NULL), _size(0), _refCount(NULL), _partUsed(NULL),
                  _partFlag(false) {}
      ~Array1D() { Clear(*this); }

      bool IsValid() const { return _data!=NULL; }
      unsigned int Size() const { return _size; }

      T& operator[](unsigned int n) { assert(n<_size); return _data[n]; }
      const T& operator[](unsigned int n) const {
        assert(n<_size); return _data[n];
      }

      void Allocate(unsigned int n=1) {
        assert(n>0);
        Clear(*this);
        _data=new T[n];
        _size=n;
        _refCount=new unsigned int;
        *_refCount=0;
        _partUsed=new unsigned int;
        *_partUsed=0;
        _partFlag=false;
      }
      void Refer(Type& V, unsigned int b, unsigned int n) {
        assert(V.IsValid());
        assert(b+n<=V.Size());
        Clear(*this);
        _data=V._data+b;
        _size=n;
        _refCount=V._refCount;
        ++(*_refCount);
        _partUsed=V._partUsed;
        _partFlag=(V._partFlag?true:((b==0)&&(n==V._size)?false:true));
        if(_partFlag) ++(*_partUsed);
      }
      void Refer(Type& V) { Refer(V,0U,V.Size()); }

    private:

      Array1D(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#include "intrinsic-type/clear.h"

namespace mysimulator {

  template <typename T>
  void Clear(Array1D<T>& V) {
    if(!V.IsValid())  return;
    for(unsigned int i=0;i<V.Size();++i) Clear(V[i]);
    if(V._partFlag) { --(*V._refCount);  --(*V._partUsed); }
    else {
      if(*V._partUsed!=0) {
        fprintf(stderr,"Need to Free Part Content First!\n");
        exit(0);
      }
      if(*V._refCount==0) {
        delete[] V._data; delete V._refCount; delete V._partUsed;
      } else --(*V._refCount);
    }
    V._partFlag=false;
    V._partUsed=NULL;
    V._refCount=NULL;
    V._size=0;
    V._data=NULL;
  }

}

#endif

