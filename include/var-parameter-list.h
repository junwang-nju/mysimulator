
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
        this->ptrhashtree()=new fixVector<TreeType,N>;
      }

      void allocate(const VectorBase<unsigned int> KeySize,
                    const VectorBase<unsigned int> ValueSize,
                    const unsigned int N,
                    unsigned int koff=uZero, unsigned int kstep=uOne,
                    unsigned int voff=uZero, unsigned int vstep=uOne) {
        assert(koff+N*kstep<=KeySize.size());
        assert(voff+N*vstep<=ValueSize.size());
        allocate(N);
        for(unsigned int i=0,j=koff,k=voff;i<N;++i,j+=kstep,k+=vstep) {
          this->keylist().allocate(KeySize[j]);
          this->valuelist().allocate(ValueSize[k]);
        }
      }

      void allocate(const VectorBase<unsigned int> KeySize,
                    const VectorBase<unsigned int> ValueSize) {
        unsigned int n;
        n=(KeySize.size()<ValueSize.size()?KeySize.size():ValueSize.size());
        allocate(KeySize,ValueSize,n);
      }

  };

}

#endif

