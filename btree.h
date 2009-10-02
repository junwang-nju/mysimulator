
#ifndef _Binary_Tree_H_
#define _Binary_Tree_H_

#include "error-proc.h"
#include <cstdlib>

namespace std {

  template <typename KeyType, typename ValueType>
  class btree_node {
    public:
      typedef btree_node<KeyType,ValueType>   Type;
      KeyType* key;
      ValueType* value;
      Type* parent;
      Type* left;
      Type* right;
      btree_node() : key(NULL), value(NULL),
                     parent(NULL), left(NULL), right(NULL) {}
      btree_node(const KeyType& K, const ValueType& V, 
                 const Type* p, const Type* l=NULL, const Type* r=NULL)
        : key(const_cast<KeyType*>(&K)), value(const_cast<ValueType*>(&V)),
          parent(const_cast<Type*>(p)), left(const_cast<Type*>(l)),
          right(const_cast<Type*>(r)) {
      }
      btree_node(Type& node) {
        myError("copier is disable for nodes of btree");
      }
  };

  template <typename KeyType, typename ValueType>
  class btree {
    public:
      typedef btree<KeyType,ValueType>        Type;
      typedef btree_node<KeyType,ValueType>   NodeType;
      NodeType root;
      btree() : root() {}
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
      ValueType* get(const KeyType& K) {
        if(root.key==NULL)  return NULL;
        NodeType* present=&root;
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

