
#ifndef _Vector_Array_Interface_H_
#define _Vector_Array_Interface_H_

#include "vec-array/container.h"

namespace mysimulator {

  template <typename T>
  class VectorArray {
    public:
      typedef VectorArray<T>  Type;
      VectorArray() = delete;
      VectorArray(const Type&) = delete;
      VectorArray(Type&&) = delete;
      Type& operator=(const Type&) = delete;
      ~VectorArray() {}
  };

}

#include "vec-array/expression-operation.h"

namespace mysimulator {

  template <typename T>
  class VectorArray<Intrinsic<T>>
      : public VectorArrayContainer<Intrinsic<T>> {

    public:

      typedef VectorArray<Intrinsic<T>>  Type;
      typedef Array<Intrinsic<T>>  VecType;
      typedef VectorArrayContainer<Intrinsic<T>>   ParentType;
      typedef unsigned int size_type;

      VectorArray() : ParentType() {}
      VectorArray(size_type n,size_type d) : ParentType(n,d) {}
      VectorArray(const Type& A) : VectorArray() {
        ParentType::imprint((ParentType const&)A); operator=(A);
      }
      VectorArray(Type&& A) : ParentType((ParentType&&)A) {}
      ~VectorArray() { ParentType::reset(); }

      Type& operator=(const Type& A) {
        ParentType::operator=(A);
        return *this;
      }
      template <typename ET>
      Type& operator=(VectorArray<ET> const& A) {
        ParentType::ParentTypeB::operator=((Array<Array<Intrinsic<ET>>> const&)A);
        return *this;
      }
      Type& operator=(const T& D) {
        assert((bool)(*this));
        ParentType::ParentTypeA::operator=(D);
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((T)((T1)D));
      }

      template <typename EA,typename EB>
      Type& operator=(VecArraySum<EA,EB> const& RA) {
        operator=(RA.first());
        return operator+=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(VecArraySub<EA,EB> const& RA) {
        operator=(RA.first());
        return operator-=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(VecArrayMul<EA,EB> const& RA) {
        operator=(RA.first());
        return operator*=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(VecArrayDiv<EA,EB> const& RA) {
        operator=(RA.first());
        return operator/=(RA.second());
      }

      template <typename ET>
      Type& operator+=(const VectorArray<ET>& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]+=A[i];
        return *this;
      }
      Type& operator+=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A));
        ParentType::ParentTypeA::operator+=((Array<Intrinsic<T>> const&)A);
        return *this;
      }
      Type& operator+=(const T& D) {
        assert((bool)(*this));
        ParentType::ParentTypeA::operator+=(D);
        return *this;
      }
      template <typename T1>
      Type& operator+=(const Intrinsic<T1>& D) {
        return operator+=((T)((T1)D));
      } 

