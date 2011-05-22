
#ifndef _Chain_Interface_H_
#define _Chain_Interface_H_

#include "chain/node/interface.h"
#include "chain/node/extract.h"
#include "referable-object/refer.h"
#include "referable-object/compare.h"
#include "referable-object/swap.h"
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
    void _remove(ChainNode<T>*& pN) {
      assert(IsContained(*pN));
      Object<ChainNode<T> > runNode;
      runNode.pdata=pN;
      runNode.flag=extract(*pN);
      release(runNode);
    }
    void remove(const T& C) {
      Object<ChainNode<T> > runNode;
      refer(runNode,root);
      while(IsValid(runNode().child)) {
        refer(runNode,runNode().child);
        if(compare(runNode().content,C)==0) {
          _remove(runNode.pdata);
          break;
        }
      }
    }
    void append(ChainNode<T>& N) {
      Object<ChainNode<T> > runNode;
      runNode.pdata=&N;
      runNode.flag=extract(N);
      swap(N.child,head.parent().child);
      swap(N.parent,head.parent);
      swap(N.parent().child,runNode);
      refer(head.parent,N);
      release(runNode);
    }
    void append(const T& C, const ObjectStateName& cFlag=Allocated) {
      assert(IsValid(C));
      allocate(head.parent().child);
      if(cFlag==Allocated) {
        allocate(head.parent().child.pdata->content);
        imprint(head.parent().child().content(),C);
        copy(head.parent().child().content(),C);
      } else if(cFlag==Referred)
        refer(head.parent().child.pdata->content,C);
      else Error("Unknown Referable-Object State Name in Append for Chain");
      ChainNode<T> *pNode;
      pNode=head.parent().child.pdata;
      refer(head.parent().child().child,head);
      swap(head.parent().child().parent,head.parent);
      refer(head.parent,*pNode);
    }

  };

  template <typename T>
  bool IsValid(const Chain<T>& C) { return IsValid(C.root)&&IsValid(C.head); }

  template <typename T>
  void release(Chain<T>& C) { C.clearData(); }

}

#endif

