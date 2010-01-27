
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
      static const unsigned int MaxRefObj;
      ObjectWStorage() : ParentType(), rObjSet() {
        rObjSet.allocate(MaxRefObj);
      }
      ObjectWStorage(const Type& O) {
        myError("Cannot create from object with storage");
      }
      Type& operator=(const Type& O) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(O));
        return *this;
      }
      template <typename inputT>
      Type& operator=(const inputT& O) {
        static_cast<ParentType*>(this)->operator=(O);
        return *this;
      }
      ~ObjectWStorage() { rObjSet.clear(); }
      void clear();
      Pool<void*>& RefList();
      const Pool<void*>& RefList() const;
      void swap(Type& O);
  };
  template <typename ObjType>
  const unsigned int ObjectWStorage<ObjType>::MaxRefObj=20;
}

#endif

