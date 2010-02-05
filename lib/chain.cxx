
#include "chain.h"
#include "memory.h"

namespace std {

  template <typename T>
  void Chain<T>::clear() {
    NodeType* pNode;
    while((pNode=Root.child())!=&Head) remove(pNode);
  }

  template <typename T>
  void Chain<T>::append(const T& content) {
    NodeType* pNode=new ChainNode<T>;
    pNode->SetChainAllocFlag(true);
    Head.add_before(*pNode);
    pNode->content()=content;
  }

  template <typename T>
  void Chain<T>::append(ChainNode<T>& node) {
    Head.add_before(node);
  }

  template <typename T>
  void Chain<T>::remove(ChainNode<T>*& pnode) {
    pnode->remove_self();
    if(pnode->IsAllocByChain())   safe_delete(pnode); 
  }

}

