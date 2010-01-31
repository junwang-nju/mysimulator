
#ifndef _Binary_Tree_Node_H_
#define _Binary_Tree_Node_H_

#include "error-proc.h"

namespace std {
  template <typename KeyType, typename ValueType>
  class BTreeNode {
    public:
      typedef BTreeNode<KeyType,ValueType> Type;
    protected:
      KeyType* Key;
      ValueType*  Value;
      Type* Parent;
      Type* Left;
      Type* Right;
      bool ParentFg;
    public:
      BTreeNode() : Key(NULL), Value(NULL),
                    Parent(NULL), Left(NULL), Right(NULL), ParentFg(true) {}
      BTreeNode(const Type& bn) {
        myError("Cannot create from node of binary tree");
      }
      BTreeNode(const KeyType* K, const ValueType* V, const Type* p,
                const bool pfg, const Type* l=NULL, const Type* r=NULL)
        : Key(const_cast<KeyType*>(K)), Value(const_cast<ValueType*>(V)),
          Parent(const_cast<Type*>(p)), Left(const_cast<Type*>(l)),
          Right(const_cast<Type*>(r)), ParentFg(pfg) {
      }
      ~BTreeNode() { clear(); }
      Type& operator=(const Type& bn) {
        Key=bn.Key;
        Value=bn.Value;
        return *this;
      }
      void clear();
      KeyType*& ptr2key();
      const KeyType* ptr2key() const;
      ValueType*& ptr2value();
      const ValueType* ptr2value() const;
      const Type* parent() const;
      const Type* left() const;
      const Type* right() const;
      const bool IsParentFromLeft() const;
      void SetParent(const Type* p, const bool pfg);
      void SetLeft(const Type* l);
      void SetRight(const Type* r);
  };
}

#endif