      template <typename EA,typename EB>
      Type& operator+=(VecArraySum<EA,EB> const& A) {
        operator+=(A.first());
        return operator+=(A.second());
      }
      template <typename EA,typename EB>
      Type& operator+=(VecArraySub<EA,EB> const& A) {
        operator+=(A.first());
        return operator-=(A.second());
      }
      template <typename EA,typename EB>
      Type& operator+=(VecArrayMul<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]+=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator+=(VecArrayDiv<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]+=A[i];
        return *this;
      }

      template <typename ET>
      Type& operator-=(const VectorArray<ET>& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]-=A[i];
        return *this;
      }
      Type& operator-=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A));
        ParentType::ParentTypeA::operator-=((Array<Intrinsic<T>> const&)A);
        return *this;
      }
      Type& operator-=(const T& D) {
        assert((bool)(*this));
        ParentType::ParentTypeA::operator-=(D);
        return *this;
      }
      template <typename T1>
      Type& operator-=(const Intrinsic<T1>& D) {
        return operator-=((T)((T1)D));
      } 

      template <typename EA,typename EB>
      Type& operator-=(VecArraySum<EA,EB> const& A) {
        operator-=(A.first());
        return operator-=(A.second());
      }
      template <typename EA,typename EB>
      Type& operator-=(VecArraySub<EA,EB> const& A) {
        operator-=(A.first());
        return operator+=(A.second());
      }
      template <typename EA,typename EB>
      Type& operator-=(VecArrayMul<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]-=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator-=(VecArrayDiv<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]-=A[i];
        return *this;
      }

      template <typename ET>
      Type& operator*=(const VectorArray<ET>& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]*=A[i];
        return *this;
      }
      Type& operator*=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A));
        ParentType::ParentTypeA::operator*=((Array<Intrinsic<T>> const&)A);
        return *this;
      }
      Type& operator*=(const T& D) {
        assert((bool)(*this));
        ParentType::ParentTypeA::operator*=(D);
        return *this;
      }
      template <typename T1>
      Type& operator*=(const Intrinsic<T1>& D) {
        return operator*=((T)((T1)D));
      } 

      template <typename EA,typename EB>
      Type& operator*=(VecArraySum<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]*=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator*=(VecArraySub<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]*=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator*=(VecArrayMul<EA,EB> const& A) {
        operator*=(A.first());
        return operator*=(A.second());
      }
      template <typename EA,typename EB>
      Type& operator*=(VecArrayDiv<EA,EB> const& A) {
        operator*=(A.first());
        return operator/=(A.second());
      }

      template <typename ET>
      Type& operator/=(const VectorArray<ET>& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]/=A[i];
        return *this;
      }
      Type& operator/=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A));
        ParentType::ParentTypeA::operator/=((Array<Intrinsic<T>> const&)A);
        return *this;
      }
      Type& operator/=(const T& D) {
        assert((bool)(*this));
        ParentType::ParentTypeA::operator/=(D);
        return *this;
      }
      template <typename T1>
      Type& operator/=(const Intrinsic<T1>& D) {
        return operator/=((T)((T1)D));
      } 

      template <typename EA,typename EB>
      Type& operator/=(VecArraySum<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]/=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator/=(VecArraySub<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]/=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator/=(VecArrayMul<EA,EB> const& A) {
        operator/=(A.first());
        return operator/=(A.second());
      }
      template <typename EA,typename EB>
      Type& operator/=(VecArrayDiv<EA,EB> const& A) {
        operator/=(A.first());
        return operator*=(A.second());
      }

      template <typename T1,typename T2>
      Type& operator+=(VecArrayMul<VectorArray<Intrinsic<T1>>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator+=(
              ((Array<Intrinsic<T1>> const&)A.first()) *
              ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator+=(VecArrayMul<VectorArray<Intrinsic<T1>>,
                                   Intrinsic<T2>> const& A) {
        assert((bool)(*this));
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        ParentType::ParentTypeA::operator+=(
              ((Array<Intrinsic<T1>> const&)A.first()) * A.second());
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator+=(VecArrayMul<Intrinsic<T1>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator+=(
              A.first() * ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator+=(VecArrayDiv<VectorArray<Intrinsic<T1>>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator+=(
              ((Array<Intrinsic<T1>> const&)A.first()) /
              ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator+=(VecArrayDiv<VectorArray<Intrinsic<T1>>,
                                   Intrinsic<T2>> const& A) {
        assert((bool)(*this));
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        ParentType::ParentTypeA::operator+=(
              ((Array<Intrinsic<T1>> const&)A.first()) / A.second());
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator+=(VecArrayDiv<Intrinsic<T1>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator+=(
              A.first() / ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }

      template <typename T1,typename T2>
      Type& operator-=(VecArrayMul<VectorArray<Intrinsic<T1>>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator-=(
              ((Array<Intrinsic<T1>> const&)A.first()) *
              ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator-=(VecArrayMul<VectorArray<Intrinsic<T1>>,
                                   Intrinsic<T2>> const& A) {
        assert((bool)(*this));
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        ParentType::ParentTypeA::operator-=(
              ((Array<Intrinsic<T1>> const&)A.first()) * A.second());
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator-=(VecArrayMul<Intrinsic<T1>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator-=(
              A.first() * ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator-=(VecArrayDiv<VectorArray<Intrinsic<T1>>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator-=(
              ((Array<Intrinsic<T1>> const&)A.first()) /
              ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator-=(VecArrayDiv<VectorArray<Intrinsic<T1>>,
                                   Intrinsic<T2>> const& A) {
        assert((bool)(*this));
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        ParentType::ParentTypeA::operator-=(
              ((Array<Intrinsic<T1>> const&)A.first()) / A.second());
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator-=(VecArrayDiv<Intrinsic<T1>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator-=(
              A.first() / ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }

      template <typename T1,typename T2>
      Type& operator*=(VecArraySum<VectorArray<Intrinsic<T1>>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator*=(
              ((Array<Intrinsic<T1>> const&)A.first()) +
              ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator*=(VecArraySum<VectorArray<Intrinsic<T1>>,
                                   Intrinsic<T2>> const& A) {
        assert((bool)(*this));
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        ParentType::ParentTypeA::operator*=(
              ((Array<Intrinsic<T1>> const&)A.first()) + A.second());
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator*=(VecArraySum<Intrinsic<T1>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator*=(
              A.first() + ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator*=(VecArraySub<VectorArray<Intrinsic<T1>>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator*=(
              ((Array<Intrinsic<T1>> const&)A.first()) -
              ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator*=(VecArraySub<VectorArray<Intrinsic<T1>>,
                                   Intrinsic<T2>> const& A) {
        assert((bool)(*this));
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        ParentType::ParentTypeA::operator*=(
              ((Array<Intrinsic<T1>> const&)A.first()) - A.second());
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator*=(VecArraySub<Intrinsic<T1>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator*=(
              A.first() - ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }

      template <typename T1,typename T2>
      Type& operator/=(VecArraySum<VectorArray<Intrinsic<T1>>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator/=(
              ((Array<Intrinsic<T1>> const&)A.first()) +
              ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator/=(VecArraySum<VectorArray<Intrinsic<T1>>,
                                   Intrinsic<T2>> const& A) {
        assert((bool)(*this));
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        ParentType::ParentTypeA::operator/=(
              ((Array<Intrinsic<T1>> const&)A.first()) + A.second());
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator/=(VecArraySum<Intrinsic<T1>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator/=(
              A.first() + ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator/=(VecArraySub<VectorArray<Intrinsic<T1>>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator/=(
              ((Array<Intrinsic<T1>> const&)A.first()) -
              ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator/=(VecArraySub<VectorArray<Intrinsic<T1>>,
                                   Intrinsic<T2>> const& A) {
        assert((bool)(*this));
        assert(ParentType::_is_same_size((ParentType const&)A.first()));
        ParentType::ParentTypeA::operator/=(
              ((Array<Intrinsic<T1>> const&)A.first()) - A.second());
        return *this;
      }
      template <typename T1,typename T2>
      Type& operator/=(VecArraySub<Intrinsic<T1>,
                                   VectorArray<Intrinsic<T2>>> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::_is_same_size((ParentType const&)A.second()));
        ParentType::ParentTypeA::operator/=(
              A.first() - ((Array<Intrinsic<T2>> const&)A.second()));
        return *this;
      }

  };

  template <typename T1,typename T2>
  typename __dual_selector<T1,T2,__mul_flag>::Type
  Dot(VectorArray<Intrinsic<T1>> const& A, VectorArray<Intrinsic<T2>> const& B){
    assert((bool)A);
    assert((bool)B);
    assert(A._is_same_size(B));
    return Dot((Array<Intrinsic<T1>> const&)A,
               (Array<Intrinsic<T2>> const&)B);
  }

}

#endif

