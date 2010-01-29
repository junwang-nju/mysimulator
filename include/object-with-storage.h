
#ifndef _Object_With_Storage_H_
#define _Object_With_Storage_H_

#include "chain.h"

namespace std {
  template <typename ObjType>
  class ObjectWStorage : public ObjType {
    protected:
      Chain<void*> rObjSet;
    public:
      typedef ObjectWStorage<ObjType> Type;
      typedef ObjType ParentType;
      ObjectWStorage() : ParentType(), rObjSet() {}
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
      Chain<void*>& RefList();
      const Chain<void*>& RefList() const;
      void swap(Type& O);
  };
}

#endif

