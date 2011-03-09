
/**
 * @file chain.h
 * @brief data structure of chain
 *
 * This file describes the data structure of chain-like arrangement of data
 * and some related operations. This kind of data structure is useful for
 * the sequential data with insertion or deletion operations.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */ 

#ifndef _Chain_H_
#define _Chain_H_

#include "data/basic/chain-node.h"

namespace std {

  /**
   * @brief data structure of chain-like data arrangement
   *
   * This data structure contains the head and root of a chain (two termini
   * of a chain). Two pointers for head and root are given. Correspondingly,
   * the flags for these nodes are also used to indicate the storage types
   * of the concerned head and root nodes.
   *
   * T is the type of data in the node of chain. 
   */
  template <typename T>
  struct Chain {

    /**
     * @brief pointer to the root node of the chain
     */
    ChainNode<T> *root;
    /**
     * @brief pointer to the head node of the chain
     */
    ChainNode<T> *head;
    /**
     * @brief flag indicating the storage state of root node in the chain
     */
    unsigned int rootstate;
    /**
     * @brief flag indicating the storage state of head node in the chain
     */
    unsigned int headstate;

    /**
     * @brief abbreviation for the data structure of chain
     */
    typedef Chain<T>    Type;

    /**
     * @brief default initiator
     *
     * All the pointers are nullified and the flags are all set as Unused.
     */
    Chain() : root(NULL), head(NULL), rootstate(Unused), headstate(Unused) {}
    /**
     * @brief initiator from another Chain object
     *
     * It is prohibited and pop up an error message.
     *
     * @param C [in] the input Chain object
     */
    Chain(const Type& C) { Error("Cannot create from Chain"); }
    /**
     * @brief copy from another Chain object
     *
     * It is implemented with assign operation.
     *
     * @param C [in] the input Chain object.
     * @return the reference to the resultant Chain object
     */
    Type& operator=(const Type& C) { copy(*this,C); return *this; }
    /**
     * @brief destructor
     *
     * It is implemented with release operation.
     */
    ~Chain() { release(*this); }

  };

  /**
   * @brief check the availability of Chain object
   *
   * It is implemented by checking the pointer of root node in Chain object.
   *
   * T is the type of data in the node of Chain Object
   *
   * @param C [in] the Chain object to be checked.
   * @return the availability of the input Chain object
   */
  template <typename T>
  bool IsAvailable(const Chain<T>& C) { return IsAvailable(C.root); }

  /**
   * @brief allocate a Chain object
   *
   * During the allocation, the root node and head node are created and are
   * linked together. The flags are also updated. This establishes a minimal
   * chain with only two elements. This Chain object should be cleaned before
   * this operation to avoid memory leak.
   *
   * T is the type of data in the node of Chain object.
   *
   * @param C [in,out] the Chain object to be initialized.
   * @return nothing
   */ 
  template <typename T>
  void allocate(Chain<T>& C) {
    release(C);
    C.root=new ChainNode<T>;  C.rootstate=Allocated;
    C.head=new ChainNode<T>;  C.headstate=Allocated;
    C.root->child=C.head;   C.root->childstate=Reference;
    C.head->parent=C.root;  C.head->parentstate=Reference;
  }

  /**
   * @brief check if a node is in the Chain object
   *
   * The root node related to the input node id generated and compared.
   * If this root node is the same as that of the input Chain object,
   * it is declared that the input node is a part of the input Chain.
   * Otherwise, the input node is not in the Chain object.
   *
   * T is the type of data in the nodes of chain.
   *
   * @param C [in] teh Chain object
   * @param CN [in] the node to be checked.
   * @return the flag indicating if the node is inside the tree, true for
   *         inside, false for others.
   */ 
  template <typename T>
  bool In(const Chain<T>& C, const ChainNode<T>& CN) {
    ChainNode<T> *pNode=const_cast<ChainNode<T>*>(CN.parent);
    while(pNode->parent!=NULL)  pNode=pNode->parent;
    return pNode==C.root;
  }

  /**
   * @brief remove a node from a Chain object
   *
   * Before the remove operation, it is checked that the node is inside
   * the concerned Chain object. Then, based on the information if this
   * node is allocated by parent node or child node, the node is cleaned
   * or the storage of the node is totally removed. These checks are helpful
   * to avoid memory leak.
   *
   * T is the type of data in the node of Chain object.
   *
   * @param C [in,out] the concerned Chain object
   * @param CN [in] the pointer to the node to be removed
   * @return nothing
   * @note Here, the pointer of node is set as const. It is copied in
   *       procedure for free or delete operation. This is useful for the
   *       case that the node is not allocated by parent or child node.
   */
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

  /**
   * @brief release Chain object
   *
   * It is implemented by iteratively removing child node of root until
   * only root and head nodes are left. Then, the storages of these nodes
   * are freed based on their properties.
   *
   * T is the type of data in the node of Chain object.
   *
   * @param C [in] the Chain object to be released.
   * @return nothing 
   */
  template <typename T>
  void release(Chain<T>& C) {
    if(IsAvailable(C)) {
      while(C.root->child!=C.head) remove(C,C.root->child);
      if(C.rootstate==Allocated)  safe_delete(C.root);  else C.root=NULL;
      if(C.headstate==Allocated)  safe_delete(C.head);  else C.head=NULL;
    }
  }

  /**
   * @brief append a new node with certain content at the end of chain
   *
   * It is implemented with the certain add_parent operation. The operation
   * is done to add node as the parent of head node.
   *
   * T is the type of data in the node of Chain object
   *
   * @param C [in,out] the Chain object to be appended.
   * @param content [in] the content for the newly inserted node
   * @param cFlag [in] the flag indicating how to operate the content.
                       It takes the value Reference as default.
   * @return nothing
   */
  template <typename T>
  void append(Chain<T>& C,
              const T& content, const unsigned int cFlag=Reference) {
    add_parent(*(C.head),content,cFlag);
  }

  /**
   * @brief append a node at the end of Chain object
   *
   * It is implemented with the certain add_parent operation. This operation
   * is done to add node as the parent of head node.
   *
   * T is the type of data in the node of Chain object
   *
   * @param C [in,out] the Chain object to be appended
   * @param CN [in] the node to be added.
   * @return nothing
   */
  template <typename T>
  void append(Chain<T>& C, ChainNode<T>& CN) { add_parent(*(C.head),CN); }

  /**
   * @brief assign Chain object from another
   *
   * It is implemented by iteratively insert nodes in source Chain object.
   * The destination Chain object should be released before this operation
   * to avoid the memory leak.
   *
   * T is the type of data in the node of Chain object.
   *
   * @param dest [out] the Chain object to accept the data.
   * @param src [in] the Chain object containing the data.
   * @return nothing
   */
  template <typename T>
  void copy(Chain<T>& dest, const Chain<T>& src) {
    assert(IsAvailable(src));
    release(dest);
    allocate(dest);
    ChainNode<T>* pNode=const_cast<ChainNode<T>*>(src.root->child);
    while(pNode!=src.head) {
      append(dest,*(pNode->content));
      pNode=pNode->child;
    }
  }

  /**
   * @brief refer to another Chain object
   *
   * Just copy all the pointers and flags from source Chain object to
   * the destination Chain object. The destination Chain object should
   * be released before this operation to avoid the memory leak.
   *
   * T is the type of data in the node of Chain object.
   *
   * @param dest [out] the Chain object to accept data
   * @param src [in] the Chain object storing data
   * @return nothing 
   */
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

