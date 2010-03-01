
#ifndef _Fixed_Parameter_List_H_
#define _Fixed_Parameter_List_H_

#include "parameter-list-base.h"
#include "ref-vector.h"

namespace std {

  template <unsigned int NItem>
  class fixParameterList : public ParameterListBase<refVector> {

    public:

      typedef fixParameterList<NItem>   Type;

      typedef ParameterListBase<refVector>  ParentType;

    protected:

      fixVector<varParameterKey,NItem>  inKeyList;

      fixVector<varParameterValue,NItem>  inValueList;

      fixVector<ParentType::TreeType,0xFFFFU> inHashTree;

      void initStatic() {
        KeyList.refer(inKeyList);
        ValueList.refer(inValueList);
        this->ptrhashtree()=&inHashTree;
      }

    public:

      fixParameterList()
        : ParentType(), inKeyList(), inValueList(), inHashTree() {
        initStatic();
      }

      fixParameterList(const Type&) {
        myError("Cannot create from fixed Parameter List");
      }

      ~fixParameterList() {}

      Type& operator=(const Type& fPL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fPL));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const ParameterListBase<VecType>& PL) {
        static_cast<ParentType*>(this)->operator=(PL);
        return *this;
      }

      void clear() {
        for(unsigned int i=0;i<NItem;++i) {
          this->keylist()[i].clear();
          this->valuelist()[i].clear();
        }
        this->clearHashTree();
      }

    protected:

      template <typename T>
      void initList(VectorBase<T>& List, const unsigned int Size) {
        for(unsigned int i=0;i<NItem;++i) List[i].allocate(Size);
      }

      template <typename T>
      void initList(VectorBase<T>& List,
                    const VectorBase<unsigned int>& Size,
                    const unsigned int off=uZero,
                    const unsigned int step=uOne) {
        assert(off+NItem*step<=Size.size());
        for(unsigned int i=0,n=off;i<NItem;++i,n+=step)
          List[i].allocate(Size[n]);
      }

    public:

      void initAs(const unsigned int kSize, const unsigned int vSize) {
        initList(this->keylist(),kSize);
        initList(this->valuelist(),vSize);
      }

      void initAs(const unsigned int kSize,
                  const VectorBase<unsigned int>& vSize,
                  const unsigned int voff=uZero,
                  const unsigned int vstep=uOne) {
        initList(this->keylist(),kSize);
        initList(this->valuelist(),vSize,voff,vstep,this->valuelist());
      }

      void initAs(const VectorBase<unsigned int>& kSize,
                  const unsigned int vSize, const unsigned int koff=uZero,
                  const unsigned int kstep=uOne) {
        initList(this->keylist(),kSize,koff,kstep);
        initList(this->valuelist(),vSize,this->valuelist());
      }

      void initAs(const VectorBase<unsigned int>& kSize,
                  const VectorBase<unsigned int>& vSize,
                  const unsigned int koff=uZero, const unsigned int kstep=uOne,
                  const unsigned int voff=uZero, const unsigned int vstep=uOne){
        initList(this->keylist(),kSize,koff,kstep);
        initList(this->valuelist(),vSize,voff,vstep);
      }

  };

}

#endif

