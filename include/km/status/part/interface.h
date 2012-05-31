
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
   * This is a child class of UsedStatus. One more counter is introduce to
   * record the number of references to part of storage. This is a special
   * use of storage since we cannot get the information of storage from child
   * information. Therefore, this object is implemented after the UsedStatus
   * class.
   */
  class PartUsedStatus : public UsedStatus {

    public:

      typedef PartUsedStatus  Type;
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
      void Init() { ParentType::Init(); _pcount=0; }
      void IncPart() { Inc(); _pcount++; }
      void DecPart() { Dec(); _pcount--; }

    protected:

      /** @brief the number of partial use */
      unsigned int _pcount;

    private:

      /** @brief disabled Copy Initiator */
      PartUsedStatus(const Type&) {}
      /** @brief disabled Copy Operator */
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PartUsedStatus& S) {
    typedef PartUsedStatus::ParentType  PType;
    Clear(static_cast<PType&>(S));
    S._pcount=0;
  }

}

#endif

