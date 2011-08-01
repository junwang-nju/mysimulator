
#ifndef _Binary_Tree_Interface_H_
#define _Binary_Tree_Interface_H_

#include "binary-tree/node/interface.h"
#include "intrinsic-type/release.h"
#include "object/compare.h"
#include "object/allocate.h"
#include "object/copy.h"
#include "io/error.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct BTree {

    public:

      typedef BTree<KeyType,ValueType>      Type;
      typedef BTreeNode<KeyType,ValueType>  NodeType;

      NodeType*  root;

      BTree() : root(NULL) {}
      ~BTree() { clearData(); }

      void clearData() { delete_pointer(root); }
      bool isvalid() const { return IsValid(root); }

      void insert(const KeyType& key, const ValueType& value,
                  const bool KeyRefFlag=true, const bool ValueRefFlag=true) {
        NodeType* now;
        now=root;
        int cmp;
        bool iflag;
        while(true) {
          cmp=0;
          if(IsValid(now)) cmp=compare(key,now->key);
          if(IsValid(now)) COut<<key<<"\t"<<now->key<<"\t"<<cmp<<Endl;
          iflag=false;
          if(cmp==0) {
            if(IsValid(now)) Warn("Same Key When Inserting for Binary-Tree!");
            else {
              root=new NodeType;
              now=root;
              now->wTree=UnassignedBranch;
              iflag=true;
            }
          } else if(cmp<0) {
            if(!IsValid(now->left)) {
              now->left=new NodeType;
              now->left->parent=now;
              now->left->wTree=LeftBranch;
              iflag=true;
            }
            now=now->left;
          } else {
            if(!IsValid(now->right)) {
              now->right=new NodeType;
              now->right->parent=now;
              now->right->wTree=RightBranch;
              iflag=true;
            }
            now=now->right;
          }
          if(iflag) {
            if(KeyRefFlag)  refer(now->key,key);
            else  { imprint(now->key,key); copy(now->key,key); }
            if(ValueRefFlag)  refer(now->value,value);
            else  { imprint(now->value,value); copy(now->value,value); }
            break;
          }
        }
      }

      const NodeType* _get(const KeyType& key) const {
        assert(IsValid(key));
        NodeType* now;
        now=root;
        int cmp;
        while(IsValid(now)) {
          cmp=compare(key,now->key);
          if(cmp==0)  break;
          else if(cmp<0)  now=now->left;
          else            now=now->right;
        }
        return now;
      }

      const ValueType* get(const KeyType& key) const {
        NodeType* p=_get(key);
        return IsValid(p)?p->value.ptr:NULL;
      }

      void _remove(const NodeType* const& pnode) {
        if(!IsValid(pnode))  return;
        NodeType* now;
        now=const_cast<NodeType* const&>(pnode);
        assert(IsValid(*now)&&(pnode==_get(now->key())));
        if(!IsValid(now->left)) {
          if(IsValid(now->parent)) {
            if(now->wTree==LeftBranch)        now->parent->left=now->right;
            else if(now->wTree==RightBranch)  now->parent->right=now->right;
            else Error("Improper Branch Flag for node!");
          } else root=now->right;
          now->right=NULL;
        } else if(!IsValid(now->right)) {
          if(IsValid(now->parent)) {
            if(now->wTree==LeftBranch)        now->parent->left=now->left;
            else if(now->wTree==RightBranch)  now->parent->right=now->left;
            else Error("Improper Branch Flag for node!");
          } else root=now->left;
          now->left=NULL;
        } else {
          NodeType* mvNode;
          mvNode=now->right;
          while(IsValid(mvNode->left))  mvNode=mvNode->left;
          if(mvNode->wTree==LeftBranch)
            mvNode->parent->left=mvNode->right;
          else if(mvNode->wTree==RightBranch)
            mvNode->parent->right=mvNode->right;
          else Error("Improper Branch Flag for node!");
          if(IsValid(mvNode->right)) {
            mvNode->right->parent=mvNode->parent;
            mvNode->right->wTree=mvNode->wTree;
          }
          mvNode->right=NULL;
          mvNode->parent=now->parent;
          mvNode->wTree=now->wTree;
          mvNode->left=now->left;
          mvNode->right=now->right;
          mvNode->left->parent=mvNode;
          mvNode->right->parent=mvNode;
          if(IsValid(mvNode->parent)) {
            if(mvNode->wTree==LeftBranch)
              mvNode->parent->left=mvNode;
            else if(mvNode->wTree==RightBranch)
              mvNode->parent->right=mvNode;
            else Error("Improper Branch Flag for node!");
          } else root=mvNode;
        }
        delete_pointer(now);
      }

      void remove(const KeyType& key) { _remove(_get(key)); }

    private:

      BTree(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename KT, typename VT>
  bool IsValid(const BTree<KT,VT>& B) { return B.isvalid(); }

  template <typename KT, typename VT>
  void release(BTree<KT,VT>& B) { B.clearData(); }

}

#endif

