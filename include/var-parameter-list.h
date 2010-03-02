
#ifndef _Variable_Parameter_List_H_
#define _Variable_Parameter_List_H_

#include "parameter-list-base.h"

namespace std {

  class varParameterList : public ParameterListBase<varVector> {

    public:

      typedef varParameterList    Type;

      typedef ParameterListBase<varVector>  ParentType;

      varParameterList() : ParentType() {}

      varParameterList(const unsigned int N) : ParentType() { allocate(N); }

      varParameterList(const Type&) {
        myError("Cannot create from variable Parameter List");
      }

      ~varParameterList() {
        static_cast<ParentType*>(this)->clearHashTree();
        safe_delete(this->ptrhashtree());
        for(unsigned int i=0;i<this->keylist().size();++i) {
          this->keylist()[i].clear();
          this->valuelist()[i].clear();
        }
      }

      void clear() {
        static_cast<ParentType*>(this)->clearHashTree();
        safe_delete(this->ptrhashtree());
        for(unsigned int i=0;i<this->keylist().size();++i) {
          this->keylist()[i].clear();
          this->valuelist()[i].clear();
        }
        static_cast<ParentType*>(this)->clear();
      }

      Type& operator=(const Type& vPL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vPL));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const ParameterListBase<VecType>& PL) {
        static_cast<ParentType*>(this)->operator=(PL);
        return *this;
      }

      void allocate(const unsigned int N) {
        this->keylist().allocate(N);
        this->valuelist().allocate(N);
        this->ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
      }

    protected:

      template <typename T>
      void allocateList(varVector<T>& List,
                        const unsigned int Size, const unsigned int N) {
        List.allocate(N);
        for(unsigned int i=0;i<N;++i) List[i].allocate(Size);
      }

      template <typename T>
      void allocateList(varVector<T>& List,
                        const VectorBase<unsigned int>& Size,
                        const unsigned int N,
                        const unsigned int off=uZero,
                        const unsigned int step=uOne) {
        assert(off+N*step<=Size.size());
        List.allocate(N);
        for(unsigned int i=0,n=off;i<N;++i,n+=step) List[i].allocate(Size[n]);
      }

    public:

      void allocate(const unsigned int kSize, const unsigned int vSize,
                    const unsigned int N) {
        allocateList(this->keylist(),kSize,N);
        allocateList(this->valuelist(),vSize,N);
        this->ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
      }

      void allocate(const unsigned int kSize,
                    const VectorBase<unsigned int>& vSize,
                    const unsigned int N,
                    const unsigned int voff=uZero,
                    const unsigned int vstep=uOne) {
        allocateList(this->keylist(),kSize,N);
        allocateList(this->valuelist(),vSize,N,voff,vstep);
        this->ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
      }

      void allocate(const VectorBase<unsigned int>& kSize,
                    const unsigned int vSize, const unsigned int N,
                    const unsigned int koff=uZero,
                    const unsigned int kstep=uOne) {
        allocateList(this->keylist(),kSize,N,koff,kstep);
        allocateList(this->valuelist(),vSize,N);
        this->ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
      }

      void allocate(const VectorBase<unsigned int>& kSize,
                    const VectorBase<unsigned int>& vSize,
                    const unsigned int N,
                    unsigned int koff=uZero, unsigned int kstep=uOne,
                    unsigned int voff=uZero, unsigned int vstep=uOne) {
        allocateList(this->keylist(),kSize,N,koff,kstep);
        allocateList(this->valuelist(),vSize,N,voff,vstep);
        this->ptrhashtree()=new fixVector<TreeType,0xFFFFU>;
      }

      void allocate(const unsigned int kSize,
                    const VectorBase<unsigned int>& vSize) {
        allocate(kSize,vSize,vSize.size());
      }

      void allocate(const VectorBase<unsigned int>& kSize,
                    const unsigned int vSize) {
        allocate(kSize,vSize,kSize.size());
      }

      void allocate(const VectorBase<unsigned int>& kSize,
                    const VectorBase<unsigned int>& vSize) {
        unsigned int n;
        n=(kSize.size()<vSize.size()?kSize.size():vSize.size());
        allocate(kSize,vSize,n);
      }

  };

}

#endif

