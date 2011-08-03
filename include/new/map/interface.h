
#ifndef _Map_Interface_H_
#define _Map_Interface_H_

#include "map/element/allocate.h"
#include "map/element/copy.h"
#include "chain/node/allocate.h"
#include "chain/node/copy.h"
#include "map/hash/compare.h"
#include "chain/interface.h"
#include "binary-tree/interface.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct Map {

    public:

      typedef Map<KeyType,ValueType>    Type;
      typedef MapElement<KeyType,ValueType>   ElementType;
      typedef ChainNode<ElementType>    CNodeType;

      Chain<ElementType>  data;
      BTree<HashTable<3>,CNodeType> mesh[0xFFFF];

      Map() : data(), mesh() {}
      ~Map() { clearData(); }

      void clearData() {
        for(unsigned int i=0;i<0xFFFF;++i)  release(mesh[i]);
        release(data);
      }
      bool isvalid() const { return IsValid(data); }

      void update() {
        for(unsigned int i=0;i<0xFFFF;++i)  release(mesh[i]);
        unsigned int n;
        CNodeType* pcnode;
        pcnode=data.root->child;
        while(pcnode!=data.head) {
          pcnode->content().update();
          n=(pcnode->content().hash[0]&0xFFFF0000)>>16;
          mesh[n].insert(pcnode->content().hash,*pcnode);
          pcnode=pcnode->child;
        }
      }
      const ValueType* _find(const ElementType& E) {
        unsigned int n=(E.hash[0]&0xFFFF0000)>>16;
        CNodeType* pcnode=mesh[n].get(E.hash);
        return pcnode==NULL?NULL:pcnode->content().value.ptr;
      }
      const ValueType* find(const KeyType& key) {
        HashTable<3> hash;
        allocate(hash);
        hash.create(key);
        unsigned int n=(hash[0]&0xFFFF0000)>>16;
        const CNodeType* pcnode=mesh[n].get(hash);
        release(hash);
        return pcnode==NULL?NULL:pcnode->content().value.ptr;
      }
      bool IsHaveKey(const KeyType& key) { return find(key)!=NULL; }

      void _add(const ElementType& E, const bool& ElemRefFlag=true) {
        assert(!IsHaveKey(E.key()));
        data.append(E,ElemRefFlag);
        CNodeType* nownode;
        nownode=data.head->parent;
        ElementType* now;
        now=nownode->content.ptr;
        now->update();
        unsigned int n=(now->hash[0]&0xFFFF0000)>>16;
        mesh[n].insert(now->hash,*nownode);
      }
      void add(const KeyType& key, const ValueType& value,
               const bool& kRefFlag=true, const bool& vRefFlag=true) {
        assert(!IsHaveKey(key));
        data._append();
        CNodeType* now;
        now=data.head->parent;
        allocate(now->content);
        ElementType* nowelem;
        nowelem=now->content.ptr;
        if(kRefFlag)  refer(nowelem->key,key);
        else { imprint(nowelem->key,key); copy(nowelem->key,key); }
        if(vRefFlag)  refer(nowelem->value,value);
        else { imprint(nowelem->value,value); copy(nowelem->value,value); }
        allocate(nowelem->hash);
        nowelem->update();
        unsigned int n=(nowelem->hash[0]&0xFFFF0000)>>16;
        mesh[n].insert(nowelem->hash,*now);
      }

      void remove(const KeyType& key) {
        HashTable<3> thash;
        allocate(thash);
        thash.create(key);
        unsigned int n=(thash[0]&0xFFFF0000)>>16;
        const BTreeNode<HashTable<3>,CNodeType>* pnode=mesh[n]._get(thash);
        CNodeType* pcnode=(pnode==NULL?NULL:pnode->value.ptr);
        mesh[n]._remove(pnode);
        if(pcnode!=NULL)  data._remove(pcnode);
      }

    private:

      Map(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename KT, typename VT>
  bool IsValid(const Map<KT,VT>& M) { return M.isvalid(); }

  template <typename KT, typename VT>
  void release(Map<KT,VT>& M) { M.clearData(); }

}

#endif

