
#ifndef _Geometry_Contact_Method_Base_H_
#define _Geometry_Contact_Method_Base_H_

#include "geometry/contact/method/model-selector-name.h"
#include "geometry/contact/method/alt-selector-name.h"

namespace mysimulator {

  class ContactMethodBase {

    public:

      typedef ContactMethodBase Type;

    private:

      ModelSelectorName _mdmode;
      AltSelectorName   _altmode;

    public:

      ContactMethodBase() : _mdmode(ModelSelectorName::First),
                            _altmode(AltSelectorName::Default) {}
      ContactMethodBase(const Type& M) : _mdmode(M._mdmode),
                                         _altmode(M._altmode) {}
      ~ContactMethodBase() { reset(); }

      operator bool() const { return true; }
      ModelSelectorName ModelMode() const { return _mdmode; }
      AltSelectorName AltMode() const { return _altmode; }
      void reset() { _mdmode=ModelSelectorName::First;
                     _altmode=AltSelectorName::Default; }

      Type& operator=(const Type& M) {
        _mdmode=M._mdmode;
        _altmode=M._altmode;
        return *this;
      }

      void SetModelMode(ModelSelectorName MSN) { _mdmode=MSN; }
      void SetAltMode(AltSelectorName ASN) { _altmode=ASN; }

  };

}

#endif

