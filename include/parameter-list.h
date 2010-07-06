
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
    /**
     * @brief the storage state of list of parameters
     */
    unsigned int state;

    /**
     * @brief default initiator
     *
     * Just initiate the pointers with NULL, and initiate flags with
     * no information
     */
    ParameterList()
      : key(NULL), value(NULL), size(0), tree(NULL), state(Unused) {}
    /**
     * @brief initiator from another list of parameter
     *
     * It is prohibited and pop up an error message
     *
     * @param PL [in] the input ParameterList object
     */
    ParameterList(const Type& PL){
      myError("Cannot create from Parameter List");
    }
    /**
     * @brief copy from another ParameterList object
     *
     * It is implemented with assign operation
     *
     * @param PL [in] the input ParameterList object
     * @return the reference to the resultant ParameterList object
     */
    Type& operator=(const Type& PL) { assign(*this,PL); return *this; }
    /**
     * @brief destructor
     *
     * It is implemented with release operation
     */
    ~ParameterList() { release(*this); }

    /**
     * @brief access the tree corresponding to hash value I
     *
     * It is a simplification of the way to access the tree corresponding
     * to the hash value I.
     *
     * @param I [in] the input hash value
     * @return the reference to binary tree corrsponding to input hash value
     */
    BTreeType& operator[](const unsigned int I) { return (*tree).hash[I]; }
    /**
     * @brief visit the tree corresponding to the hash value I
     *
     * It is a simplification of the way to visit the tree corresponding
     * to the hash value I.
     *
     * @param I [in] the input hash value
     * @return the const reference to the binary tree corrsponding to
     *         input hash value
     */
    const BTreeType& operator[](const unsigned int I) const {
      return (*tree).hash[I];
    }

  };

  /**
   * @brief check the availability of the list of parameter
   *
   * It is implemented by checking the internal pointer to the tree array
   *
   * @param PL [in] the ParameterList object to be checked
   * @return the availability of the input ParameterList object
   */
  bool IsAvailable(const ParameterList& PL) { return IsAvailable(PL.tree); }

  /**
   * @brief update the tree in ParameterList object
   *
   * At first, the contents of the original tree are released. Then,
   * the internal key-value map are inserted into the tree. The concerned
   * ParameterList object is checked for its availability before this
   * operation.
   */
  void updatetree(ParameterList& PL) {
    assert(IsAvailable(PL));
    for(unsigned int i=0;i<0xFFFFU;++i) release(PL[i]);
    for(unsigned int i=0;i<PL.size;++i)
      insert(PL[(PL.key[i].hash[0]&0xFFFF0000U)>>16],PL.key[i],PL.value[i]);
  }

  /**
   * @brief assign ParameterList object from another
   *
   * It is implemented by copying the keys and values of source object
   * into those in destination object. The number of the concerned
   * keys or values is the minimum of the numbers of keys or values
   * in source and destination objects. Then, the tree in the ParameterList
   * object is updated. The concerned ParameterList objects are
   * checked for their availability before this operation.
   *
   * @param dest [out] the ParameterList object to accept input
   * @param src [in] the ParameterList object storing input
   * @return nothing
   */
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

  /**
   * @brief release the ParameterList object
   *
   * based on the internal storage state, the internal storage in ParameterList
   * object is released. The flags are also updated.
   *
   * @param PL [out] the ParameterList object to be released
   * @return nothing
   */
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

  /**
   * @brief allocate ParameterList object with constant size of key and value
   *
   * The internal key, value and tree are allocated based on the input
   * information. The state are also updated.
   *
   * @param PL [out] the ParameterList object to be allocated
   * @param ksize,vsize [in] the sizes of a key and of a value
   * @param nitem [in] the number of keys and values
   * @return nothing
   */
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

  /**
   * @brief allocate ParameterList object with various size of keys and constant size of values
   *
   * The internal key, value and tree are allocated based on the input
   * information. The state are also updated.
   *
   * @param PL [out] the ParameterList object to be allocated
   * @param ksize [in] the array containing the sizes of keys
   * @param vsize [in] the size of values
   * @param nitem [in] the number of keys and values
   * @param koff [in] the offset for the first element in array ksize.
   *                  It takes a default value of uZero.
   * @param kstep [in] the separation between elements in array ksize.
   *                   It takes a default value of uOne
   * @return nothing
   */
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

  /**
   * @brief allocate ParameterList object with constant size of keys and various size of values
   *
   * The internal key, value and tree are allocated based on the input
   * information. The state are also updated.
   *
   * @param PL [out] the ParameterList object to be allocated
   * @param ksize [in] the size of keys
   * @param vsize [in] the array containing the sizes of values
   * @param nitem [in] the number of keys and values
   * @param voff [in] the offset for the first element in array vsize.
   *                  It takes a default value of uZero.
   * @param vstep [in] the separation between elements in array vsize.
   *                   It takes a default value of uOne
   * @return nothing
   */
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

  /**
   * @brief allocate ParameterList object with various size of keys and values
   *
   * The internal key, value and tree are allocated based on the input
   * information. The state are also updated.
   *
   * @param PL [out] the ParameterList object to be allocated
   * @param ksize [in] the array containing the sizes of keys
   * @param vsize [in] the array containing the sizes of values
   * @param nitem [in] the number of keys and values
   * @param koff, voff [in] the offset for the first element in array ksize
   *                        and vsize. They take default value of uZero.
   * @param kstep, vstep [in] the separation between elements in array ksize
   *                          and vsize. They take default value of uOne
   * @return nothing
   */
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

  /**
   * @brief refer to another ParameterList object
   *
   * Just copy the pointers and flags in source object into
   * those of the destinate object.
   *
   * @param dest [out] the ParameterList object to accept input
   * @param src [in] the ParameterList object storing input
   * @return nothing
   */
  void refer(ParameterList& dest, const ParameterList& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.key=src.key;
    dest.value=src.value;
    dest.size=src.size;
    dest.tree=src.tree;
    dest.state=Reference;
  }

  /**
   * @brief get the pointer of value corresponding to a value
   *
   * A temporary key is generated based on the input indices. The pointer
   * of values based on this key is found out.
   *
   * @param PL [in] the ParameterList object containing the library of
   *                parameters. It uses a reference to ease the get operation
   * @param idx [in] the array containing indices
   * @param nidx [in] the number of indices
   * @param ioff [in] the offset of the first element in the array idx.
   *                  it takes the default value of iZero.
   * @param istep [in] the separation between used elements in array idx.
   *                   it takes the default values of lOne.
   * @return the pointer to the Vector of values corresponding to the input
   *         indices.
   */
  const Vector<UniqueParameter>*
    get(ParameterList& PL, const unsigned int* idx, const unsigned int nidx,
                           const int ioff=iZero, const long istep=lOne) {
    static ParameterKey K;
    allocate(K,nidx);
    assign(K.index,idx,nidx,ioff,istep);
    buildhash(K);
    return get(PL[(K.hash[0]&0xFFFF0000U)>>16],K);
  }

  /**
   * @brief read ParameterList object from istream
   *
   * read the keys and values from istream, and update the tree accordingly.
   *
   * @param is [in,out] the istream to be read
   * @param PL [out] the ParameterList to accept input
   * @return the istream after input
   */
  istream& operator>>(istream& is, ParameterList& PL) {
    assert(IsAvailable(PL));
    for(unsigned int i=0;i<PL.size;++i) is>>PL.key[i]>>PL.value[i];
    updatetree(PL);
    return is;
  }

}

#endif

