
#ifndef _Parameter_Key_Base_H_
#define _Parameter_Key_Base_H_

#include "ref-vector.h"

namespace std {
  template <template <typename> class IndexVecType>
  class ParameterKeyBase {
    public:
      typedef ParameterKeyBase<IndexVecType>  Type;
      typedef IndexVecType<unsigned int>  IndexType;
      typedef refVector<unsigned int>   HashType;
    protected:
      IndexType Index;
      HashType  Hash;
    public:
      ParameterKeyBase() : Index(), Hash() {
        assert(IndexVecType<unsigned int>::IsVector); }
      ParameterKeyBase(const Type& P) {
        myError("Cannot create from parameter key base");
      }
      ~ParameterKeyBase() { clear(); }
      Type& operator=(const Type& P) {
        Index=P.Index;
        BuildHash();
        return *this;
      }
      const IndexType& index() const;
      const HashType& hash() const;
      IndexType& index();
      HashType& hash();
      void BuildHash();
      void clear();
  };
  template <template <typename> class IdVec>
  istream& operator>>(istream& is, ParameterKeyBase<IdVec>& P);
  template <template <typename> class IdVecA, template <typename> class IdVecB>
  int compare(const ParameterKeyBase<IdVecA>& PA,
              const ParameterKeyBase<IdVecB>& PB);
}

#endif
