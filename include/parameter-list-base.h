
#ifndef _Parameter_List_H_
#define _Parameter_List_H_

#include "parameter-list-key.h"
#include "btree.h"

namespace std {
  template <typename DataVecType>
  class ParameterList {
    public:
      typedef ParameterList   Type;
      typedef varVector<double> ParameterValue;
      typedef btree<ParameterKey,ParameterValue>  HNodeType;
    protected:
      DataVecType<ParameterKey> KeyList;
      DataVecType<ParameterValue> ValueList;
      refVector<HNodeType> HashTree;
  };
}

#endif

