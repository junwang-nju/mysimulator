
#include "chain.h"
#include "memory.h"

namespace std {

  template <typename T>
  void Chain<T>::clear() { while(Head!=&Root) remove(Head); }

  template <typename T>
  void Chain<T>::append(const T& content) {
    Head->child()=new ChainNode<T>;
    Head->child()->parent()=Head;
    Head=Head->child();
    Head->SetChainAllocFlag(true);
    Head->content()=content;
  }

  template <typename T>
  void Chain<T>::append(ChainNode<T>& node) {
    Head->child()=&node;
    node.parent()=Head;
    node.child()=NULL;
    Head=&node;
  }

  template <typename T>
  void Chain<T>::remove(ChainNode<T>*& pnode) {
    ChainNode<T>* ppnode=pnode->parent();
    ChainNode<T>* pcnode=pnode->child();
    if(pnode->IsAllocByChain())   safe_delete(pnode); 
    else                          pnode->clear();
    ppnode->child()=pcnode;
    if(pcnode!=NULL)  pcnode->parent()=ppnode;
    else              Head=ppnode;
  }

}

