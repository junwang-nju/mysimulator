
#ifndef _Vector_Array_Container_H_
#define _Vector_Array_Container_H_

#include "array/interface.h"
#include "basic/align.h"

namespace mysimulator {

  template <typename T>
  class VectorArrayContainer : protected Array<T>, public Array<Array<T>> {

    public:

      typedef VectorArrayContainer<T>   Type;
      typedef Array<T>  ParentTypeA;
      typedef Array<Array<T>>   ParentTypeB;
      typedef unsigned int size_type;

      VectorArrayContainer() : ParentTypeA(), ParentTypeB() {}
      VectorArrayContainer(size_type n,size_type dim) : VectorArrayContainer() {
        allocate(n,dim);
      }
      VectorArrayContainer(const Type&) = delete;
      VectorArrayContainer(Type&& C) : VectorArrayContainer() {
        ParentTypeA::swap((ParentTypeA&&)C);
        ParentTypeB::swap((ParentTypeB&&)C);
      }
      ~VectorArrayContainer() { reset(); }

      operator bool() const {
        return ParentTypeA::operator bool() && ParentTypeB::operator bool();
      }
      size_type size() const { return ParentTypeB::size(); }
      Array<T>& operator[](size_type i) { return ParentTypeB::operator[](i); }
      Array<T> const& operator[](size_type i) const {
        return ParentTypeB::operator[](i);
      }
      template <typename Y>
      bool _is_same_size(VectorArrayContainer<Y> const& A) const {
        if(size()!=A.size())  return false;
        for(size_type i=0;i<size();++i)
          if((*this)[i].size()!=A[i].size())  return false;
        return true;
      }
      void reset() { ParentTypeB::reset(); ParentTypeA::reset(); }

      void allocate(size_type n, size_type dim) {
        size_type rdim=__span16<T>(dim);
        reset();
        ParentTypeA::allocate(n*rdim);
        ParentTypeB::allocate(n);
        for(size_type i=0,w=0;i<n;w+=rdim,++i)
          operator[](i)._refer((ParentTypeA const&)(*this),w,dim);
      }
      template <typename Y>
      void allocate(Array<Intrinsic<Y>> const& SZ) {
        static_assert(Intrinsic<Y>::IsInteger,
                      "Only Integer permitted as size for allocation!\n");
        assert((bool)SZ);
        Array<UInt> rSZ(SZ.size());
        size_type m=0;
        for(size_type i=0;i<SZ.size();++i) {
          assert(SZ[i]>0);
          rSZ[i]=__span16<T>(SZ[i]);
          m+=rSZ[i];
        }
        reset();
        ParentTypeA::allocate(m);
        ParentTypeB::allocate(SZ.size());
        for(size_type i=0,w=0;i<size();w+=rSZ[i++])
          operator[](i)._refer((ParentTypeA const&)(*this),w,SZ[i]);
        rSZ.reset();
      }

      void refer(Type const& A) {
        assert((bool)A);
        reset();
        ParentTypeA::refer((ParentTypeA const&)A);
        ParentTypeB::refer((ParentTypeB const&)A);
      }
      void refer(Type const& A,size_type bg,size_type num) {
        assert((bool)A);
        reset();
        ParentTypeB::refer((ParentTypeB const&)A,bg,num);
        size_type y=(A[bg].head()-A[0].head());
        size_type w=(A[bg+num-1].head()-A[bg].head())+A[bg+num-1].size();
        ParentTypeA::_refer((ParentTypeA const&)A,y,w);
      }
      template <typename Y>
      void imprint(VectorArrayContainer<Y> const& A) {
        assert((bool)A);
        Array<UInt> SZ(A.size());
        for(size_type i=0;i<A.size();++i) SZ[i]=A[i].size();
        allocate(SZ);
        SZ.reset();
      }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(_is_same_size(A));
        ParentTypeA::operator=((ParentTypeA const&)A);
        return *this;
      }
      Type& operator=(const T& D) {
        assert((bool)(*this));
        ParentTypeA::operator=(D);
        return *this;
      }

  };

}

#endif

