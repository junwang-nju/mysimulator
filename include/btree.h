
/**
 * @file btree.h
 * @brief the data structure and operation of binary tree
 *
 * This file describes the data structure and operations for binary
 * tree. This data structure may be efficient in searching certain items.
 * The rate is in logarithm manner in average, which is faster than
 * the linear manner along an array.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Binary_Tree_H_
#define _Binary_Tree_H_

#include "btree-node.h"

namespace std {

  /**
   * @brief data structure of binary tree
   *
   * Binary tree is a kind of tree structure. Binary tree arranges
   * the elements based on their relation (larger or smaller). All
   * the elements smaller than a certain element are arranged on the
   * left branch, and the others are put on the right branch. Each
   * element is a combination (or pair) of key and value. 
   *
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @note The binary tree is not unique for a set of data. The arrangement
   *       of elements depends on the order to insert elements.
   */
  template <typename KeyType, typename ValueType>
  struct BTree {

    /**
     * @brief definition of node type
     */
    typedef BTreeNode<KeyType,ValueType>  NodeType;
    /**
     * @brief abbreviation of the type of binary tree
     */
    typedef BTree<KeyType,ValueType>      Type;

    /**
     * @brief the pointer of root node in the tree
     *
     * This pointer gives out the entrance of the tree.
     */
    NodeType *root;

    /**
     * @brief default initiator
     *
     * Just assign the pointer to the root node as NULL.
     */
    BTree() : root(NULL) {}

    /**
     * @brief initiator from another binary tree
     *
     * It is prohibited and an eror message is pop-up.
     *
     * @param BT [in] the input BTree object
     */
    BTree(const Type& BT) { myError("Cannot create from BinaryTree"); }

    /**
     * @brief copy from another BTree object
     *
     * It is implemented with assign function.
     *
     * @param BT [in] the input BTree object
     * @return the reference to the resultant BTree object
     */
    Type& operator=(const Type& BT) { assign(*this,BT); return *this; }

    /**
     * @brief destructor
     *
     * It is implemented with release function.
     */
    ~BTree() { release(*this); }

  };

  /**
   * @brief check if a BTree object is available
   *
   * It is implemented by checking the availability of pointer of root node.
   *
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param BT [in] the BTree object to be checked.
   */
  template <typename KeyType, typename ValueType>
  bool IsAvailable(const BTree<KeyType,ValueType>& BT) {
    return IsAvailable(BT.root);
  }

  /**
   * @brief release a BTree object
   *
   * The release operation is implemented by iteratively releasing the
   * leafs of tree. In my procedure, a node is checked if it has child.
   * if a child is found, the procedure goes to the child leaf to do the
   * same check until it is just a leaf. The leaf is deleted then, left
   * first and right later. It is a depth-first search.  
   * 
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param BT [in,out] The BTree object to be freed. After this operation,
   *                    the pointer of root node in this object is set as
   *                    NULL.
   * @return nothing
   */
  template <typename KeyType, typename ValueType>
  void release(BTree<KeyType,ValueType>& BT) {
    BTreeNode<KeyType,ValueType> *present, *tofree;
    present=BT.root;
    while(IsAvailable(present)) {
      if(IsAvailable(present->left))  present=present->left;
      else if(IsAvailable(present->right))  present=present->right;
      else {
        tofree=present;
        present=tofree->parent;
        if(tofree->branch==LeftBranch) present->left=NULL;
        else if(tofree->branch==RightBranch)  present->right=NULL;
        else if(tofree->branch==Unassigned) {}
        else myError("Unknown Branch Flag");
        safe_delete(tofree);
      }
    }
    BT.root=NULL;
  }

  /**
   * @brief assign a part of BTree object to another based on node pointer
   *
   * This assign operation copies the content of a BTree object into another.
   * The inputs are the root pointers of destination and souce BTree objects.
   * This increases the flexibility. As a supplementation, the expected
   * parent node for destination BTree and the branch type from this parent
   * node are also given. Then the nodes in the source tree are enumerated,
   * and corresponding nodes in destination tree are allocated and assigned.
   * The resultant tree is a copy (not a reference) to the source tree. The
   * pointer to destination tree is freed at first to avoid memory leak.
   *
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param destBN [out] pointer to root node of BTree object as destination
   * @param srcBN [in] pointer to root node of BTree object as source
   * @param destPN [in] pointer to parent node of BTree object pointed by
   *                    destBN.
   * @param destBR [in] the branch flag indicating which branch the BTree
   *                    object pointed by destBN belongs to.
   * @return nothing
   * @note the free operation for destBN may not remove the original tree
   *       under the pointer destBN since this operation is just for a node.
   */
  template <typename KeyType, typename ValueType>
  void assign(BTreeNode<KeyType,ValueType>*& destBN,
              const BTreeNode<KeyType,ValueType>* srcBN,
              const BTreeNode<KeyType,ValueType>* destPN,
              const unsigned int destBR) {
    safe_delete(destBN);
    if(IsAvailable(srcBN)) {
      destBN=new BTreeNode<KeyType,ValueType>;
      destBN->key=new KeyType;
      destBN->value=new ValueType;
      *(destBN->key)=*(srcBN->key);
      *(destBN->value)=*(srcBN->value);
      destBN->keystate=Allocated;
      destBN->valuestate=Allocated;
      destBN->parent=const_cast<BTreeNode<KeyType,ValueType>*>(destPN);
      destBN->branch=destBR;
      if(IsAvailable(srcBN->left))
        assign(destBN->left,srcBN->left,destBN,LeftBranch);
      if(IsAvailable(srcBN->right))
        assign(destBN->right,srcBN->right,destBN,RightBranch);
    }
  }

  /**
   * @brief assign a BTree object from another
   *
   * This is implemented with the assign operation based on the pointers to
   * the root nodes of BTree objects. The destination BTree object is released
   * at first to avoid memory leak.
   *
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param destBT [out] the BTree object containing the data
   * @param srcBT [in] the BTree object inputing the data
   * @return nothing
   */
  template <typename KeyType, typename ValueType>
  void assign(BTree<KeyType,ValueType>& destBT,
              const BTree<KeyType,ValueType>& srcBT) {
    release(destBT);
    assign(destBT.root,srcBT.root,
           static_cast<const BTreeNode<KeyType,ValueType>*>(NULL),
           Unassigned);
  }

  /**
   * @brief insert a node with certain content in a BTree object
   *
   * A node for BTre is newly allocated. Its contents is copied or refered
   * based on the input data and flag. Then through comparing with existed
   * nodes, this node is inserted into a BTree object. If the new node is
   * small, it would be put in left branch, otherwise in right branch.
   * This new node generally becomes a new leaf in the concerned tree.
   * 
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param destBT [in,out] the BTree object to accept the insert node
   * @param key,value [in] the expected data for key and value of the new node
   * @param kflag,vflag [in] the flags indicating the input key and value
   *                         should be refered ot copied. The default mode
   *                         is to refer the input data for efficiency.
   * @return nothing
   */
  template <typename KeyType, typename ValueType>
  void insert(BTree<KeyType,ValueType>& destBT,
              const KeyType& key, const ValueType& value,
              const unsigned int kflag=Reference,
              const unsigned int vflag=Reference) {
    BTreeNode<KeyType,ValueType> *present;
    int cmp;
    present=destBT.root;
    while(IsAvailable(present)) {
      cmp=compare(key,*(present->key));
      if(cmp==0) {
        if(vflag==Reference) present->value=const_cast<ValueType*>(&value);
        else if(vflag==Allocated) {
          myWarn("Same Key met!");
          present->value=new ValueType;
          *(present->value)=value;
        } else myError("Imporoper Value Flag");
        present->valuestate=vflag;
        return;
      } else if(cmp<0) {
        if(IsAvailable(present->left))  present=present->left;
        else {
          present->left=new BTreeNode<KeyType,ValueType>;
          if(kflag==Reference) present->left->key=const_cast<KeyType*>(&key);
          else if(kflag==Allocated) {
            present->left->key=new KeyType;
            *(present->left->key)=key;
          } else myError("Imporoper Key Flag");
          present->left->keystate=kflag;
          if(vflag==Reference)
            present->left->value=const_cast<ValueType*>(&value);
          else if(vflag==Allocated) {
            present->left->value=new ValueType;
            *(present->left->value)=value;
          } else myError("Imporoper Value Flag");
          present->left->valuestate=vflag;
          present->left->parent=present;
          present->left->branch=LeftBranch;
          return;
        }
      } else {
        if(IsAvailable(present->right)) present=present->right;
        else {
          present->right=new BTreeNode<KeyType,ValueType>;
          if(kflag==Reference) present->right->key=const_cast<KeyType*>(&key);
          else if(kflag==Allocated) {
            present->right->key=new KeyType;
            *(present->right->key)=key;
          } else myError("Imporoper Key Flag");
          present->right->keystate=kflag;
          if(vflag==Reference)
            present->right->value=const_cast<ValueType*>(&value);
          else if(vflag==Allocated) {
            present->right->value=new ValueType;
            *(present->right->value)=value;
          } else myError("Imporoper Value Flag");
          present->right->valuestate=vflag;
          present->right->parent=present;
          present->right->branch=RightBranch;
          return;
        }
      }
    }
    destBT.root=new BTreeNode<KeyType,ValueType>;
    if(kflag==Reference) destBT.root->key=const_cast<KeyType*>(&key);
    else if(kflag==Allocated) {
      destBT.root->key=new KeyType;
      *(destBT.root->key)=key;
    }
    destBT.root->keystate=kflag;
    if(vflag==Reference) destBT.root->value=const_cast<ValueType*>(&value);
    else if(vflag==Allocated) {
      destBT.root->value=new ValueType;
      *(destBT.root->value)=value;
    }
    destBT.root->valuestate=vflag;
  }

  /**
   * @brief get a value based on the key from a BTree object
   *
   * It is implemented with the getNode operation. The related node is
   * found out firstly. The pointer to the concerned value is output then.
   *
   * KeyType is the type of keys. ValueType is the type of values.
   *
   * @param BT [in] the BTree object to be touched.
   * @param key [in] the key to be used to search for value.
   * @return the const pointer to the corresponding value, and NULL for
   *         no-match-found case. 
   * @note Here, we use the pointer to value is to be compatible with
   *       the case that the key does not in the BTree object.
   */
  template <typename KeyType, typename ValueType>
  const ValueType* get(
      const BTree<KeyType,ValueType>& BT, const KeyType& key) {
    const BTreeNode<KeyType,ValueType>* BN=getNode(BT,key);
    return (IsAvailable(BN)?BN->value:NULL);
  }

  template <typename KeyType, typename ValueType>
  const BTreeNode<KeyType,ValueType>* getNode(
      const BTree<KeyType,ValueType>& BT, const KeyType& key) {
    BTreeNode<KeyType,ValueType> *present;
    int cmp;
    present=BT.root;
    while(IsAvailable(present)) {
      cmp=compare(key,*(present->key));
      if(cmp==0)      break;
      else if(cmp<0)  present=present->left;
      else            present=present->right;
    }
    return present;
  }

  template <typename KeyType, typename ValueType>
  void removeNode(BTree<KeyType,ValueType>& BT, const KeyType& key) {
    const BTreeNode<KeyType,ValueType> *BN=getNode(BT,key);
    removeNode(BT,BN);
  }

  template <typename KeyType, typename ValueType>
  void removeNode(BTree<KeyType,ValueType>& BT,
                  const BTreeNode<KeyType,ValueType>* iBN){
    BTreeNode<KeyType,ValueType> *BN;
    BN=const_cast<BTreeNode<KeyType,ValueType>*>(iBN);
    assert(BN==getNode(BT,*(BN->key)));
    if(IsAvailable(BN)) {
      if(!IsAvailable(BN->left)) {
        if(IsAvailable(BN->parent)) {
          if(BN->branch==LeftBranch)  BN->parent->left=BN->right;
          else if(BN->branch==RightBranch)  BN->parent->right=BN->right;
          else myError("Improper Branch Flag");
        } else BT.root=BN->right;
        BN->right=NULL;
      } else if(!IsAvailable(BN->right)) {
        if(IsAvailable(BN->parent)) {
          if(BN->branch==LeftBranch)  BN->parent->left=BN->left;
          else if(BN->branch==RightBranch)  BN->parent->right=BN->left;
          else myError("Improper Branch Flag");
        } else BT.root=BN->left;
        BN->left=NULL;
      } else {
        BTreeNode<KeyType,ValueType> *movenode;
        movenode=BN->right;
        while(IsAvailable(movenode->left))  movenode=movenode->left;
        if(movenode->branch==LeftBranch)
          movenode->parent->left=movenode->right;
        else if(movenode->branch==RightBranch)
          movenode->parent->right=movenode->right;
        if(IsAvailable(movenode->right)) {
          movenode->right->parent=movenode->parent;
          movenode->right->branch=movenode->branch;
        }
        movenode->parent=BN->parent;
        movenode->branch=BN->branch;
        if(IsAvailable(movenode->parent)) {
          if(movenode->branch==LeftBranch)
            movenode->parent->left=movenode;
          else if(movenode->branch==RightBranch)
            movenode->parent->right=movenode;
          else myError("Improper Branch Flag");
        } else BT.root=movenode;
        movenode->left=BN->left;  BN->left=NULL;
        movenode->right=BN->right;  BN->right=NULL;
      }
    }
    safe_delete(BN);
  }

}

#endif

