
#ifndef _Reference_Object_H_
#define _Reference_Object_H_

#include "object-with-storage.h"

namespace std {
  template <typename ObjType>
  class refObject : public ObjType {
    protected:
      Pool<void*>*  pRefList;
      int           thisID;
    public:
      typedef refObject<ObjType>  Type;
      typedef ObjType ParentType;
      refObject() : ParentType(), pRefList(NULL), thisID(-1) {}
      refObject(const Type& O) {
        myError("Cannot create from reference object");
      }
      ~refObject() { pRefList=NULL; thisID=-1; }
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
      Pool<void*>* PtrRefList();
      const Pool<void*>* PtrRefList() const;
      const int& PresentID() const;
      void SetID(const int id);
      void clear();
      void swap(Type& O);
      virtual void refer(const ObjectWStorage<ObjType>& O) = 0;
      virtual void refer(const Type& O) = 0;
  };
}

#endif

