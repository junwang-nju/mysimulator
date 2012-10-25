
#ifndef _Array_2D_Container_Base_H_
#define _Array_2D_Container_Base_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  class Array2DContainerBase : public Array<Array<T>> {

    public:

      typedef Array2DContainerBase<T>   Type;
      typedef Array<Array<T>>   ParentType;
      typedef unsigned int size_type;
      typedef typename ArrayContentSelector<T>::monomer_type monomer_type;
      typedef monomer_type& reference;
      typedef monomer_type const& const_reference;

      Array2DContainerBase() : ParentType() {}
      Array2DContainerBase(const Type&) = delete;
      Array2DContainerBase(Type&& A) : ParentType((ParentType&&)A) {}
      ~Array2DContainerBase() { ParentType::reset(); }

      Type& operator=(const Type& A) { return ParentType::operator=(A); }

      reference operator()(size_type i,size_type j) {
        return (ParentType::operator[](i))[j];
      }
      const_reference operator()(size_type i,size_type j) const {
        return (ParentType::operator[](i))[j];
      }

  };

}

#endif

