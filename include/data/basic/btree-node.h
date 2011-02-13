
/**
 * @file btree-node.h
 * @brief the node type of binary tree
 *
 * This file gives the data structure for the node in binary tree and
 * some related operations. It is a basic part of binary tree. 
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Binary_Tree_Node_H_
#define _Binary_Tree_Node_H_

#include "operation/basic/util.h"
#include "data/name/storage-state.h"
#include "operation/basic/error-op.h"
#include "operation/basic/memory.h"
#include <cstdlib>
#include <cassert>

namespace std {

  /**
   * @brief the name of branch which a node is in.
   *
   * A series of names for branches are defines as shortcuts for using.
   */
  enum BranchName {
    /**
     * @brief the flag indicating that the node does not belong to any branch
     */
    Unassigned=0,
    /**
     * @brief the flag indicating the node is in the left branch of parent
     */
    LeftBranch,
    /**
     * @brief the flag indicating the node is in the right branch of parent
     */
    RightBranch
  };

  /**
   * @brief data structure for node in binary tree
   *
   * This data structure contains the pointers to the necessary content
   * of key and value. To ease the navigation on the tree, the pointers
   * to the parent, left child, and right child are also included. Besides,
   * several flags related to branch, key, and values are also used for
   * flexibility.
   *
   * KeyType is the type of keys. ValueType is the type of values. 
   */
  template <typename KeyType, typename ValueType>
  struct BTreeNode {

    /**
     * @brief abbreviation for BTreeNode object
     */
    typedef BTreeNode<KeyType,ValueType>  Type;

    /**
     * @brief pointer to the key of node
     */
    KeyType* key;
    /**
     * @brief pointer to the value of node
     */
    ValueType* value;
    /**
     * @brief pointer to the parent node
     */
    Type* parent;
    /**
     * @brief pointer to the left child
     */
    Type* left;
    /**
     * @brief pointer to the right child
     */
    Type* right;
    /**
     * @brief the flag indicating thich branch this node belongs to
     */
    unsigned int branch;
    /**
     * @brief the flag indicating the storage state of key
     */
    unsigned int keystate;
    /**
     * @brief the flag indicating the storage state of value
     */
    unsigned int valuestate;

    /**
     * @brief default initiator
     *
     * Just assign all the pointers as NULL, and assign all flags
     * with no information.
     */
    BTreeNode()
      : key(NULL), value(NULL), parent(NULL), left(NULL), right(NULL),
        branch(Unassigned), keystate(Unused), valuestate(Unused) {}
    /**
     * @brief initiator from another node for binary tree
     *
     * It is prohibited and pop up an error message.
     *
     * @param N [in] the input BTreeNode object.
     */ 
    BTreeNode(const Type& N) { Error("Cannot create from BinaryTree Node"); }
    /**
     * @brief copy from another node in binary tree
     *
     * It is implemented with assign operation.
     *
     * @param BN [in] the input node in binary tree
     * @return the reference to the resultant BTreeNode object. 
     */
    Type& operator=(const Type& BN) { assign(*this,BN); return *this; }
    /**
     * @brief destructor
     *
     * It is implemented with release operation.
     */
    ~BTreeNode() { release(*this); }

  };

  /**
   * @brief check the availability of a node in binary tree
   *
   * It is implemented by check the availability of the pointers to
   * the key and value in the node.
   *
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param BN [in] the node to be checked.
   * @return the availability of the concerned node.
   */
  template <typename KeyType, typename ValueType>
  bool IsAvailable(const BTreeNode<KeyType,ValueType>& BN) {
    return IsAvailable(BN.key)&&IsAvailable(BN.value);
  }

  /**
   * @brief assign a node from another
   *
   * The destination node is released at first to avoid memory leak.
   * Then the key and value of the source node are refered by the
   * corresponding part of the destination node.
   *
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param destBN [out] the node to be re-written
   * @param srcBN [in] the node to be copied
   * @return nothing
   */
  template <typename KeyType, typename ValueType>
  void assign(BTreeNode<KeyType,ValueType>& destBN,
              const BTreeNode<KeyType,ValueType>& srcBN) {
    assert(IsAvailable(srcBN));
    release(destBN);
    destBN.key=srcBN.key;
    destBN.value=srcBN.value;
    destBN.keystate=Reference;
    destBN.valuestate=Reference;
  }

  /**
   * @brief release a node in binary tree
   *
   * The key and value of the node are releases based on their types.
   * The related pointer for parent node is nullified with the parent node
   * untouched. The child nodes are released by deleting the pointers
   * inside the node. The flags are then cleaned.
   *
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param BN [in,out] The node to be released. After this operation,
   *                    all the contents are same as those after initiation
   *                    by default initiator.
   * @return nothing.
   * @note This release may totally destroy the child tree when the pointers
   *       to child nodes are deleted.
   */
  template <typename KeyType, typename ValueType>
  void release(BTreeNode<KeyType,ValueType>& BN) {
    if(BN.keystate==Allocated)      safe_delete(BN.key);    else BN.key=NULL;
    if(BN.valuestate==Allocated)    safe_delete(BN.value);  else BN.value=NULL;
    BN.parent=NULL;
    safe_delete(BN.left);
    safe_delete(BN.right);
    BN.branch=Unassigned;
    BN.keystate=Unused;
    BN.valuestate=Unused;
  }

}

#endif

