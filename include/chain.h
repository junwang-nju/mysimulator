
#ifndef _Chain_H_
#define _Chain_H_

#include "chain-node.h"
#include <cassert>

namespace std {

  template <typename T>
  struct Chain {

    ChainNode<T> *root;
    ChainNode<T> *head;
    unsigned int rootstate;
    unsigned int headstate;

    typedef Chain<T>    Type;

    Chain() : root(NULL), head(NULL), rootstate(Unused), headstate(Unused) {}
    Chain(const Type&) { myError("Cannot create from Chain"); }
    Type& operator=(const Type& C) { assign(*this,C); return *this; }
    ~Chain() { release(*this); }

  };

  template <typename T>
  bool IsAvailable(const Chain<T>& C) { return IsAvailable(C.root); }

  template <typename T>
  void allocate(Chain<T>& C) {
    C.root=new ChainNode<T>;  C.rootstate=Allocated;
    C.head=new ChainNode<T>;  C.headstate=Allocated;
    C.root->child=C.head;   C.root->childstate=Reference;
    C.head->parent=C.root;  C.head->parentstate=Reference;
  }

  template <typename T>
  bool In(const Chain<T>& C, const ChainNode<T>& CN) {
    ChainNode<T> *pNode=const_cast<ChainNode<T>*>(CN.parent);
    while(pNode->parent!=NULL)  pNode=pNode->parent;
    return pNode==C.root;
  }

  template <typename T>
  void remove(Chain<T>& C, const ChainNode<T>* CN) {
    assert(In(C,*CN));
    bool cflag;
    ChainNode<T> *tofree=const_cast<ChainNode<T>*>(CN);
    if((tofree->parent->childstate==Allocated)||
       (tofree->child->parentstate==Allocated))  cflag=true;
    else cflag=false;
    if(cflag) safe_delete(tofree);
    else      release(*tofree);  
  }

  template <typename T>
  void release(Chain<T>& C) {
    if(IsAvailable(C)) {
      while(C.root->child!=C.head) remove(C,C.root->child);
      if(C.rootstate==Allocated)  safe_delete(C.root);  else C.root=NULL;
      if(C.headstate==Allocated)  safe_delete(C.head);  else C.head=NULL;
    }
  }

  template <typename T>
  void append(Chain<T>& C,
              const T& content, const unsigned int cFlag=Reference) {
    add_parent(*(C.head),content,cFlag);
  }

  template <typename T>
  void append(Chain<T>&C, ChainNode<T>& CN) { add_parent(*(C.head),CN); }

  template <typename T>
  void assign(Chain<T>& dest, const Chain<T>& src) {
    assert(IsAvailable(src));
    release(dest);
    allocate(dest);
    ChainNode<T>* pNode=const_cast<ChainNode<T>*>(src.root->child);
    while(pNode!=src.head) {
      append(dest,*(pNode->content));
      pNode=pNode->child;
    }
  }

  template <typename T>
  void refer(Chain<T>& dest, const Chain<T>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.root=src.root;
    dest.head=src.head;
    dest.rootstate=Reference;
    dest.headstate=Reference;
  }

}

#endif

