
#include "parameter-key-base.h"
#include "hash-func.h"
#include <cassert>

namespace std {

  template <template <typename> class IdVec>
  const IdVec<unsigned int>& ParameterKeyBase<IdVec>::index() const {
    return Index;
  }

  template <template <typename> class IdVec>
  const refVector<unsigned int>& ParameterKeyBase<IdVec>::hash() const {
    return Hash;
  }

  template <template <typename> class IdVec>
  IdVec<unsigned int>& ParameterKeyBase<IdVec>::index() { return Index; }
  
  template <template <typename> class IdVec>
  refVector<unsigned int>& ParameterKeyBase<IdVec>::hash() { return Hash; }

  template <template <typename> class IdVec>
  void ParameterKeyBase<IdVec>::BuildHash() {
    assert(Hash.size()==3);
    unsigned int hsize=Index.size()*4;
    Hash[0]=hash_ap(reinterpret_cast<char*>(Index.data()),hsize);
    Hash[1]=hash_dek(reinterpret_cast<char*>(Index.data()),hsize);
    Hash[2]=hash_bp(reinterpret_cast<char*>(Index.data()),hsize);
  }

  template <template <typename> class IdVec>
  void ParameterKeyBase<IdVec>::clear() {
    Index.clear();
    Hash.clear();
  }

  template <template <typename> class IdVec>
  istream& operator>>(istream& is, ParameterKeyBase<IdVec>& P) {
    is>>P.index();
    P.BuildHash();
    return is;
  }

  template <template <typename> class IdVecA, template <typename> class IdVecB>
  int compare(const ParameterKeyBase<IdVecA>& PA,
              const ParameterKeyBase<IdVecB>& PB) {
    unsigned int n=PA.hash.size();
    assert(n==PB.hash().size());
    for(unsigned int i=0;i<PA.hash().size();++i)
      if(PA.hash()[i]!=PB.hash()[i])  return (PA.hash()[i]>PB.hash()[i]?1:-1);
    return 0;
  }

}
