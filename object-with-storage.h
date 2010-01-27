
#ifndef _Object_With_Storage_H_
#define _Object_With_Storage_H_

#include "pool.h"

namespace std {
  template <typename ObjType>
  class ObjectWStorage : public ObjType {
    protected:
      Pool<void*> rObjSet;
    public:
      typedef ObjectWStorage<ObjType> Type;
      typedef ObjType ParentType;
  };
}

#endif

