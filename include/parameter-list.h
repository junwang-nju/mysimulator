
/**
 * @file parameter-list.h
 * @brief data structure for list of parameter
 *
 * This file includes the data structure for a list of parameters
 * with a map between keys and values. Some operations to
 * read values based on the keys are also offered. This provides
 * an efficient frame to store and extract key-value maps.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Parameter_List_H_
#define _Parameter_List_H_

#include "parameter-key.h"
#include "unique-parameter.h"
#include "vector.h"
#include "btree.h"

namespace std {

  /**
   * @brief declaration of the type for the list of parameter
   */
  struct ParameterList;

  void assign(ParameterList&,const ParameterList&);
  void release(ParameterList&);

  /**
   * @brief the data structure for list of parameter
   *
   * This contains lists of keys and of values, and the hash-tree structure
   * to search the map relation. The map relation is one-to-one for
   * each index. The hash-tree structure is used to accelerate the search
   * the map for a value based on a key. This is regularly used as
   * the storage of library of prameters.
   */
  struct ParameterList {

    /**
     * @brief abbreviation for the type of the list of parameters
     */
    typedef ParameterList Type;
    /**
     * @brief abbreivation for the binary tree between ParameterKey and Vector object of UniqueParameter
     */
    typedef BTree<ParameterKey,Vector<UniqueParameter> > BTreeType;

    /**
     * @brief internal object for combination of hash and tree structures
     *
     * It contains an array of object of binary tree. Based on hash result,
     * a certain tree could be picked out. In this implementation,
     * the size of array is taken as 0xFFFFU.
     */
    struct HashTreeType { BTreeType hash[0xFFFFU]; };

    /**
     * @brief the pointer to array of ParameterKey
     */
    ParameterKey *key;
    /**
     * @brief Vector object of UniqueParameter as parameter value
     */
    Vector<UniqueParameter> *value;
    /**
     * @brief size of keys or values
     */
    unsigned int size;
    /**
     * @brief the pointer to hash-tree structure
     */
    HashTreeType *tree;
    unsigned int state;

    ParameterList()
      : key(NULL), value(NULL), size(0), tree(NULL), state(Unused) {}
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
        for(unsigned int i=0;i<PL.size;++i) {
          release(PL.key[i]);
          release(PL.value[i]);
        }
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

  void refer(ParameterList& dest, const ParameterList& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.key=src.key;
    dest.value=src.value;
    dest.size=src.size;
    dest.tree=src.tree;
    dest.state=Reference;
  }

  const Vector<UniqueParameter>*
    get(ParameterList& PL, const unsigned int* idx, const unsigned int nidx,
                           const int ioff=iZero, const long istep=lOne) {
    static ParameterKey K;
    allocate(K,nidx);
    assign(K.index,idx,nidx,ioff,istep);
    buildhash(K);
    return get(PL[(K.hash[0]&0xFFFF0000U)>>16],K);
  }

  istream& operator>>(istream& is, ParameterList& PL) {
    assert(IsAvailable(PL));
    for(unsigned int i=0;i<PL.size;++i) is>>PL.key[i]>>PL.value[i];
    updatetree(PL);
    return is;
  }

}

#endif

