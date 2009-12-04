
#ifndef _ID_List_H_
#define _ID_List_H_

#include "interaction-type.h"
#include "interaction.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  class IDList {

    public:

      uint interactionTag;

      void (*efunc)(const VectorBase<Property*>&, const ParamList&,
                    DistEvalObj&, const GeomType&,double&);

      void (*gfunc)(VectorBase<Property*>&, const ParamList&,
                    DistEvalObj&, const GeomType&);

      void (*bfunc)(VectorBase<Property*>&, const ParamList&,
                    DistEvalObj&, const GeomType&, double&);

      varVector<varVector<uint> > List;
      
      varVector<Property*> runProperty;

      typedef IDList<DistEvalObj,GeomType>    Type;

      IDList()
        : interactionTag(0), efunc(NULL), gfunc(NULL), bfunc(NULL),
          List(), runProperty() {
      }

      IDList(const Type& IDL) { myError("copier for IDList is disabled!"); }

      Type& operator=(const Type& IDL) {
        interactionTag=IDL.interactionTag;
        efunc=IDL.efunc;
        gfunc=IDL.gfunc;
        bfunc=IDL.bfunc;
        List=IDL.List;
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& operator=(const IDList<runDistEvalObj,runGeomType>& IDL) {
        interactionTag=IDL.interactionTag;
        efunc=IDL.efunc;
        gfunc=IDL.gfunc;
        bfunc=IDL.bfunc;
        List=IDL.List;
        return *this;
      }

      Type& allocate(const uint& NL, const uint& NID) {
        List.allocate(NL);
        for(uint i=0;i<NL;++i)  List[i].allocate(NID);
        runProperty.allocate(NID);
        return *this;
      }

      template <typename runDistEvalObj, typename runGeomType>
      Type& allocate(const IDList<runDistEvalObj,runGeomType>& IDL) {
        uint nl=IDL.List.size();
        uint nid=IDL.List[0].size();
        return allocate(nl,nid);
      }

      void set_interaction(const uint& iTag) {
        interactionTag=iTag;
        switch(iTag) {
          case ParticleParticle_Harmonic:
            efunc=E_ParPar_Harmonic;
            gfunc=G_ParPar_Harmonic;
            bfunc=EG_ParPar_Harmonic;
            break;
          case ParticleParticle_LJ1012:
            efunc=E_ParPar_LJ1012;
            gfunc=G_ParPar_LJ1012;
            bfunc=EG_ParPar_LJ1012;
            break;
          case ParticleParticle_LJ612:
            efunc=E_ParPar_LJ612;
            gfunc=G_ParPar_LJ612;
            bfunc=EG_ParPar_LJ612;
            break;
          case ParticleParticle_LJ612Cut:
            efunc=E_ParPar_LJ612Cut;
            gfunc=G_ParPar_LJ612Cut;
            bfunc=EG_ParPar_LJ612Cut;
            break;
          default:
            myError("Unknown Interaction Type!");
        };
      }

  };

}

#endif

