
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

#include "vec-array/expression-sum.h"
#include "vec-array/expression-substract.h"
#include "vec-array/expression-multiple.h"
#include "vec-array/expression-divide.h"

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
        ParentType::ParentTypeB::operator=((Array<Array<ET>> const&)A);
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
        ParentType::ParentTypeA::operator+=((Array<T> const&)A);
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
        ParentType::ParentTypeA::operator-=((Array<T> const&)A);
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
        ParentType::ParentTypeA::operator*=((Array<T> const&)A);
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
        ParentType::ParentTypeA::operator/=((Array<T> const&)A);
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

  };

}

#endif

