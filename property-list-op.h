
#ifndef _Property_List_Operation_H_
#define _Property_List_Operation_H_

#include "property-list.h"
#include "vector-op.h"

namespace std {

  template <template <typename> class vType>
  double dot(const PropertyList<vType>& P, const VectorBase<double>& v) {
    assert(vType<int>::IsVector);
    return dot(P.PropertyData,v);
  }

  template <template <typename> class vType>
  double dot(const VectorBase<double>& v, const PropertyList<vType>& P) {
    assert(vType<int>::IsVector);
    return dot(P.PropertyData,v);
  }

  template <template <typename> class vTypeA,
            template <typename> class vTypeB>
  double dot(const PropertyList<vTypeA>& Pa, const PropertyList<vTypeB>& Pb){
    assert((vTypeA<int>::IsVector)&&(vTypeB<int>::IsVector));
    return dot(Pa.PropertyData,Pb.PropertyData);
  }

  template <template <typename> class vType>
  double norm(const PropertyList<vType>& P) {
    assert(vType<int>::IsVector);
    return norm(P.PropertyData);
  }

  template <template <typename> class vType>
  double normSQ(const PropertyList<vType>& P) {
    assert(vType<int>::IsVector);
    return normSQ(P.PropertyData);
  }

  template <template <typename> class vType>
  double sumABS(const PropertyList<vType>& P) {
    assert(vType<int>::IsVector);
    return sumABS(P.PropertyData);
  }

}

#endif

