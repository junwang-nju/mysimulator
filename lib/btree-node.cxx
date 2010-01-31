
#include "btree-node.h"

namespace std {

  template <typename KeyType,typename ValueType>
  void BTreeNode<KeyType,ValueType>::clear() {
    Key=NULL; Value=NULL; Parent=NULL; Left=NULL; Right=NULL; ParentFg=true;
  }

  template <typename KeyType,typename ValueType>
  KeyType*& BTreeNode<KeyType,ValueType>::ptr2key() { return Key; }

  template <typename KeyType,typename ValueType>
  const KeyType* BTreeNode<KeyType,ValueType>::ptr2key() const { return Key; }

  template <typename KeyType,typename ValueType>
  ValueType*& BTreeNode<KeyType,ValueType>::ptr2value() { return Value; }

  template <typename KeyType,typename ValueType>
  const ValueType* BTreeNode<KeyType,ValueType>::ptr2value() const {
    return Value;
  }

  template <typename KeyType,typename ValueType>
  const bool BTreeNode<KeyType,ValueType>::IsParentFromLeft() const {
    return ParentFg;
  }

  template <typename KeyType,typename ValueType>
  const BTreeNode<KeyType,ValueType>*
  BTreeNode<KeyType,ValueType>::parent() const {
    return Parent;
  }

  template <typename KeyType,typename ValueType>
  const BTreeNode<KeyType,ValueType>*
  BTreeNode<KeyType,ValueType>::left() const {
    return Left;
  }

  template <typename KeyType,typename ValueType>
  const BTreeNode<KeyType,ValueType>*
  BTreeNode<KeyType,ValueType>::right() const {
    return Right;
  }

  template <typename KeyType,typename ValueType>
  void BTreeNode<KeyType,ValueType>::SetParent(
      const BTreeNode<KeyType,ValueType>* p, const bool pfg) {
    Parent=p;
    ParentFg=pfg;
  }

  template <typename KeyType,typename ValueType>
  void BTreeNode<KeyType,ValueType>::SetLeft(
      const BTreeNode<KeyType,ValueType>* l) {
    Left=l;
  }

  template <typename KeyType,typename ValueType>
  void BTreeNode<KeyType,ValueType>::SetRight(
      const BTreeNode<KeyType,ValueType>* r) {
    Right=r;
  }

}

