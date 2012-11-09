
#ifndef _System_Hessian_Interface_H_
#define _System_Hessian_Interface_H_

#include "vec-array/interface.h"
#include "system/kind/coordinate-size.h"

namespace mysimulator {

  template <typename T>
  class Hessian {
    public:
      typedef Hessian<T>  Type;
      Hessian() = delete;
      Hessian(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~Hessian() {}
  };

  template <typename T>
  class Hessian<Intrinsic<T>> {

    public:

      static_assert(__float_point_flag<T>::FG,
                    "Hessian Only works for Floating-Point cases!\n");

      typedef Hessian<Intrinsic<T>>    Type;
      typedef unsigned int size_type;

    private:

      VectorArray<Intrinsic<T>>   _data;
      Array<UInt> idx;

    public:

      Hessian() : _data(), idx() {}
      Hessian(const Type& H) : _data(H._data), idx(H.idx) {}
      Hessian(Type&& H) : Hessian() { swap(H); }
      Hessian(Array<SystemKindName> const& K,unsigned int dim) : Hessian() {
        allocate(K,dim);
      }
      ~Hessian() { reset(); }

      operator bool() const { return (bool)_data && (bool)idx; }
      void reset() { _data.reset(); idx.reset(); }

      Type& operator=(const Type& H) {
        assert((bool)(*this));
        assert((bool)H);
        _data=H._data;
        idx=H.idx;
        return *this;
      }
      Type& operator=(const T& D) { _data=D; }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) { _data=D; }

      T& operator()(size_type i,size_type xi,size_type j,size_type xj) {
        return _data[idx[i]+xi][idx[j]+xj];
      }
      const T& operator()(size_type i,size_type xi,
                          size_type j,size_type xj) const {
        return _data[idx[i]+xi][idx[j]+xj];
      }

      void allocate(Array<SystemKindName> const& K,unsigned int dim) {
        assert((bool)K);
        reset();
        Array<UInt> SZ(K.size());
        for(size_type i=0;i<K.size();++i) SZ[i]=CoordinateSize<T>(K[i],dim);
        idx.allocate(SZ.size());
        idx[0]=0;
        for(size_type i=1;i<K.size();++i) idx[i]=idx[i]+SZ[i-1];
        unsigned int DIM=idx[idx.size()-1]+SZ[SZ.size()-1];
        _data.allocate(DIM,DIM);
        SZ.reset();
      }

      void swap(Hessian<Intrinsic<T>>& H) {
        std::swap(_data,H._data);
        std::swap(idx,H.idx);
      }


  };

}

namespace std {

  template <typename T>
  void swap(mysimulator::Hessian<mysimulator::Intrinsic<T>>& H1,
            mysimulator::Hessian<mysimulator::Intrinsic<T>>& H2) {
    H1.swap(H2);
  }

}

#endif

