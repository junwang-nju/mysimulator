
#ifndef _Chain_Interface_H_
#define _Chain_Interface_H_

#include "chain/node/interface.h"
#include "referable-object/refer.h"
#include "referable-object/compare.h"
#include "referable-object/swap.h"
#include "generic/exchange.h"
#include "intrinsic-type/allocate.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T>
  struct Chain {

    typedef Chain<T>    Type;

    ChainNode<T> root,head;

    Chain() : root(), head() {}
    Chain(const Type&) { Error("Copier of Chain Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Chain Disabled!");
      return *this;
    }
    ~Chain() { clearData(); }

    void clearData() {
      if(!IsValid(*this)) return;
      while(IsValid(root.child)&&IsValid(root.child().child))
        _remove(root.child.pdata);
      release(root);
      release(head);
    };
    bool IsContained(const ChainNode<T>& N) {
      Object<ChainNode<T> > runNode;
      refer(runNode,N);
      while(IsValid(runNode().parent))  refer(runNode,runNode().parent);
      return IsSameObject(runNode,root);
    }
    bool IsContained(const T& C) {
      Object<ChainNode<T> > runNode;
      refer(runNode,root);
      while(IsValid(runNode().child)) {
        refer(runNode,runNode().child);
        if(compare(runNode().content,C)==0)   return true;
      }
      return false;
    }
    void _remove(const ChainNode<T>* N) {
      assert(IsContained(*N));
      ChainNode<T> *nfree;
      nfree=const_cast<ChainNode<T>*>(N);
      swap(nfree->parent().child,nfree->child);
      swap(nfree->parent().child().parent,nfree->parent);
      if((nfree->parent.flag==Allocated)||(nfree->child.flag==Allocated)) {
        nfree->parent.flag=Referred;
        nfree->child.flag=Referred;
        delete nfree;
      } else release(*nfree);
    }
    void remove(const T& C) {
      Object<ChainNode<T> > runNode;
      refer(runNode,root);
      while(IsValid(runNode().child)) {
        refer(runNode,runNode().child);
        if(compare(runNode().content,C)==0) {
          _remove(&(runNode()));
          break;
        }
      }
    }
    void append(ChainNode<T>& N) {
      release(N.child);
      swap(N.child,head.parent().child);
      release(N.parent);
      swap(N.parent,head.parent);
      refer(head.parent().child,N);
      refer(head.parent,N);
    }
    void append(const T& C, const ObjectStateName& cFlag=Referred) {
      assert(IsValid(C));
      allocate(head.parent().child);
      if(cFlag==Allocated) {
        allocate(head.parent().child.pdata->content);
        imprint(head.parent().child().content(),C);
        copy(head.parent().child().content(),C);
      } else if(cFlag==Referred)
        refer(head.parent().child.pdata->content,C);
      else Error("Unknown Referable-Object State Name in Append for Chain");
      Object<ChainNode<T> > runNode;
      refer(runNode,head.parent().child);
      refer(head.parent().child().child,head);
      swap(head.parent().child().parent,head.parent);
      refer(head.parent,runNode);
    }

  };

  template <typename T>
  bool IsValid(const Chain<T>& C) { return IsValid(C.root)&&IsValid(C.head); }

  template <typename T>
  void release(Chain<T>& C) { C.clearData(); }

  template <typename T>
  void allocate(Chain<T>& C) {
    release(C);
    allocate(C.root);
    allocate(C.head);
    refer(C.root.child,C.head);
    refer(C.head.parent,C.root);
  }

}

#endif

