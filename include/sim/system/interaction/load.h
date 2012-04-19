
#ifndef _System_Interaction_Load_H_
#define _System_Interaction_Load_H_

#include "system/interaction/interface.h"

#define _Load(PART,PartType) \
  template <typename T,typename IDType,typename ParamType,typename GeomType,\
            typename BufferType,template<typename> class ContentType> \
  void load##PART(\
      SystemInteraction<T,IDType,ParamType,GeomType,BufferType,ContentType>& I,\
      const PartType i#PART) { \
    Imprint(I.PART,i##PART); \
    Copy(I.PART,i##PART); \
  }

#endif

