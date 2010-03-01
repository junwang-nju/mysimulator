
#ifndef _Parameter_Key_Base_H_
#define _Parameter_Key_Base_H_

#include "fix-vector.h"
#include "hash-func.h"
#include <cassert>

namespace std {

  template <template <typename> class IndexVecType>
  class ParameterKeyBase {

    public:

      typedef ParameterKeyBase<IndexVecType>  Type;

      typedef IndexVecType<unsigned int>  IndexType;

      typedef fixVector<unsigned int,3>   HashType;

    protected:

      IndexType Index;

      HashType Hash;

    public:

      ParameterKeyBase() : Index(), Hash() {
        assert(IndexVecType<unsigned int>::IsVector);
      }

      ParameterKeyBase(const Type& P) {
        myError("Cannot create from parameter key base");
      }

      ~ParameterKeyBase() { clear(); }

      Type& operator=(const Type& P) {
        Index=P.Index;
        BuildHash();
        return *this;
      }

      const IndexType& index() const { return Index; }

      const HashType& hash() const { return Hash; }

      IndexType& index() { return Index; }

      HashType& hash() { return Hash; }

      void BuildHash() {
        unsigned int hsize=Index.size()*4;
        Hash[0]=hash_ap(reinterpret_cast<char*>(Index.data()),hsize);
        Hash[1]=hash_dek(reinterpret_cast<char*>(Index.data()),hsize);
        Hash[2]=hash_bp(reinterpret_cast<char*>(Index.data()),hsize);
      }

      void clear() { Index.clear(); }

  };

  template <template <typename> class IdVec>
  istream& operator>>(istream& is, ParameterKeyBase<IdVec>& P) {
    is>>P.index();
    P.BuildHash();
    return is;
  }

  template <template <typename> class IdVecA, template <typename> class IdVecB>
  int compare(const ParameterKeyBase<IdVecA>& PA,
              const ParameterKeyBase<IdVecB>& PB) {
    for(unsigned int i=0;i<PA.hash().size();++i)
      if(PA.hash()[i]!=PB.hash()[i])  return (PA.hash()[i]>PB.hash()[i]?1:-1);
    return 0;
  }

}

#endif
