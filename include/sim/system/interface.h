
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "system/interaction/interface.h"
#include "array/1d/size.h"
#include "array/2d/release.h"

#ifndef _TemplateType_
#define _TemplateType_ \
  T,IDType,ParamType,GeomType,BufferType,ContentType
#else
#error "Duplicate Definition for _TemplateType_"
#endif

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            typename BufferType,template<typename> class ContentType>
  struct System {

    public:

      typedef System<_TemplateType_>  Type;
      typedef SystemInteraction<_TemplateType_> InteractionType;
      typedef SystemPropagator<T,ContentType>  PropagatorType;
      typedef (*EvoluteFuncType)(
          ContentType<T>&,InteractionType*,PropagatorType*,
          const unsigned int**);

      unsigned int EvoluteMode;
      ContentType<T>        Content;
      InteractionType*      Interactions;
      PropagatorType*       Propagators;
      unsigned int**        GroupMap;
      EvoluteFuncType       EvFunc;

      System() : EvoluteMode(0), Content(), Interactions(NULL),
                 Propagators(NULL), GroupMap(NULL), EvFunc(NULL) {}
      ~System() { clearData(); }

      void clearData() {
        EvFunc=NULL;  release2d(GroupMap); release(Propagators);
        release(Interactions); release(Content);  EvoluteMode=0;
      }
      bool isvalid() const {
        return IsValid(Content)&&(Interactions!=NULL)&&(Propagators!=NULL)&&
               (GroupMap!=NULL)&&(EvFunc!=NULL)&&(EvoluteMode!=0);
      }

      void init() {
        assert(isvalid());
        unsigned int n=size(Propagators);
        for(unsigned int i=0;i<n;++i) Propagators[i].init();
      }
      void evolute() {
        assert(isvalid());
        EvFunc(*Content,Interactions,Propagators,GroupMap);
      }
      void clear() {
        assert(isvalid());
        unsigned int n=size(Propagators);
        for(unsigned int i=0;i<n;++i) Propagators[i].clear();
      }

      void build() {
        // not copied
      }

    private:

      System(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  bool IsValid(const System<T,IDT,PT,GT,BT,DT,CT>& S) { return S.isvalid(); }

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void release(System<T,IDT,PT,GT,BT,DT,CT>& S) { S.clearData(); }

}

#ifdef _TemplateType_
#undef _TemplateType_
#endif

#endif

