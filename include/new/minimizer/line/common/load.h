
#ifndef _Minimizer_Line_Common_Load_H_
#define _Minimizer_Line_Common_Load_H_

#include "minimizer/line/common/interface.h"
#include "minimizer/base/load.h"
#include "minimizer/system-propagate-method-mapping.h"
#include "array/1d/refer.h"
#include "system/propagate/minimizer/line/regular/parameter-name.h"
#include "system/propagate/allocate.h"
#include "system/content/data/eg/allocate.h"
#include "system/content/with-egv/refer.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _create_minimizer(LineMinimizerCommon<T,IDT,PT,GT,VT,SCT>& M) {
    allocate(M.MemSys);
    allocate(M.RunSys);
    allocate(M.MemSys().Content);
    allocate(M.RunSys().Content);
    imprint(M.MemSys().Content().X,M.Sys().Content().X);
    allocate(M.MemSys().Content().EGData,M.Sys().Content().X);
    imprint(M.RunSys().Content().X,M.Sys().Content().X);
    allocate(M.RunSys().Content().EGData,M.Sys().Content().X);
    imprint(M.LineDirc,M.Sys().Content().X);
    refer(M.MemSys().Content().Velocity,M.LineDirc);
    refer(M.RunSys().Content().Velocity,M.LineDirc);
    allocate(M.MemSys().Interactions,M.Sys().Interactions.size);
    for(unsigned int i=0;i<M.Sys().Interactions.size;++i) {
      refer(M.MemSys().Interactions[i].Func,M.Sys().Interactions[i].Func);
      if(M.MemSys().Interactions[i].Func.size==1)
        SetWorkFunc(M.MemSys().Interactions[i],SingleInteraction);
      else
        SetWorkFunc(M.MemSys().Interactions[i],ArrayInteraction);
      refer(M.MemSys().Interactions[i].ID,M.Sys().Interactions[i].ID);
      refer(M.MemSys().Interactions[i].Param,M.Sys().Interactions[i].Param);
      refer(M.MemSys().Interactions[i].Geom,M.Sys().Interactions[i].Geom);
      allocate(M.MemSys().Interactions[i].EGData);
      allocate(M.MemSys().Interactions[i].EGData(),M.Sys().Content().X);
    }
    allocate(M.RunSys().Interactions,M.Sys().Interactions.size);
    for(unsigned int i=0;i<M.Sys().Interactions.size;++i) {
      refer(M.RunSys().Interactions[i].Func,M.Sys().Interactions[i].Func);
      if(M.RunSys().Interactions[i].Func.size==1)
        SetWorkFunc(M.RunSys().Interactions[i],SingleInteraction);
      else
        SetWorkFunc(M.RunSys().Interactions[i],ArrayInteraction);
      refer(M.RunSys().Interactions[i].ID,M.Sys().Interactions[i].ID);
      refer(M.RunSys().Interactions[i].Param,M.Sys().Interactions[i].Param);
      refer(M.RunSys().Interactions[i].Geom,M.Sys().Interactions[i].Geom);
      allocate(M.RunSys().Interactions[i].EGData);
      allocate(M.RunSys().Interactions[i].EGData(),M.Sys().Content().X);
    }
    allocate(M.MemSys().Propagates,M.Sys().Propagates.size);
    allocate(M.RunSys().Propagates,M.Sys().Propagates.size);
    for(unsigned int i=0;i<M.Sys().Propagates.size;++i) {
      SystemPropagateMethodName SPN;
      SPN=MinimizerSysPropagateMethodMapping(M.Sys().Propagates[i].Method);
      allocate(M.MemSys().Propagates[i],SPN);
      allocate(M.RunSys().Propagates[i],SPN);
      refer(M.MemSys().Propagates[i].MerIDRange,
            M.Sys().Propagates[i].MerIDRange);
      refer(M.RunSys().Propagates[i].MerIDRange,
            M.Sys().Propagates[i].MerIDRange);
      unsigned int n=M.Sys().Propagates[i].MerIDRange.size;
      allocate(M.MemSys().Propagates[i].grpContent,n);
      allocate(M.RunSys().Propagates[i].grpContent,n);
      M.MemSys().Propagates[i].buildGroupContent(M.MemSys().Content());
      M.RunSys().Propagates[i].buildGroupContent(M.RunSys().Content());
      void* pStep=reinterpret_cast<void*>(&(M.Step));
      switch(SPN) {
        case SysFixPosition:
          break;
        case SysMinimizerLineRegular:
          M.MemSys().Propagates[i].Param[MinLineRegularStep].ptr[0]=pStep;
          M.RunSys().Propagates[i].Param[MinLineRegularStep].ptr[0]=pStep;
          break;
        default:
          Error("This Grouping Method Cannot be processed!");
      }
    }
    M.MemSys().build();
    M.RunSys().build();
    M.MemSys().init();
    M.RunSys().init();
  }

}

#define _Load_Min \
  assert(IsValid(S));\
  release(M);\
  typedef typename LineMinimizerCommon<T,IDT,PT,GT,VT,SCT>::ParentType Type;\
  load(static_cast<Type&>(M),S);\
  _create_minimizer(M);

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void load(LineMinimizerCommon<T,IDT,PT,GT,VT,SCT>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) { _Load_Min }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void load(LineMinimizerCommon<T,IDT,PT,GT,VT,SCT>& M,
            Object<System<T,IDT,PT,GT,VT,SCT> >& S) { _Load_Min }

}

#undef _Load_Min

#endif

