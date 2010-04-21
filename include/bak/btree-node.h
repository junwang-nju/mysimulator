
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

      void clear() {
        Key=NULL; Value=NULL; Parent=NULL; Left=NULL; Right=NULL; ParentFg=0;
      }

      KeyType*& ptr2key() { return Key; }

      const KeyType* ptr2key() const { return Key; }

      ValueType*& ptr2value() { return Value; }

      const ValueType* ptr2value() const { return Value; }

      const Type* parent() const { return Parent; }

      const Type* left() const { return Left; }

      const Type* right() const { return Right; }

      const int WhereParentFrom() const { return ParentFg; }

      void SetParent(const Type* p, const int pfg) {
        Parent=const_cast<Type*>(p);
        ParentFg=pfg;
      }

      void SetLeft(const Type* l) { Left=const_cast<Type*>(l); }

      void SetRight(const Type* r) { Right=const_cast<Type*>(r); }

      const bool IsAllocByTree() const { return AllocFg; }

      void SetTreeAllocFlag(const bool afg) { AllocFg=afg; }

  };

}

#endif

