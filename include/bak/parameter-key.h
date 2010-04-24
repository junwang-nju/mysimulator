
#ifndef _Parameter_Key_H_
#define _Parameter_Key_H_

#include "fix-vector.h"
#include "var-vector.h"
#include "ref-vector.h"
#include "hash-func.h"
#include <cassert>

namespace std {

  template <template <typename> class IndexVecType>
  class ParameterKey {

    public:

      typedef ParameterKey<IndexVecType>  Type;

      typedef IndexVecType<unsigned int>  IndexType;

      typedef fixVector<unsigned int,3>   HashType;

    protected:

      IndexType Index;

      HashType Hash;

    public:

      ParameterKey() : Index(), Hash() {
        assert(IndexVecType<unsigned int>::IsVector);
      }

      ParameterKey(const unsigned int NI) : Index(), Hash() {
        assert(IndexVecType<unsigned int>::IsVector);
        allocate(NI);
      }

      ParameterKey(const Type& P) {
        myError("Cannot create from parameter key");
      }

      ~ParameterKey() { clear(); }

      Type& operator=(const Type& P) {
        Index=P.Index;
        BuildHash();
        return *this;
      }

      template <template <typename> class iIndexVecType>
      Type& operator=(const ParameterKey<iIndexVecType>& PK) {
        Index=PK.Index;
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

      void allocate(const unsigned int nIdx) { myError("Not Available"); }

      template <template <typename> class iIndexVecType>
      void refer(const ParameterKey<iIndexVecType>& PK) {
        myError("Not Available");
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

  };

  template <>
  void ParameterKey<varVector>::allocate(const unsigned int nIdx) {
    index().allocate(nIdx);
  }

  template <>
  template <template <typename> class iIndexVecType>
  void ParameterKey<refVector>::refer(const ParameterKey<iIndexVecType>& PK) {
    index().refer(PK.index());
    hash()=PK.hash();
  }

  template <template <typename> class IdVec>
  istream& operator>>(istream& is, ParameterKey<IdVec>& P) {
    is>>P.index();
    P.BuildHash();
    return is;
  }

  template <template <typename> class IdVecA, template <typename> class IdVecB>
  int compare(const ParameterKey<IdVecA>& PA,
              const ParameterKey<IdVecB>& PB) {
    for(unsigned int i=0;i<PA.hash().size();++i)
      if(PA.hash()[i]!=PB.hash()[i])  return (PA.hash()[i]>PB.hash()[i]?1:-1);
    return 0;
  }

}

#endif
