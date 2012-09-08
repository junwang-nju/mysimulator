
#ifndef _Array_Base_Interface_H_
#define _Array_Base_Interface_H_

#include <memory>
#include <cassert>

namespace mysimulator {

  template <typename T, typename TPtr>
  class ArrayBase {

    public:

      typedef ArrayBase<T,TPtr>  Type;

    private:

      TPtr         _pdata;
      unsigned int _ndata;

    public:

      ArrayBase() : _pdata(nullptr), _ndata(0U) {}
      ArrayBase(const Type&) = delete;
      ~ArrayBase() { Clear(); }

      void Clear() { _ndata=0; _pdata.reset(); }

      T& operator[](unsigned int i) {
        assert(i<_ndata);
        return _pdata[i];
      }
      const T& operator[](unsigned int i) const {
        assert(i<_ndata);
        return _pdata[i];
      }

    protected:

      Type& operator=(const Type& iA) {
        assert(_ndata>=iA._ndata);
      }

  };

}

#endif

