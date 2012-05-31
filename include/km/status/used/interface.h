
/**
 * @file status/used/interface.h
 * @brief Object of access state, for case that whole content is used
 *
 * When a storage is used (referred) as by other objects, namely another
 * entrance point to this storage ior part of it is provided, this status
 * records the how many accesses are there. This is used as part of memory
 * management and GC mechanism.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Status_Used_Interface_H_
#define _Status_Used_Interface_H_

#include <cassert>

namespace mysimulator {

  /**
   * @class UsedStatus
   * @brief Object recording access to storage
   *
   * a count is used to record the number of access to certain storage. The
   * access could be the whole storage or part of it. the later one is coded
   * with another class PartUsedStatus.
   */
  class UsedStatus {

    public:

      /** @brief normalized name of this class */
      typedef UsedStatus  Type;

      friend void Clear(Type&);

      /** @brief default initiator
       *
       * Just init the count as zero.
       */
      UsedStatus() : _count(0) {}
      /** @brief destructor with Clear operation */
      ~UsedStatus() { Clear(*this); }

      /** @brief check Validity of this state
       *
       * When the count is not smaller than one, it means there is at least
       * one (primary) access to the storage. zero means that the state is
       * not used.
       *
       * @return true when object is valid (namely count is not smaller than 1)
       */
      bool IsValid() const { return _count>0; }
      /** @brief check if there is only one access to storage
       *
       * When the count is one, only one object access the storage, and there
       * are not reference accesses.
       *
       * @return true when count equals to 1
       */
      bool Only() const { return _count==1; }
      /** @brief init operation
       *
       * just init the count (set as one).
       */
      void Init() { _count=1; }
      /** @brief increment of count
       *
       * just add one to indicate wuth one more reference
       * @note since _count is unsigned int type, an explicit check is
       *       employed with assert.
       */
      void Inc() { assert(_count<0xFFFFFFFFU); ++_count; }
      /** @brief decrement of count
       *
       * just minus one to indicate one reference is released.
       * @note an assert check is employed to check if this operation is valid.
       */
      void Dec() { assert(_count>1); --_count; }

    protected:

      /** @brief the count indicating how many times object points to storage
       *
       * @note Since the storage itself is the intrinsic object pointing to the
       *       storage, the minimum of the count should be 1.
       */
      unsigned int _count;

    private:

      /** @brief disabled copy initiator */
      UsedStatus(const Type&) {}
      /** @brief disable copy operation */
      Type& operator=(const Type&) { return *this; }

  };

  /** @brief clear the content of UsedStatus object
   *
   * just nullify the count, which put the object in a unused state.
   *
   * @param S the UsedStatus object to be cleared
   */
  void Clear(UsedStatus& S) { S._count=0; }

}

#endif

