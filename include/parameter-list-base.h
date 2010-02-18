
#ifndef _Parameter_List_Base_H_
#define _Parameter_List_Base_H_

#include "var-parameter-key.h"
#include "var-parameter-value.h"
#include "ref-vector.h"
#include "btree.h"

namespace std {

  template <template <typename> class VecType>
  class ParameterListBase {

    public:

      typedef ParameterListBase<VecType>    Type;
 
      typedef BTree<varParameterKey,varParameterValue>  NodeType;

    protected:

      VecType<varParameterKey>    KeyList;

      VecType<varParameterValue>  ValueList;

      refVector<NodeType>         HashTree;

    public:

      ParameterListBase() : KeyList(), ValueList(), HashTree() {}

      ParameterListBase(const Type& PL) {
        myError("Cannot create from parameter list base");
      }

     ~ParameterListBase() { clear(); }

      Type& operator=(const Type& PL) {
        KeyList=PL.KeyList;
        ValueList=PL.ValueList;
        updateHashTree();
        return *this;
      }

      void clear() {
        KeyList.clear();
        ValueList.clear();
        clearHashTree();
      }

      VecType<varParameterKey>& keylist() { return KeyList; }

      const VecType<varParameterKey>& keylist() const { return KeyList; }

      VecType<varParameterValue>& valuelist() { return ValueList; }

      const VecType<varParameterValue>& valuelist() const { return ValueList; }

      refVector<NodeType>& hashtree() { return HashTree; }
      
      const refVector<NodeType>& hashtree() const { return HashTree; }

    protected:

      void clearHashTree() {
        unsigned int n=HashTree.size();
        for(unsigned int i=0;i<n;++i) HashTree[i].clear();
      }

    public:

      void updateHashTree() {
        assert(KeyList.size()==ValueList.size());
        clearHashTree();
        unsigned int n=KeyList.size();
        for(unsigned int i=0;i<n;++i)
          HashTree[(KeyList[i].hash()[0]&0xFFFF0000)>>16].insert(
              KeyList[i],ValueList[i]);
      }

      const varParameterValue* get(const VectorBase<unsigned int>& idx) const {
        varParameterKey tKey;
        tKey.SetIndexSize(idx.size());
        tKey.index()=idx;
        tKey.BuildHash();
        return HashTree[(tKey.hash()[0]&0xFFFF0000)>>16].get(tKey);
      }

  };

  template <template <typename> class VecType>
  istream& operator>>(istream& is, ParameterListBase<VecType>& PL) {
    unsigned int n=PL.keylist().size();
    for(unsigned int i=0;i<n;++i) {
      is>>PL.keylist()[i]>>PL.valuelist()[i];
      PL.keylist()[i].BuildHash();
    }
    PL.updateHashTree();
    return is;
  }

}

#endif

