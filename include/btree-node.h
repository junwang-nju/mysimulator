
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
      int ParentFg;
      bool AllocFg;
    public:
      BTreeNode() : Key(NULL), Value(NULL),
                    Parent(NULL), Left(NULL), Right(NULL), ParentFg(0),
                    AllocFg(false) {}
      BTreeNode(const Type& bn) {
        myError("Cannot create from node of binary tree");
      }
      BTreeNode(const KeyType* K, const ValueType* V, const Type* p,
                const int pfg=0, const Type* l=NULL, const Type* r=NULL,
                const bool afg=false)
        : Key(const_cast<KeyType*>(K)), Value(const_cast<ValueType*>(V)),
          Parent(const_cast<Type*>(p)), Left(const_cast<Type*>(l)),
          Right(const_cast<Type*>(r)), ParentFg(pfg), AllocFg(afg) {
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
      const int WhereParentFrom() const;
      void SetParent(const Type* p, const int pfg);
      void SetLeft(const Type* l);
      void SetRight(const Type* r);
      const bool IsAllocByTree() const;
      void SetTreeAllocFlag(const bool afg);
  };
}

#endif

