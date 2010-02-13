
#ifndef _Variable_Vector_H_
#define _Variable_Vector_H_

#include "object-with-storage.h"
#include "vector-base.h"
#include "memory.h"
#include "ref-vector.h"

namespace std {

  template <typename T>
  class varVector : public ObjectWStorage<VectorBase<T> > {

    public:

      typedef T DataType;

      typedef varVector<T>  Type;

      typedef ObjectWStorage<VectorBase<T> >  ParentType;

      varVector() : ParentType() { }

      varVector(const unsigned int N) : ParentType() { allocate(N); }

      varVector(const Type& V) {
        myError("Cannot create from variable vector");
      }

      virtual ~varVector() { safe_delete_array(this->data()); }

      Type& operator=(const Type& V) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(V));
        return *this;
      }

      template <typename inputT>
      Type& operator=(const inputT& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }

      void clear() {
        safe_delete_array(this->data());
        typedef ChainNode<void*>  NodeType;
        NodeType *pNode;
        const NodeType *pRoot=&(this->RefList().root());
        const NodeType *pHead=&(this->RefList().head());
        while((pNode=const_cast<NodeType*>(pRoot->child()))!=pHead)
          reinterpret_cast<refVector<T>*>(pNode->content())->clear();
        static_cast<ParentType*>(this)->clear();
      }

      void allocate(const unsigned int N) {
        static_cast<ParentType*>(this)->RefList().clear();
        if(this->size()!=N) {
          safe_delete_array(this->data());
          this->data()=new T[N];
          this->SetSize(N);
          this->SetHeadTail();
        }
      }

      virtual const char* type() const { return "Variable Vector"; }

  };

}

#endif

