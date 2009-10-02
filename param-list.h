
#ifndef _Parameter_List_H_
#define _Parameter_List_H_

#include "var-vector.h"
#include "fix-vector.h"
#include "btree.h"
#include "hash_func.h"

namespace std {

  class ParamKey {

    public:

      varVector<uint> Index;

      fixVector<uint,3> hash;

      void BuildHash() {
        uint size=Index.size()*4;
        hash[0]=hash_ap(reinterpret_cast<char*>(Index.data()),size);
        hash[1]=hash_dek(reinterpret_cast<char*>(Index.data()),size);
        hash[2]=hash_bp(reinterpret_cast<char*>(Index.data()),size);
      }

  };

  int compare(const ParamKey& K1, const ParamKey& K2) {
    if(K1.hash[0]>K2.hash[0])           return 1;
    else if(K1.hash[0]<K2.hash[0])      return -1;
    else {
      if(K1.hash[1]>K2.hash[1])         return 1;
      else if(K1.hash[1]<K2.hash[1])    return -1;
      else {
        if(K1.hash[2]>K2.hash[2])       return 1;
        else if(K1.hash[2]<K2.hash[2])  return -1;
        else                            return 0;
      }
    }
  }

  class ParamList {

    public:
    
      typedef ParamKey                            ParamKeyType;

      typedef varVector<double>                   ParamValueType;

      typedef btree<ParamKeyType,ParamValueType>  NodeType;

      varVector<ParamKeyType>   KeyList;

      varVector<ParamValueType> ValueList;

      fixVector<NodeType,0xFFFF> HashTree;

      ParamList() : KeyList(), ValueList(), HashTree() {}

      void UpdateHashTree() {
        assert(KeyList.size()==ValueList.size());
        uint n=KeyList.size();
        for(uint i=0;i<n;++i)
          HashTree[(KeyList[i].hash[0]&0xFFFF0000)>>16].insert(
              KeyList[i],ValueList[i]);
      }

      template <typename vType>
      ParamValueType* get(const vType& Index) {
        ParamKey tKey;
        tKey.Index.Duplicate(Index);
        tKey.BuildHash();
        return HashTree[(tKey.hash[0]&0xFFFF0000)>>16].get(tKey);
      }

  };
}

#endif

