
#ifndef _Reference_Object_H_
#define _Reference_Object_H_

#include "object-with-storage.h"

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

      ChainNode<void*>&  RefInfo() { return rNode; }

      const ChainNode<void*>& RefInfo() const { return rNode; }

      void clear() {
        static_cast<ParentType*>(this)->clear();
        rNode.remove_self();
      }

      virtual void refer(ObjectWStorage<SObjType>& O) = 0;

      virtual void refer(Type& O) = 0;

  };

}

#endif

