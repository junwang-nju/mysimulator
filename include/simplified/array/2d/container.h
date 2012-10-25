
#ifndef _Array_2D_Container_H_
#define _Array_2D_Container_H_

#include "array/2d/container-base.h"

namespace mysimulator {

  template <typename T>
  class Array2DContainer : private Array<T>, public Array2DContainerBase<T> {

    public:

      typedef Array2DContainer<T>   Type;
      typedef Array<T>  ParentTypeA;
      typedef Array2DContainerBase<T> ParentTypeB;
      typedef unsigned int size_type;
      typedef Array<T>  vec_type;
      typedef vec_type& vreference;
      typedef vec_type const& const_vreference;

      Array2DContainer() : ParentTypeA(), ParentTypeB() {}
      Array2DContainer(size_type m,size_type n) : Array2DContainer() {
        allocate(m,n);
      }
      Array2DContainer(const Type&) = delete;
      Array2DContainer(Type&& A) : ParentTypeA((ParentTypeA&&)A),
                                   ParentTypeB((ParentTypeB&&)A) {}
      ~Array2DContainer() { reset(); }

      operator bool() const {
        return ParentTypeA::operator bool() &&
               ParentTypeB::operator bool();
      }
      size_type size() const { return ParentTypeB::size(); }
      vreference operator[](size_type i) { return ParentTypeB::operator[](i); }
      const_vreference operator[](size_type i) const {
        return ParentTypeB::operator[](i);
      }
      void reset() { ParentTypeB::reset(); ParentTypeA::reset(); }

      void allocate(size_type m, size_type n) {
        reset();
        ParentTypeA::allocate(m*n);
        ParentTypeB::allocate(m);
        for(size_type i=0,w=0;i<m;++i,w+=n)
          ParentTypeB::operator[](i).refer((ParentTypeA const&)(*this),w,n);
      }
      void allocate(Array<UInt> const& sarray) {
        reset();
        size_type m=sarray.size();
        size_type n=0;
        for(size_type i=0;i<m;++i) n+=sarray[i]; // could be update!!
        ParentTypeA::allocate(n);
        ParentTypeB::allocate(m);
        for(size_type i=0,w=0;i<m;w+=sarray[i++])
          ParentTypeB::operator[](i).refer((ParentTypeA const&)(*this),
                                           w,sarray[i]);
      }

      void refer(const Type& A) {
        reset();
        ParentTypeA::refer((ParentTypeA const&)A);
        ParentTypeB::refer((ParentTypeB const&)A);
      }
      void refer(const Type& A,size_type bg,size_type num) {
        reset();
        ParentTypeB::refer((ParentTypeB const&)A,bg,num);
        size_type y=(A[bg].head()-A[0].head());
        size_type w=(A[bg+num-1].head()-A[bg].head())+A[bg+num-1].size();
        ParentTypeA::refer((ParentTypeA const&)A,y,w);
      }
      template <typename Y>
      void imprint(const Array2DContainer<Y>& A) {
        ParentTypeA::imprint((ParentTypeA const&)A);
        ParentTypeB::imprint_structure((ParentTypeB const&)A);
        for(size_type i=0,w=0;i<size();w+=A[i++].size())
          ParentTypeB::operator[](i).refer((ParentTypeA const&)(*this),
                                           w,A[i].size());
      }
      template <typename Y>
      void imprint_structure(const Array2DContainer<Y>& A) {
        ParentTypeA::imprint_structure((ParentTypeA const&)A);
        ParentTypeB::imprint_structure((ParentTypeB const&)A);
        for(size_type i=0,w=0;i<size();w+=A[i++].size())
          ParentTypeB::operator[](i).refer((ParentTypeA const&)(*this),
                                           w,A[i].size());
      }
      void swap(Type& A) {
        ParentTypeA::swap((ParentTypeA&)A);
        ParentTypeB::swap((ParentTypeB&)A);
      }

  };

