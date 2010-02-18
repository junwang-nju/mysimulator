
#ifndef _Variable_Parameter_List_H_
#define _Variable_Parameter_List_H_

#include "parameter-list-base.h"
#include "object-with-storage.h"
#include "var-vector.h"
#include "fix-vector.h"

namespace std {

  class varParameterList :public ObjectWStorage<ParameterListBase<varVector> >{

    public:
    
      typedef varParameterList    Type;
      
      typedef ObjectWStorage<ParameterListBase<varVector> >   ParentType;

    protected:
    
      fixVector<NodeType,0xFFFF>  HashTreeData;

    public:

      varParameterList() : ParentType(), HashTreeData() {
        HashTree.refer(HashTreeData);
      }

      varParameterList(const Type& PL) {
        myError("Cannot create with variable parameter list");
      }

      virtual ~varParameterList() { this->clear(); }

      Type& operator=(const Type& P) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(P));
        return *this;
      }

      void allocate(const unsigned int N) {
        KeyList.allocate(N);
        ValueList.allocate(N);
        this->clearHashTree();
      }

      void allocate(const VectorBase<unsigned int>& KeySize,
                    const VectorBase<unsigned int>& ValueSize,
                    const unsigned int N,
                    unsigned int koff=uZero, unsigned int kstep=uOne,
                    unsigned int voff=uZero, unsigned int vstep=uOne) {
        assert(koff+N*kstep<=KeySize.size());
        assert(voff+N*vstep<=ValueSize.size());
        allocate(N);
        for(unsigned int i=0,j=koff,k=voff;i<N;++i,j+=kstep,k+=vstep) {
          this->KeyList[i].SetIndexSize(KeySize[j]);
          this->ValueList[i].allocate(ValueSize[k]);
        }
        this->clearHashTree();
      }

      void allocate(const VectorBase<unsigned int>& KeySize,
                    const VectorBase<unsigned int>& ValueSize) {
        unsigned int n;
        n=(KeySize.size()<ValueSize.size()?KeySize.size():ValueSize.size());
        allocate(KeySize,ValueSize,n);
      }

  };

}

#endif
