
#ifndef _Chain_Interface_H_
#define _Chain_Interface_H_

#include "chain/node/interface.h"
#include "intrinsic-type/release.h"
#include "intrinsic-type/valid.h"
#include "intrinsic-type/compare.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename T>
  struct Chain {

    public:

      typedef Chain<T>      Type;
      typedef ChainNode<T>  NodeType;

      NodeType  root;
      NodeType* head;

      Chain() : root(), head(NULL) {}
      ~Chain() { clearData(); }

      void clearData() {
        if(!isvalid())  return;
        while(root.child!=head) _remove(root.child);
        delete_pointer(root.child);
        release(root);
        head=NULL;
      }
      bool isvalid() const { return IsValid(head); }

      void _remove(ChainNode<T>* pnode) {
        ChainNode<T>* mparent=pnode->parent;
        ChainNode<T>* mchild=pnode->child;
        delete_pointer(mparent->child);
        mparent->child=mchild;
        mchild->parent=mparent;
      }
      void remove(const T& d) {
        assert(isvalid());
        ChainNode<T>* now=&root;
        while(now!=head) {
          now=now->child;
          if(compare(now->content,d)==0) { _remove(now); break; }
        }
      }
      void append(const T& d) {
        assert(isvalid());
        ChainNode<T>* middle=new ChainNode<T>;
        allocate(middle->content);
        middle->content()=d;
        ChainNode<T>* mparent=head->parent;
        ChainNode<T>* mchild=head;
        middle->parent=mparent;
        middle->child=mchild;
        mparent->child=middle;
        mchild->parent=middle;
      }

    private:

      Chain(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const Chain<T>& C) { return C.isvalid(); }

  template <typename T>
  void release(Chain<T>& C) { C.clearData(); }

}

#endif

