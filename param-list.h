
#ifndef _Parameter_List_H_
#define _Parameter_List_H_

#include "var-vector.h"
#include "fix-vector.h"
#include "vector-op.h"
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

  istream& operator>>(istream& is, ParamKey& K) {
    is>>K.Index;
    K.BuildHash();
    return is;
  }

  int compare(const ParamKey& K1, const ParamKey& K2) {
    if(K1.hash[0]==K2.hash[0])
      if(K1.hash[1]==K2.hash[1])
        if(K1.hash[2]==K2.hash[2])      return 0;
        else                            return (K1.hash[2]>K2.hash[2]?1:-1);
      else                              return (K1.hash[1]>K2.hash[1]?1:-1);
    else                                return (K1.hash[0]>K2.hash[0]?1:-1);
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
      const ParamValueType* get(const vType& Index) const {
        ParamKey tKey;
        tKey.Index.Duplicate(Index);
        tKey.BuildHash();
        return HashTree[(tKey.hash[0]&0xFFFF0000)>>16].get(tKey);
      }

  };

  istream& operator>>(istream& is, ParamList& PL) {
    uint n;
    is>>n;
    PL.KeyList.allocate(n);
    PL.ValueList.allocate(n);
    for(uint i=0;i<n;++i)   is>>PL.KeyList[i]>>PL.ValueList[i];
    PL.UpdateHashTree();
    return is;
  }

}

#endif

