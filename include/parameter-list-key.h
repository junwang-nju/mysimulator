
#ifndef _Parameter_List_Key_H_
#define _Parameter_List_Key_H_

#include "var-vector.h"
#include "fix-vector.h"

namespace std {
  class ParameterKey {
    public:
      typedef ParameterKey  Type;
    protected:
      varVector<unsigned int> Index;
      fixVector<unsigned int,3> Hash;
    public:
      ParameterKey() : Index(), Hash() {}
      ParameterKey(const Type& PK) {
        myError("Cannot create from parameter key");
      }
      ~ParameterKey() { clear(); }
      Type& operator=(const Type& PK) {
        Index=PK.Index;
        BuildHash();
        return *this;
      }
      void clear();
      void BuildHash();
      const varVector<unsigned int>& index() const;
      const fixVector<unsigned int,3>& hash() const;
      void SetIndex(const varVector<unsigned int>& VI);
  };
}

#endif

