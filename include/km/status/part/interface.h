
#ifndef _Status_Part_Interface_H_
#define _Status_Part_Interface_H_

#include "status/used/interface.h"

namespace mysimulator {

  class PartUsedStatus : public UsedStatus {

    public:

      typedef PartUsedStatus  Type;
      typedef UsedStatus      ParentType;
      friend void Clear(PartUsedStatus&);

      PartUsedStatus() : ParentType(), _pcount(0) {}
      ~PartUsedStatus() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid(); }
      bool Only() const {
        return static_cast<const ParentType*>(this)->Only()&&(_pcount==0);
      }
      bool AllPartUse() const { return IsValid()&&(this->_count==_pcount+1); }
      void Init() { static_cast<ParentType*>(this)->Init(); _pcount=0; }
      void IncPart() { Inc(); _pcount++; }
      void DecPart() { Dec(); _pcount--; }

    protected:

      unsigned int _pcount;

    private:

      PartUsedStatus(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PartUsedStatus& S) {
    typedef PartUsedStatus::ParentType  PType;
    Clear(static_cast<PType&>(S));
    S._pcount=0;
  }

}

#endif

