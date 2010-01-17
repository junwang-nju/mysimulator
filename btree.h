
/**
 * @file btree.h
 * @brief The implementation for binary tree
 *
 * The binary tree is a useful data structure for efficient random
 * access. In our package it is implemented as the storage for
 * parameter libraries.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 * @todo Some operations for binary tree (such deleting) are not
 *       implemented now.
 */

#ifndef _Binary_Tree_H_
#define _Binary_Tree_H_

#include "error-proc.h"
#include <cstdlib>

namespace std {

  /**
   * @brief the node class for the binary tree
   *
   * It is a collection of the pointers to present data and the neighboring
   * objects (including parent, left and right children). This object is used
   * as a node in the binary tree. These pointers enable the navigation
   * in the tree structure.
   *
   * \a KeyType
   *    The type of key
   *
   * \a ValueType
   *    The type of value
   */
  template <typename KeyType, typename ValueType>
  class btree_node {
    public:
      /**
       * @brief alias for the node type in btree structure
       */
      typedef btree_node<KeyType,ValueType>   Type;
      /**
       * @brief the pointer to the key object of content
       */
      KeyType* key;
      /**
       * @brief the pointer to the value object of content
       */
      ValueType* value;
      /**
       * @brief the pointer to the parent node
       */
      Type* parent;
      /**
       * @brief the pointer to the left node
       */
      Type* left;
      /**
       * @brief the pointer to the right node
       */
      Type* right;
      /**
       * @brief default initiator
       *
       * Just initiate these pointers as NULL.
       */
      btree_node() : key(NULL), value(NULL),
                     parent(NULL), left(NULL), right(NULL) {}
      /**
       * @brief initiator with input key, value and neighbor pointers
       *
       * Just initiate the pointers based on the input objects.
       *
       * @param [in] K
       *        The input \a KeyType object as key
       *
       * @param [in] V
       *        The input \a ValueType object as value
       *
       * @param [in] p
       *        The pointer to the parent node
       *
       * @param [in] l
       *        The pointer to the left child, which takes NULL as
       *        default value.
       *
       * @param [in] r
       *        The pointer to the right child, which takes NULL as
       *        default value.
       */
      btree_node(const KeyType& K, const ValueType& V, 
                 const Type* p, const Type* l=NULL, const Type* r=NULL)
        : key(const_cast<KeyType*>(&K)), value(const_cast<ValueType*>(&V)),
          parent(const_cast<Type*>(p)), left(const_cast<Type*>(l)),
          right(const_cast<Type*>(r)) {
      }
      /**
       * @brief destructor
       *
       * Just set all the pointers as NULL.
       */
      ~btree_node() {
        key=NULL;     value=NULL;
        parent=NULL;  left=NULL;    right=NULL;
      }
      /**
       * @brief initiator from another node object
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] node
       *        The input node object
       */
      btree_node(Type& node) {
        myError("copier is disable for nodes of btree");
      }
      /**
       * @brief copier from another node object
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] node
       *        The input node object
       *
       * @return the reference to the present object
       */
      Type& operator=(const Type& bnode) {
        myError("assignment is disable for nodes of btree");
        return *this;
      }
  };

  /**
   * @brief the binary tree structure
   *
   * This is a binary-tree structure. It is a kind of storage for efficient
   * search.
   *
   * @todo the deletion of nodes is not implemented now. It would be useful
   *       when the parameter are modified. 
   */
  template <typename KeyType, typename ValueType>
  class btree {
    public:
      /**
       * @brief alias for the binary tree structure
       */
      typedef btree<KeyType,ValueType>        Type;
      /**
       * @brief alias for the node of binary tree structure
       */
      typedef btree_node<KeyType,ValueType>   NodeType;
      /**
       * @brief the root node of the whole tree
       */
      NodeType root;
      /**
       * @brief default initiator
       *
       * Just initiate the root node with null parameter.
       */
      btree() : root() {}
      /**
       * @brief destructor
       *
       * Initiate the nodes sequentially until the root node, and assign
       * the related pointers as NULL. 
       */
      ~btree() {
        NodeType *present=&root, *tofree;
        while(true) {
          if(present->left!=NULL) present=present->left;
          else if(present->right!=NULL) present=present->right;
          else {
            if(present==&root)  break;
            else {
              tofree=present;
              present=present->parent;
              delete tofree;
            }
          }
        }
        root.left=NULL;
        root.right=NULL;
      }
      /**
       * @brief initiator from another binary tree
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] bt
       *        The input binary-tree object
       */
      btree(const Type& bt) {
        myError("assignment is disable for btree");
      }
      /**
       * @brief copier from another binary tree
       *
       * It is prohibited by popping up an error.
       *
       * @param [in] bt
       *        The input binary-tree object
       *
       * @return the reference to the present object
       */
      Type& operator=(const Type& bt) {
        myError("assignment is disable for btree");
        return *this;
      }
      /**
       * @brief insert a new key and value
       *
       * Through navigating along the tree, a false flag is returned
       * when there is already an element in the tree, or insert
       * new node to the tree.
       *
       * @param [in] K
       *        The input key object
       *
       * @param [in] V
       *        The input value object
       *
       * @return the flag indicating if the insertion is OK.
       */
      bool insert(const KeyType& K, const ValueType& V) {
        if(root.key==NULL) {
          root.key=const_cast<KeyType*>(&K);
          root.value=const_cast<ValueType*>(&V);
          return true;
        }
        NodeType* present=&root;
        int cmp;
        while(true) {
          cmp=compare(*(present->key),K);
          if(cmp==0)  return false;
          else if(cmp<0) {
            if(present->left==NULL) {
              present->left=new NodeType(K,V,present,NULL,NULL);
              return true;
            } else
              present=present->left;
          } else {
            if(present->right==NULL) {
              present->right=new NodeType(K,V,present,NULL,NULL);
              return true;
            } else
              present=present->right;
          }
        }
        return true;
      }
      /**
       * @brief extract the value matching the input key
       *
       * Through navigating along the tree, the certain node matching
       * the input key is extracted. If no elements are found, NULL
       * pointer is obtained.
       *
       * @param [in] K
       *        The input \a KeyType key
       *
       * @return the pointer to the expected value object.
       */
      const ValueType* get(const KeyType& K) const {
        if(root.key==NULL)  return NULL;
        NodeType* present=const_cast<NodeType*>(&root);
        int cmp;
        while(true) {
          cmp=compare(*(present->key),K);
          if(cmp==0)  return present->value;
          else if(cmp<0) {
            if(present->left==NULL) return NULL;
            else present=present->left;
          } else {
            if(present->right==NULL)  return NULL;
            else present=present->right;
          }
        }
        return NULL;
      }
  };

}

#endif

