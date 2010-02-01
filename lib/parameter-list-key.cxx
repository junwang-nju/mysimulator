
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

}

