/**
 * @file parameter-key.h
 * @brief the key structure to define parameter
 *
 * This file defines data structure for keys in define parameter for
 * simulations. This is regularly used to record the unit typpes for
 * parameter access.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Parameter_Key_H_
#define _Parameter_Key_H_

#include "hash-func.h"
#include "storage-state-name.h"
#include "error-proc.h"
#include "vector-impl.h"

namespace std {

  struct ParameterKey;
  bool IsAvailable(const ParameterKey&);
  void assign(ParameterKey&, const ParameterKey&);
  void release(ParameterKey&);

  /**
   * @brief data structure as the key for parameter in simulation
   *
   * This object contains a series of indices, which are generally
   * the type of concerned units. This could uniquely corresponds to
   * specific interactions. To ease search, some temporary data for
   * hash are used.
   */
  struct ParameterKey {

    /**
     * @brief indices corresponding to units
     */
    unsigned int* index;
    /**
     * @brief size of array containing indices
     */
    unsigned int  size;
    /**
     * @brief size for array in hash calculation
     */
    unsigned int  hsize;
    /**
     * @brief array containing hash
     */
    unsigned int  hash[3];
    /**
     * @brief storage state of key object
     */
    unsigned int  state;

    /**
     * @brief abbreviation for ParameterKey type
     */
    typedef ParameterKey  Type;

    /**
     * @brief default initiator
     *
     * Initiate the pointer with NULL and the flags with no information
     */
    ParameterKey() : index(NULL), size(0), hsize(0), state(Unused) {
      hash[0]=hash[1]=hash[2]=0;
    }
    /**
     * @brief initiator from another ParameterKey object
     *
     * it is prohibited and pop up an error message
     *
     * @param K [in] the input ParameterKey object
     */
    ParameterKey(const Type& K){ myError("Cannot create from Parameter Key"); }
    /**
     * @brief copy from another ParameterKey
     *
     * it is implemented with assign operation
     *
     * @param K [in] the input ParameterKey object
     * @return the reference to the resultant ParameterKey object
     */
    Type& operator=(const Type& K) { assign(*this,K); return *this; }
    /**
     * @brief destructor
     *
     * it is implemented with release operation
     */
    ~ParameterKey() { release(*this); }

  };

  /**
   * @brief check if the ParameterKey object is available
   *
   * It is implemented by checking the index in ParameterKey object.
   *
   * @param K [in] the ParameterKey object to be checked
   * @return the availability of the input ParameterKey object
   */
  bool IsAvailable(const ParameterKey& K) { return IsAvailable(K.index); }

  /**
   * @brief build up the hash
   *
   * The hash data is built up according to the internal indices. The
   * indices are converted as array of char. The methods of hash production
   * are presumed.
   *
   * @param K [in,out] the ParameterKey object related to this operation
   * @return nothing
   */
  void buildhash(ParameterKey& K) {
    K.hash[0]=hash_ap(reinterpret_cast<char*>(K.index),K.hsize);
    K.hash[1]=hash_dek(reinterpret_cast<char*>(K.index),K.hsize);
    K.hash[2]=hash_bp(reinterpret_cast<char*>(K.index),K.hsize);
  }

  /**
   * @brief assign ParameterKey object from another
   *
   * This operation assigns the indices at first, and builds up hash
   * in consequence.
   *
   * @param dest [out] the ParameterKey object to accept input
   * @param src [in] the ParameterKey object storing input
   * @return nothing
   */
  void assign(ParameterKey& dest, const ParameterKey& src) {
    assert(IsAvailable(src));
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    assign(dest.index,src.index,n);
    buildhash(dest);
  }

  /**
   * @brief release ParameterKey object
   *
   * release the storage of indices based on its state, and clean up the
   * flags and temporary data.
   *
   * @param K [out] the ParameterKey to be released
   * @return nothing
   */
  void release(ParameterKey& K) {
    if(K.state==Allocated) safe_delete_array(K.index);  else K.index=NULL;
    K.size=0; K.hsize=0;
    K.hash[0]=K.hash[1]=K.hash[2]=0;
    K.state=Unused;
  }

  /**
   * @brief allocate ParameterKey object
   *
   * The index is allocated based on input information, and is assigned
   * as zero. The ParameterKey object is released before this operation
   * to avoid memory leak.
   *
   * @param K [in,out] the ParameterKey object to be allocated
   * @param nidx [in] the number of expected indices
   * @return nothing.
   */
  void allocate(ParameterKey& K, const unsigned int nidx) {
    release(K);
    K.index=new unsigned int[nidx];
    K.size=nidx;
    K.hsize=4*nidx;
    K.state=Allocated;
    assign(K.index,uZero,K.size);
  }

  /**
   * @brief refer to another ParameterKey object
   *
   * Just copy all the pointers and data from source object into the
   * destinate object. The destinate object is released before this operation
   * to avoid memory leak.
   *
   * @param dest [out] the ParameterKey object to accept input
   * @param src [in] the ParameterKey object storing input
   * @return nothing
   */
  void refer(ParameterKey& dest, const ParameterKey& src) {
    release(dest);
    dest.index=src.index;
    dest.state=Reference;
    dest.size=src.size;
    dest.hsize=src.hsize;
    assign(dest.hash,src.hash,3);
  }

  /**
   * @brief read ParameterKey object from istream
   *
   * The indices are read from istream. Then, the has is built up.
   *
   * @param is [in,out] the istream for input
   * @param K [out] the ParameterKey object to accept input data
   * @return the istream after reading
   */
  istream& operator>>(istream& is, ParameterKey& K) {
    assert(IsAvailable(K));
    for(unsigned int i=0;i<K.size;++i) is>>K.index[i];
    buildhash(K);
    return is;
  }

  /**
   * @brief compare two ParameterKey objects
   *
   * The comparison is based on the hash data seqentially. When the first
   * non-equal hash value is found, their comparison result is result
   * of the comparison between two ParameterKey objects. If all the
   * hash values are same, these ParameterKey objects are equal.
   *
   * @param k1,k2 [in] two ParameterKey object to compare
   * @return 0 representing equal, 1 representing k1>k2, and -1 representing
   *         k1<k2.
   */
  int compare(const ParameterKey& k1, const ParameterKey& k2) {
    for(unsigned int i=0;i<3;++i)
      if(k1.hash[i]!=k2.hash[i]) return (k1.hash[i]>k2.hash[i]?1:-1);
    return 0;
  }

}

#endif

