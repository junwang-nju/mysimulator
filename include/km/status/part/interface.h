
/**
 * @file status/part/interface.h
 * @brief Object for access state, for the case that part of content is used
 *
 * When part of a certain storage is used (referred) by other object, this
 * object could be used as the record how many child accesses are there. This
 * is used as part of the memory management and GC mechanism.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Status_Part_Interface_H_
#define _Status_Part_Interface_H_

#include "status/used/interface.h"

namespace mysimulator {

  /**
   * @class PartUsedStatus
   * @brief Object recording partial access to storage
   *
   * This is a child class of UsedStatus. One more counter is introduced to
   * record the number of references to part of storage. This is a special
   * use of storage since we cannot get the information of storage from child
   * information. Therefore, this object is implemented after the UsedStatus
   * class.
   */
  class PartUsedStatus : public UsedStatus {

    public:

      /** @brief normalized name of this class */
      typedef PartUsedStatus  Type;
      /** @brief normalized name of the parent class of this name */
      typedef UsedStatus      ParentType;

      friend void Clear(PartUsedStatus&);

      /** @brief default initiator
       *
       * Just initiate the parent class and the count recording ppartial use.
       */
      PartUsedStatus() : ParentType(), _pcount(0) {}
      /** @brief destructor with Clear operation */
      ~PartUsedStatus() { Clear(*this); }

      /** @brief check Validity to use this Object */
      bool IsValid() const { return ParentType::IsValid(); }
      /** @brief check if the present use is the only use, but not partial use
       *
       * This implementation is consistent with the definition in UsedStatus.
       * The onlu use of storage cannot be partial use.
       */
      bool Only() const { return ParentType::Only()&&(_pcount==0); }
      /** @brief check if all the uses are partial use
       *
       * Considering the original allocated object, the count of use is larger
       * that that for partial use with 1 for the case with all partial use.
       */
      bool AllPartUse() const { return IsValid()&&(this->_count==_pcount+1); }
      /** @brief init operation
       *
       * init parent class and init the local count (set it as zero).
       */
      void Init() { ParentType::Init(); _pcount=0; }
      /** @brief increment of counters
       *
       * increase the counts in parent and local by just add one.
       * @note counts are unsigned int. so they cannot be larger than
       *       the type requirement. boundary is checked with assert.
       */
      void IncPart() { Inc(); assert(_pcount<0xFFFFFFFFU); _pcount++; }
      /** @brief decrement of counts
       *
       * decrease the counts in parent and local by just minus one.
       * @note counts are unsigned int. boundary of count is checked
       * with assert.
       */
      void DecPart() { Dec(); assert(_pcount>=1); _pcount--; }

    protected:

      /** @brief the number of partial use */
      unsigned int _pcount;

    private:

      /** @brief disabled Copy Initiator */
      PartUsedStatus(const Type&) {}
      /** @brief disabled Copy Operator */
      Type& operator=(const Type&) { return *this; }

  };

  /** @brief Clear the contect of PartUsedStatus object
   *
   * Just clear the parent class and reset the local count.
   *
   * @param S the PartUsedStatus object to be cleaned up
   */
  void Clear(PartUsedStatus& S) {
    typedef PartUsedStatus::ParentType  PType;
    Clear(static_cast<PType&>(S));
    S._pcount=0;
  }

}

#endif

