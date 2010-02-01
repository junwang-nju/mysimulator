
#include "parameter-list-key.h"
#include "hash-func.h"

namespace std {

  void ParameterKey::clear() { Index.clear(); Hash=0U; }

  void ParameterKey::BuildHash() {
    unsigned int hsize=Index.size()*4;
    Hash[0]=hash_ap(reinterpret_cast<char*>(Index.data()),hsize);
    Hash[1]=hash_dek(reinterpret_cast<char*>(Index.data()),hsize);
    Hash[2]=hash_bp(reinterpret_cast<char*>(Index.data()),hsize);
  }

  const varVector<unsigned int>& ParameterKey::index() const { return Index; }

  const fixVector<unsigned int,3>& ParameterKey::hash() const { return Hash; }

  void ParameterKey::SetIndex(const varVector<unsigned int>& VI) { Index=VI; }

  istream& operator>>(istream& is, ParameterKey& PK) {
    is>>PK.Index;
    PK.BuildHash();
    return is;
  }

  int compare(const ParameterKey& K1, const ParameterKey& K2) {
    if(K1.hash()[0]==K2.hash()[0])
      if(K1.hash()[1]==K2.hash()[1])
        if(K1.hash()[2]==K2.hash()[2]) return 0;
        else                           return (K1.hash()[2]>K2.hash()[2]?1:-1);
      else                           return (K1.hash()[1]>K2.hash()[1]?1:-1);
    else                           return (K1.hash()[0]>K2.hash()[0]?1:-1);
  }

}

