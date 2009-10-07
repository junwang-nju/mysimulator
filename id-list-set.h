
#ifndef _ID_List_Set_H_
#define _ID_List_Set_H_

#include "id-list.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class IDListSet : public varVector<IDList<DistEvalObj,GeomType> > {

    public:

      typedef IDListSet<DistEvalObj,GeomType>             Type;

      typedef varVector<IDList<DistEvalObj,GeomType> >    ParentType;

      IDListSet() : ParentType() {}

      IDListSet(const Type& IDLS) {
        myError("copier for id list set is disabled!");
      }

      Type& operator=(const Type& IDLS) {
        static_cast<ParentType*>(this)->operator=(IDLS);
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& operator=(const IDListSet<runDistEvalObj,runGeomType>& IDLS) {
        static_cast<ParentType*>(this)->operator=(IDLS);
        return *this;
      }

  };

}

#endif

