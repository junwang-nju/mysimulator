
#ifndef _Reference_Object_H_
#define _Reference_Object_H_

#include "object-with-storage.h"
#include "memory.h"

namespace std {
  template <typename RObjType, typename SObjType>
  class refObject : public RObjType {
    protected:
      ChainNode<void*>  rNode;
    public:
      typedef refObject<RObjType,SObjType>  Type;
      typedef RObjType ParentType;
      refObject() : ParentType(), rNode() {}
      refObject(const Type& O) {
        myError("Cannot create from reference object");
      }
      ~refObject() { rNode.clear(); }
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
      ChainNode<void*>  RefInfo();
      const ChainNode<void*> RefInfo() const;
      void clear();
      virtual void refer(ObjectWStorage<SObjType>& O) = 0;
      virtual void refer(Type& O) = 0;
  };
}

#endif

