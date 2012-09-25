
#ifndef _Array_Base_Interface_H_
#define _Array_Base_Interface_H_

#include <cassert>

namespace mysimulator {

  template <typename T, typename TPtr>
  class ArrayBase {

    public:

      typedef ArrayBase<T,TPtr>  Type;

    protected:

      TPtr         _pdata;
      unsigned int _ndata;

    public:

      ArrayBase() : _pdata(nullptr), _ndata(0U) {}
      ArrayBase(const Type&) = delete;
      ~ArrayBase() { Clear(); }

      void Clear() { _ndata=0; if((bool)_pdata) _pdata.reset(); }
      unsigned int Size() const { return _ndata; }

      T& operator[](unsigned int i) {
        assert(i<_ndata);
        return *(_pdata.get()+i);
      }
      const T& operator[](unsigned int i) const {
        assert(i<_ndata);
        return *(_pdata.get()+i);
      }

      Type& operator=(const Type& iA) {
        assert(_ndata<=iA._ndata);
        return *this;
      }

  };

}

#endif

