
/**
 * @file param-list.h
 * @brief the list structure containing the parameters
 *
 * All the parameters are stored inside a list. Each item in list is stored as
 * a vector of double parameters. A vector of hash indices (actually three) is
 * used as the flags of the item in parameter list. The whole list is arranged
 * with the combination of binary tree and hash table to enable efficient
 * searches. Each parameter could be obtained based on the monomer indices
 * and interaction type. This file gives the basic interface to read items.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 * @todo the method to systematically input parameters should be created.
 */

#ifndef _Parameter_List_H_
#define _Parameter_List_H_

#include "var-vector.h"
#include "fix-vector.h"
#include "vector-op.h"
#include "btree.h"
#include "hash-func.h"

namespace std {

  /**
   * @brief the class containing the key to search parameters
   *
   * This class includes the indices to locate an item of parameter.
   * These indices may contain the indices of the related units and
   * the interaction type. An internal hash index is also included.
   * This hash index is used to search parameter internally. The
   * method to generate hash is also included.
   *
   * @note the hash functions are not systematically tested.
   */
  class ParamKey {

    public:

      /**
       * @brief the indices to refer to the parameters
       *
       * These \c unsigned \c int type indices are used as entrances
       * to locate the parameter items in the whole list. They generally
       * include the indices of the related units and the interaction
       * types.
       * @note The interaction type is necessary since the same group
       *       of units may relate to different kinds of interactions.
       */
      varVector<uint> Index;

      /**
       * @brief the hash index as an internal interface to access parameter
       *
       * Three hash indeices are used. It is said that three is enough for
       * rather large database. For our present problem, three would
       * probably be OK.
       *
       * @note the efficiency of these hash functions are not tested.
       */
      fixVector<uint,3> hash;

      /**
       * @brief build up the hash index
       *
       * The internal hash indices are generated based on three kinds of
       * hash functions. These functions use the array as input.
       */
      void BuildHash() {
        uint size=Index.size()*4;
        hash[0]=hash_ap(reinterpret_cast<char*>(Index.data()),size);
        hash[1]=hash_dek(reinterpret_cast<char*>(Index.data()),size);
        hash[2]=hash_bp(reinterpret_cast<char*>(Index.data()),size);
      }

  };

  /**
   * @brief input the key for parameter from istream
   *
   * Just import the indices and update the hash.
   *
   * @param [in,out] is
   *        The input istream.
   *
   * @param [out] K
   *        The key for parameter list
   *
   * @return the istream after input.
   */ 
  istream& operator>>(istream& is, ParamKey& K) {
    is>>K.Index;
    K.BuildHash();
    return is;
  }

  /**
   * @brief compare two keys for parameter list
   *
   * Two keys for parameter lists are compared based on the hash index.
   * The indices of the hash are compared correspondingly. An order could
   * be defined.
   *
   * @param [in] K1
   *        One key for parameter list
   *
   * @param [in] K2
   *        Another key for parameter list
   *
   * @return 1 indicating K1 is ahead of K2, or -1 indicating K1 is later
   *         after K2, or 0 when they are equal.
   */
  int compare(const ParamKey& K1, const ParamKey& K2) {
    if(K1.hash[0]==K2.hash[0])
      if(K1.hash[1]==K2.hash[1])
        if(K1.hash[2]==K2.hash[2])      return 0;
        else                            return (K1.hash[2]>K2.hash[2]?1:-1);
      else                              return (K1.hash[1]>K2.hash[1]?1:-1);
    else                                return (K1.hash[0]>K2.hash[0]?1:-1);
  }

  /**
   * @brief list of parameter
   *
   * This class defines a list of parameters. This list is a series of
   * maps between keys and parameters. This is similar as the set in STL.
   * Different from the set in STL, binary tree and hash table are combined
   * internally. This kind of implementation is used for efficiency.
   */
  class ParamList {

    public:

      /**
       * @brief alias for key of parameter
       */
      typedef ParamKey                            ParamKeyType;

      /**
       * @brief alias for the values of parameter
       *
       * It is implemented as vector of \c double type value as parameter.
       */
      typedef varVector<double>                   ParamValueType;

      /**
       * @brief alias for the map structure between key and values
       *
       * It is implemented with btree structure.
       */
      typedef btree<ParamKeyType,ParamValueType>  NodeType;

      /**
       * @brief the list of keys for parameter
       */
      varVector<ParamKeyType>   KeyList;

      /**
       * @brief the list of values for parameter
       */
      varVector<ParamValueType> ValueList;

      /**
       * @brief the hash table of binary tree as structure
       */
      fixVector<NodeType,0xFFFF> HashTree;

      /**
       * @brief default initiator
       *
       * Just initiate the lists of keys, of values, and the hash tree
       * with null parameter.
       */
      ParamList() : KeyList(), ValueList(), HashTree() {}

      /**
       * @brief allocate the internal storage
       *
       * The lists of keys and of values are allocated based on the
       * input size.
       *
       * @param [in] N
       *        The expected number of items
       *
       * @return The reference to the present object
       */
      ParamList& allocate(const uint& N) {
        KeyList.allocate(N);
        ValueList.allocate(N);
        return *this;
      }

      /**
       * @brief update the hash tree
       *
       * build up the hash tree based on the corresponding hash
       * index. The key and value are inserted into certain
       * item of hash tree.
       */
      void UpdateHashTree() {
        assert(KeyList.size()==ValueList.size());
        uint n=KeyList.size();
        for(uint i=0;i<n;++i)
          HashTree[(KeyList[i].hash[0]&0xFFFF0000)>>16].insert(
              KeyList[i],ValueList[i]);
      }

      /**
       * @brief read the values corresponding to the input indices
       *
       * Based on the input index, a hash index is created. Based on this
       * hash index, the item in the hash tree is read and output. This
       * function is defined as const to enable the calling from const
       * object.
       *
       * @param [in] Index
       *        the vector of index
       *
       * @return the pointer to the expected object of values
       */
      const ParamValueType* get(const VectorBase<uint>& Index) const {
        ParamKey tKey;
        tKey.Index.Duplicate(Index);
        tKey.BuildHash();
        return HashTree[(tKey.hash[0]&0xFFFF0000)>>16].get(tKey);
      }

  };

  /**
   * @brief input the list of parameter from istream
   *
   * Firstly, read the size of list, and then read the keys and values,
   * and then establish the whole list.
   *
   * @param [in,out] is
   *        The input istream
   *
   * @param [out] PL
   *        The list of parameter to accept input
   *
   * @return the istream after input.
   */
  istream& operator>>(istream& is, ParamList& PL) {
    uint n;
    is>>n;
    PL.allocate(n);
    for(uint i=0;i<n;++i)   is>>PL.KeyList[i]>>PL.ValueList[i];
    PL.UpdateHashTree();
    return is;
  }

}

#endif

