
#include "chain-node.h"

namespace std {

  template <typename T>
  void ChainNode<T>::clear() {
    Parent=NULL;
    Child=NULL;
  }

  template <typename T>
  ChainNode<T>* ChainNode<T>::parent() { return Parent; }

  template <typename T>
  const ChainNode<T>* ChainNode<T>::parent() const { return Parent; }

  template <typename T>
  ChainNode<T>* ChainNode<T>::child() { return Child; }

  template <typename T>
  const ChainNode<T>* ChainNode<T>::child() const { return Child; }

  template <typename T>
  T& ChainNode<T>::content() { return Content; }

  template <typename T>
  const T& ChainNode<T>::content() const { return Content; }

  template <typename T>
  const bool ChainNode<T>::IsAllocByChain() const { return AllocFg; }

  template <typename T>
  void ChainNode<T>::SetChainAllocFlag(bool efg) { AllocFg=efg; }

  template <typename T>
  void ChainNode<T>::add_before(Type& node) {
    Parent->Child=&node;
    node.Parent=Parent;
    node.Child=this;
    Parent=&node;
  }

  template <typename T>
  void ChainNode<T>::remove_self() {
    Parent->Child=Child;
    Child->Parent=Parent;
    clear();
  }

}

