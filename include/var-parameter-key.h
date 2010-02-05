
#ifndef _Variable_Parameter_Key_H_
#define _Variable_Parameter_Key_H_

#include "parameter-key-base.h"
#include "object-with-storage.h"
#include "var-vector.h"
#include "fix-vector.h"

namespace std {
  class varParameterKey : public ObjectWStorage<ParameterKeyBase<varVector> > {
    public:
      typedef varParameterKey   Type;
      typedef ObjectWStorage<ParameterKeyBase<varVector> >  ParentType;
    protected:
      fixVector<unsigned int, 3> HashData;
    public:
      varParameterKey() : ParentType() { hash().refer(HashData); }
      varParameterKey(const Type& P) {
        myError("Cannot create with variable parameter key");
      }
      virtual ~varParameterKey() { clear(); }
  };
}

#endif