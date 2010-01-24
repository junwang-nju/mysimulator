
#include "vector-base.h"
#include "vector-impl.h"

namespace std {

  template<>
  VectorBase<double>& VectorBase<double>::scale(const VectorBase<double>& V) {
    long n=(nData<V.nData?nData:V.nData);
    return scale(V,n);
  }

  template <>
  VectorBase<double>& VectorBase<double>::scale(const double value) {
    return scale(value,nData);
  }

  template <>
  VectorBase<double>& VectorBase<double>::scale(
      const Type& V, long nsc, int voff, long vstep, int off, long step) {
    assert(static_cast<unsigned int>(voff+vstep*nsc)<V.nData);
    assert(static_cast<unsigned int>(off+step*nsc)<nData);
    vector_scale(Data,V.Data,nsc,voff,vstep,off,step);
    return *this;
  }

  template <>
  VectorBase<double>& VectorBase<double>::scale(
      const double& value, long nsc, int off, long step) {
    assert(static_cast<unsigned int>(off+step*nsc)<nData);
    vector_scale(Data,&value,nsc,iZero,lZero,off,step);
    return *this;
  }

}