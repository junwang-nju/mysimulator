
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
        return *this;
      }
      void clear();
  };
}

#endif

