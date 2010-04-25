
#ifndef _Chain_Node_H_
#define _Chain_Node_H_

#include "error-proc.h"
#include "storage-state-name.h"
#include "memory.h"
#include "util.h"

namespace std {

  template <typename T>
  struct ChainNode {

    typedef ChainNode<T>  Type;

    Type* parent;
    Type* child;
    T *content;
    unsigned int parentstate;
    unsigned int childstate;
    unsigned int contentstate;

    ChainNode() 
      : parent(), child(), content(), 
        parentstate(Unused), childstate(Unused), contentstate(Unused) {}
    ChainNode(const Type&) { myError("Cannot create from Chain Node"); }
    Type& operator=(const Type& CN) { assign(*this,CN); return *this; }
    ~ChainNode() { release(*this); }

    T& operator()() { return *content; }
    const T& operator()() const { return *content; }

  };

  template <typename T>
  bool IsAvailable(const ChainNode<T>& CN) { return IsAvailable(CN.content); }

  template <typename T>
  void release(ChainNode<T>& N) {
    if(IsAvailable(N.parent)) {
      N.parent->child=N.child;
      N.parent->childstate=N.childstate;
    }
    if(IsAvailable(N.child)) {
      N.child->parent=N.parent;
      N.child->parentstate=N.parentstate;
    }
    N.parent=NULL;   N.parentstate=Unused;
    N.child=NULL;    N.childstate=Unused;
    if(N.contentstate==Allocated) safe_delete(N.content); else N.content=NULL;
    N.contentstate=Unused;
  }

  template <typename T>
  void assign(ChainNode<T>& dest, const ChainNode<T>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    *(dest.content)=*(src.content);
  }

  template <typename T>
  void refer(ChainNode<T>& dest, const ChainNode<T>& src) {
    dest.parent=const_cast<ChainNode<T>*>(src.parent);
    dest.child=const_cast<ChainNode<T>*>(src.child);
    dest.content=const_cast<T*>(src.content);
    dest.parentstate=Reference;
    dest.childstate=Reference;
    dest.contentstate=Reference;
  }

  template <typename T>
  void allocate(ChainNode<T>& CN) {
    CN.content=new T;
    CN.contentstate=Allocated;
  }

  template <typename T>
  void add_parent(ChainNode<T>& dest, ChainNode<T>& parent) {
    if(parent.childstate==Allocated)  safe_delete(parent.child);
    parent.child=&dest;
    parent.childstate=dest.parent->childstate;
    if(parent.parentstate==Allocated) safe_delete(parent.parent);
    parent.parent=dest.parent;
    parent.parentstate=dest.parentstate;
    dest.parent->child=&parent;
    dest.parent->childstate=Reference;
    dest.parent=&parent;
    dest.parentstate=Reference;
  }

  template <typename T>
  void add_parent(ChainNode<T>& dest,
                  const T& content, const unsigned int cflag=Reference) {
    dest.parent->child=new ChainNode<T>;
    dest.parent->child->child=&dest;
    dest.parent->child->childstate=dest.parent->childstate;
    dest.parent->child->parent=dest.parent;
    dest.parent->child->parentstate=dest.parentstate;
    if(cflag==Allocated) {
      dest.parent->child->content=new T;
      *(dest.parent->child->content)=content;
    } else if(cflag==Reference)
      dest.parent->child->content=const_cast<T*>(&content);
    else myError("Improper Storage flag");
    dest.parent->childstate=Allocated;
    dest.parent=dest.parent->child;
    dest.parentstate=Reference;
  }

}

#endif