  template <typename T>
  class Array2DContainer<Intrinsic<T>>
      : private Array<Intrinsic<T>>,
        public Array2DContainerBase<Intrinsic<T>> {

    public:

      typedef Array2DContainer<Intrinsic<T>>  Type;
      typedef Array<Intrinsic<T>>   ParentTypeA;
      typedef Array2DContainerBase<Intrinsic<T>>  ParentTypeB;
      typedef unsigned int size_type;
      typedef Array<Intrinsic<T>>  vec_type;
      typedef vec_type& vreference;
      typedef vec_type const& const_vreference;

      Array2DContainer() : ParentTypeA(), ParentTypeB() {}
      Array2DContainer(size_type m,size_type n) : Array2DContainer() {
        allocate(m,n);
      }
      Array2DContainer(const Type&) = delete;
      Array2DContainer(Type&& A) : ParentTypeA((ParentTypeA&&)A),
                                   ParentTypeB((ParentTypeB&&)A) {}
      ~Array2DContainer() { reset(); }

      operator bool() const {
        return ParentTypeA::operator bool() &&
               ParentTypeB::operator bool();
      }
      size_type size() const { return ParentTypeB::size(); }
      vreference operator[](size_type i) { return ParentTypeB::operator[](i); }
      const_vreference operator[](size_type i) const {
        return ParentTypeB::operator[](i);
      }
      void reset() { ParentTypeB::reset(); ParentTypeA::reset(); }

      void allocate(size_type m, size_type n) {
        reset();
        size_type rn=__span16(n);
        ParentTypeA::allocate(m*rn);
        ParentTypeB::allocate(m);
        for(size_type i=0,w=0;i<m;++i,w+=rn)
          ParentTypeB::operator[](i)._refer((ParentTypeA const&)(*this),w,n);
      }
      void allocate(Array<UInt> const& sarray) {
        reset();
        size_type m=sarray.size();
        size_type n=0;
        for(size_type i=0;i<m;++i) n+=__span16(sarray[i]); // could be update!!
        ParentTypeA::allocate(n);
        ParentTypeB::allocate(m);
        for(size_type i=0,w=0;i<m;w+=__span16(sarray[i++]))
          ParentTypeB::operator[](i)._refer((ParentTypeA const&)(*this),
                                            w,sarray[i]);
      }

      void refer(const Type& A) {
        reset();
        ParentTypeA::refer((ParentTypeA const&)A);
        ParentTypeB::refer((ParentTypeB const&)A);
      }
      void refer(const Type& A,size_type bg,size_type num) {
        reset();
        ParentTypeB::refer((ParentTypeB const&)A,bg,num);
        size_type y=(A[bg].head()-A[0].head());
        size_type w=(A[bg+num-1].head()-A[bg].head())+A[bg+num-1].size();
        ParentTypeA::_refer((ParentTypeA const&)A,y,w);
      }
      template <typename Y>
      void imprint(const Array2DContainer<Y>& A) {
        Array<UInt> SZ;
        SZ.allocate(A.size());
        for(size_type i=0;i<A.size();++i) SZ[i]=A[i].size();
        allocate(SZ);
      }
      template <typename Y>
      void imprint_structure(const Array2DContainer<Y>& A) { imprint(A); }
      void swap(Type& A) {
        ParentTypeA::swap((ParentTypeA&)A);
        ParentTypeB::swap((ParentTypeB&)A);
      }

    private:

      size_type __span16(size_type n) { // may shift to basic
        size_type nbyte=n*sizeof(T);
        return ((nbyte&(~0xFU))+((nbyte&0xFU)==0?0:16))/sizeof(T);
      }

  };

}

namespace std {

  template <typename T>
  void swap(mysimulator::Array2DContainer<T>& A1,
            mysimulator::Array2DContainer<T>& A2) {
    A1.swap(A2);
  }

}

#endif

