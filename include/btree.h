
#ifndef _Binary_Tree_H_
#define _Binary_Tree_H_

#include "btree-node.h"
#include "memory.h"

namespace std {

  template <typename KeyType, typename ValueType>
  class BTree {

    public:

      typedef BTree<KeyType,ValueType>  Type;

      typedef BTreeNode<KeyType,ValueType>  NodeType;

    protected:

      NodeType *pRoot;

    private:

      void copy(NodeType*& present, const NodeType* bpresent,
                const NodeType* pparent, const int pflag) {
        if(bpresent!=NULL)
          present=new NodeType(bpresent->ptr2key(),bpresent->ptr2value(),
                               pparent,pflag,NULL,NULL,true);
        NodeType* pcnode;
        pcnode=const_cast<NodeType*>(present->left());
        if(bpresent->left()!=NULL)
          copy(pcnode,bpresent->left(),present,-1);
        pcnode=const_cast<NodeType*>(present->right());
        if(bpresent->right()!=NULL)
          copy(pcnode,bpresent->right(),present,1);
      }

    public:

      BTree() : pRoot(NULL) {}

      BTree(const Type& bt) { myError("Cannot create from binary tree"); }

      ~BTree() { clear(); }

      Type& operator=(const Type& BT) {
        clear();
        copy(pRoot,BT.pRoot,NULL,0);
        return *this;
      }

      const NodeType* ptrRoot() const { return pRoot; }

      void clear() {
        NodeType *present=pRoot, *tofree;
        while(present!=NULL) {
          if(present->left()!=NULL)
            present=const_cast<NodeType*>(present->left());
          else if(present->right()!=NULL)
            present=const_cast<NodeType*>(present->right());
          else {
            tofree=present;
            present=const_cast<NodeType*>(present->parent());
            remove(tofree);
          }
        }
      }

      void insert(const KeyType& K, const ValueType& V) {
        NodeType *present=pRoot;
        int cmp;
        while(present!=NULL) {
          cmp=compare(K,*(present->ptr2key()));
          if(cmp==0) {
            present->ptr2value()=const_cast<ValueType*>(&V);
            return;
          } else if(cmp<0)  {
            if(present->left()!=NULL)
              present=const_cast<NodeType*>(present->left());
            else {
              present->SetLeft(new NodeType(&K,&V,present,-1,NULL,NULL,true));
              return;
            }
          } else  {
            if(present->right()!=NULL)
              present=const_cast<NodeType*>(present->right());
            else {
              present->SetRight(new NodeType(&K,&V,present,1,NULL,NULL,true));
              return;
            }
          }
        }
        pRoot=new NodeType(&K,&V,NULL,0,NULL,NULL,true);
      }

      void insert(NodeType& nd) {
        NodeType *present=pRoot;
        int cmp,pflag=0;
        while(present!=NULL) {
          cmp=compare(*(nd.ptr2key()),*(present->ptr2key()));
          if(cmp==0) {
            myError("Conflict in the inserted Key");
            return;
          } else if(cmp<0)  {
            if(present->left()!=NULL)
              present=const_cast<NodeType*>(present->left());
            else {
              present->SetLeft(&nd);
              nd.SetParent(present,-1);
              return;
            }
          } else  {
            if(present->right()!=NULL)
              present=const_cast<NodeType*>(present->right());
            else {
              present->SetRight(&nd);
              nd.SetParent(present,1);
              return;
            }
          }
        }
        pRoot=&nd;
      }

      const ValueType* get(const KeyType& K) const {
        NodeType *present=pRoot;
        int cmp;
        while(present!=NULL) {
          cmp=compare(K,*(present->ptr2key()));
          if(cmp==0)  return  present->ptr2value();
          else if(cmp<0)  present=const_cast<NodeType*>(present->left());
          else            present=const_cast<NodeType*>(present->right());
        }
        return NULL;
      }

      const NodeType* getNode(const KeyType& K) const {
        NodeType *present=pRoot;
        int cmp;
        while(present!=NULL) {
          cmp=compare(K,*(present->ptr2key()));
          if(cmp==0)      break;
          else if(cmp<0)  present=const_cast<NodeType*>(present->left());
          else            present=const_cast<NodeType*>(present->right());
        }
        return present;
      }

      void remove(NodeType*& pnd) {
        if(pnd==NULL) return;
        NodeType *parent=const_cast<NodeType*>(pnd->parent());
        NodeType *left=const_cast<NodeType*>(pnd->left());
        NodeType *right=const_cast<NodeType*>(pnd->right());
        int pflag=pnd->WhereParentFrom();
        if(left==NULL) {
          if(pflag==0)      pRoot=right;
          else if(pflag==1) parent->SetRight(right);
          else              parent->SetLeft(right);
          if(right!=NULL)   right->SetParent(parent,pflag);
        } else if(right==NULL) {
          if(pflag==0)      pRoot=left;
          else if(pflag==1) parent->SetRight(left);
          else              parent->SetLeft(left);
          left->SetParent(parent,pflag);
        } else {
          NodeType *rnd=right;
          while(rnd->left()!=NULL)
            rnd=const_cast<NodeType*>(rnd->left());
          if(rnd->WhereParentFrom()==1)
            const_cast<NodeType*>(rnd->parent())->SetRight(rnd->right());
          else
            const_cast<NodeType*>(rnd->parent())->SetLeft(rnd->right());
          if(rnd->right()!=NULL)
            const_cast<NodeType*>(rnd->right())->SetParent(
                rnd->parent(),rnd->WhereParentFrom());
          rnd->SetParent(parent,pflag);
          rnd->SetLeft(left);
          rnd->SetRight(right);
        }
        if(pnd->IsAllocByTree()) safe_delete(pnd);
      }

  };
}

#endif

