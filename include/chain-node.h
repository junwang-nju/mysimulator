
/**
 * @file chain-node.h
 * @brief the data structure of node in chain
 *
 * This file contains the data structure of node in a chain structure and
 * the related operations for this structure. This is the basic part of
 * Chain data structure.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Chain_Node_H_
#define _Chain_Node_H_

#include "error-proc.h"
#include "storage-state-name.h"
#include "memory.h"
#include "util.h"

namespace std {

  /**
   * @brief data structure of node in chain structure
   *
   * The node is a unit of chain which seqentially arranges a series of
   * nodes together. The node stores the pointer to content for flexibility.
   * To ease the navigation along the chain, the pointers of the parent and
   * child nodes are also recorded. Several flags for neighbor nodes and
   * contents are also declared.
   * 
   * T is the type of data inside the node
   *
   * @note two pointers (parent and child) enables the visit of the chain
   *      in both forward and backward directions.
   */
  template <typename T>
  struct ChainNode {

    /**
     * @brief abbreviation for the type of node in chain
     */
    typedef ChainNode<T>  Type;

    /**
     * @brief the pointer to the parent node
     */
    Type* parent;
    /**
     * @brief the pointer to the child node
     */
    Type* child;
    /**
     * @brief the pointer to the content
     */
    T *content;
    /**
     * @brief the flag indicating the storage state of pointer to parent
     */
    unsigned int parentstate;
    /**
     * @brief the flag indicating the storage state of pointer to child
     */
    unsigned int childstate;
    /**
     * @brief the flag indicating the storage state of pointer to content
     */
    unsigned int contentstate;

    /**
     * @brief default initiator
     *
     * All the pointers are nullified, and all the flags are assigned
     * with no information.
     */
    ChainNode() 
      : parent(), child(), content(), 
        parentstate(Unused), childstate(Unused), contentstate(Unused) {}
    /**
     * @brief initiator from another node in chain
     *
     * It is prohibited and pop up an erro message.
     *
     * @param N [in] the input node in chain
     */
    ChainNode(const Type& N) { myError("Cannot create from Chain Node"); }
    /**
     * @brief copy from another node in chain
     *
     * It is implemented with assign operation.
     *
     * @param CN [in] the input node in chain
     * @return the reference to the resultant node in chain.
     */
    Type& operator=(const Type& CN) { assign(*this,CN); return *this; }
    /**
     * @brief destructor
     *
     * It is implemented with release operation.
     */
    ~ChainNode() { release(*this); }

    /**
     * @brief access the content of node in chain
     *
     * This is an interface to ease the using of content. It just takes
     * the data pointed by the pointer content. The pointer content is
     * checked for availability before this operation. 
     *
     * @return the reference to the data pointed by pointer content.
     */
    T& operator()() { assert(IsAvailable(content)); return *content; }
    /**
     * @brief visit the content of node in chain
     *
     * This is an interfaceto read content of node. It just takes the data
     * through the pointer content. The pointer content is checked for
     * availability before using.
     *
     * @return the const reference to the data pointed by the pointer content
     */
    const T& operator()() const {
      assert(IsAvailable(content));
      return *content;
    }

  };

  /**
   * @brief Check the availability of the node in chain
   *
   * It is implemented by checking the availability of pointer content.
   *
   * T is the type of data in node.
   *
   * @param CN [in] the node to be checked.
   * @return the availability of the node in chain
   */
  template <typename T>
  bool IsAvailable(const ChainNode<T>& CN) { return IsAvailable(CN.content); }

  /**
   * @brief release the storage of node
   *
   * This release operation delete the storage of content based on its type.
   * The pointers of parent and child for the parent and child nodes are
   * redefined based on present information. Then, pointers and flags in
   * present node are nullified.
   *  
   * T is the type of data in node.
   *
   * @param N [in,out] the node to be released.
   * @return nothing
   * @note The release for the node of chain is different from that
   *       for the node in binary tree.
   */
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

  /**
   * @brief assign node in chain with another
   *
   * Just copy the data pointed by content in source node to destination node.
   * The source and destination nodes are all checked for their availability
   * before this operation.
   *
   * T is the type of data in node.
   *
   * @param dest [out] the node to accept the input information
   * @param src [in] the node storing input information
   * @return nothing.  
   */
  template <typename T>
  void assign(ChainNode<T>& dest, const ChainNode<T>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    dest()=src();
  }

  /**
   * @brief refer to another node
   *
   * This operation just asssigns all the pointers in the source node
   * as those in destination node. This enables a reference for source
   * node. The flags in the destination nodes are also changed
   * correspondingly.
   *
   * T is the type of data in the node.
   *
   * @param dest [out] the node to accept information
   * @param src [in] the node storing input information
   * @return nothing
   */
  template <typename T>
  void refer(ChainNode<T>& dest, const ChainNode<T>& src) {
    dest.parent=const_cast<ChainNode<T>*>(src.parent);
    dest.child=const_cast<ChainNode<T>*>(src.child);
    dest.content=const_cast<T*>(src.content);
    dest.parentstate=Reference;
    dest.childstate=Reference;
    dest.contentstate=Reference;
  }

  /**
   * @brief allocate a node in chain
   *
   * Just allocate the storage for content, and change the corresponding
   * flag. The content is released before this operation to avoid memory
   * leak.
   *
   * T is the type of data in node.
   *
   * @param CN [in,out] the node to be allocated
   * @return nothing
   */ 
  template <typename T>
  void allocate(ChainNode<T>& CN) {
    safe_delete(CN.content);
    CN.content=new T;
    CN.contentstate=Allocated;
  }

  /**
   * @brief add a node as the the parent node of destination node.
   *
   * This operation is to insert the node parent before the node dest.
   * The pointers in the node dest, the original parent of dest, and
   * the newly inserted node would be changed based on their relations.
   * If the original parent or child of the inserted node is allocated
   * (rather than reference), it would be necessary to be released
   * before this operation to avoid memory leak.
   *
   * T is the type of data in node.
   *
   * @param dest [in,out] the node in the chain.
   * @param parent [in,out] the node to be inserted before dest
   * @return nothing
   */
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

  /**
   * @brief add a new node with certain content as parent of destination node
   *
   * This is similar as the operation add_parent by inserting a node
   * before destination. The difference is the inserted node is newly
   * allocated. The content of this allocated node is assigned based on
   * input information.
   *
   * T is the type of data in node.
   *
   * @param dest [in,out] the node in the chain
   * @param content [in] the content for the inserted node
   * @param cflag [in] the flag to access the input content. It defaultly
   *                   takes the values of Reference indicating the content
   *                   in node is assigned as a reference.
   * @return nothing
   */
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

