
#ifndef _Parameter_List_H_
#define _Parameter_List_H_

#include "parameter-key.h"
#include "unique-parameter.h"
#include "vector.h"
#include "btree.h"

namespace std {

  struct ParameterList;

  void assign(ParameterList&,const ParameterList&);
  void release(ParameterList&);

  struct ParameterList {

    typedef ParameterList Type;
    typedef BTree<ParameterKey,Vector<UniqueParameter> > BTreeType;

    struct HashTreeType { BTreeType hash[0xFFFFU]; };

    ParameterKey *key;
    Vector<UniqueParameter> *value;
    unsigned int size;
    HashTreeType *tree;
    unsigned int state;

    ParameterList()
      : key(NULL), value(NULL), size(NULL), tree(NULL), state(Unused) {}
    ParameterList(const Type&){ myError("Cannot create from Parameter List"); }
    Type& operator=(const Type& PL) { assign(*this,PL); return *this; }
    ~ParameterList() { release(*this); }

    BTreeType& operator[](const unsigned int I) { return (*tree).hash[I]; }
    const BTreeType& operator[](const unsigned int I) const {
      return (*tree).hash[I];
    }

  };

  bool IsAvailable(const ParameterList& PL) { return IsAvailable(PL.tree); }

  void updatetree(ParameterList& PL) {
    assert(IsAvailable(PL));
    for(unsigned int i=0;i<0xFFFFU;++i) release(PL[i]);
    for(unsigned int i=0;i<PL.size;++i)
      insert(PL[(PL.key[i].hash[0]&0xFFFF0000U)>>16],PL.key[i],PL.value[i]);
  }

  void assign(ParameterList& dest, const ParameterList& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    for(unsigned int i=0;i<n;++i) {
      dest.key[i]=src.key[i];
      dest.value[i]=src.value[i];
    }
    updatetree(dest);
  }

  void release(ParameterList& PL) {
    if(IsAvailable(PL)) {
      if(PL.state==Reference) {
        PL.key=NULL;
        PL.value=NULL;
        PL.tree=NULL;
      } else if(PL.state==Allocated) {
        for(unsigned int i=0;i<0xFFFFU;++i) release(PL[i]);
        safe_delete(PL.tree);
        safe_delete_array(PL.key);
        safe_delete_array(PL.value);
      }
    }
    PL.size=0;
    PL.state=Unused;
  }

  void allocate(ParameterList& PL,
                const unsigned int ksize, const unsigned int vsize,
                const unsigned int nitem) {
    PL.key=new ParameterKey[nitem];
    PL.value=new Vector<UniqueParameter>[nitem];
    PL.size=nitem;
    for(unsigned int i=0;i<nitem;++i) {
      allocate(PL.key[i],ksize);
      allocate(PL.value[i],vsize);
    }
    PL.tree=new ParameterList::HashTreeType;
    PL.state=Allocated;
  }

  void allocate(ParameterList& PL,
                const unsigned int *ksize, const unsigned int vsize,
                const unsigned int nitem,
                const unsigned int koff=uZero, const unsigned int kstep=uOne) {
    PL.key=new ParameterKey[nitem];
    PL.value=new Vector<UniqueParameter>[nitem];
    PL.size=nitem;
    unsigned int *pks=const_cast<unsigned int*>(ksize)+koff;
    for(unsigned int i=0;i<nitem;++i,pks+=kstep) {
      allocate(PL.key[i],*pks);
      allocate(PL.value[i],vsize);
    }
    PL.tree=new ParameterList::HashTreeType;
    PL.state=Allocated;
  }

  void allocate(ParameterList& PL,
                const unsigned int ksize, const unsigned int *vsize,
                const unsigned int nitem,
                const unsigned int voff=uZero, const unsigned int vstep=uOne) {
    PL.key=new ParameterKey[nitem];
    PL.value=new Vector<UniqueParameter>[nitem];
    PL.size=nitem;
    unsigned int *pvs=const_cast<unsigned int*>(vsize)+voff;
    for(unsigned int i=0;i<nitem;++i,pvs+=vstep) {
      allocate(PL.key[i],ksize);
      allocate(PL.value[i],*pvs);
    }
    PL.tree=new ParameterList::HashTreeType;
    PL.state=Allocated;
  }

  void allocate(ParameterList& PL,
                const unsigned int *ksize, const unsigned int *vsize,
                const unsigned int nitem,
                const unsigned int koff=uZero, const unsigned int kstep=uOne,
                const unsigned int voff=uZero, const unsigned int vstep=uOne) {
    PL.key=new ParameterKey[nitem];
    PL.value=new Vector<UniqueParameter>[nitem];
    PL.size=nitem;
    unsigned int *pks=const_cast<unsigned int*>(ksize)+koff;
    unsigned int *pvs=const_cast<unsigned int*>(vsize)+voff;
    for(unsigned int i=0;i<nitem;++i,pks+=kstep,pvs+=vstep) {
      allocate(PL.key[i],*pks);
      allocate(PL.value[i],*pvs);
    }
    PL.tree=new ParameterList::HashTreeType;
    PL.state=Allocated;
  }

}

#endif

