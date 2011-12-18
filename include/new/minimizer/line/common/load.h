
#ifndef _Minimizer_Line_Common_Load_H_
#define _Minimizer_Line_Common_Load_H_

#include "minimizer/line/common/interface.h"
#include "minimizer/base/load.h"
#include "minimizer/system-grouping-method-mapping.h"
#include "array/1d/refer.h"
#include "system/grouping/action/minimizer/line/regular/parameter-name.h"
#include "system/grouping/allocate.h"

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
    imprint(M.MemSys().Content().Gradient,M.Sys().Content().X);
    imprint(M.RunSys().Content().X,M.Sys().Content().X);
    imprint(M.RunSys().Content().Gradient,M.Sys().Content().X);
    allocate(M.MemSys().Content().Energy);
    allocate(M.RunSys().Content().Energy);
    imprint(M.LineDirc,M.Sys().Content().X);
    refer(M.MemSys().Content().Velocity,M.LineDirc);
    refer(M.RunSys().Content().Velocity,M.LineDirc);
    refer(M.MemSys().Interaction,M.Sys().Interaction);
    refer(M.RunSys().Interaction,M.Sys().Interaction);
    allocate(M.MemSys().Groups,M.Sys().Groups.size);
    allocate(M.RunSys().Groups,M.Sys().Groups.size);
    for(unsigned int i=0;i<M.Sys().Groups.size;++i) {
      SystemGroupingMethodName SGN;
      SGN=MinimizerSysGrpMethodMapping(M.Sys().Groups[i].Method);
      allocate(M.MemSys().Groups[i],SGN);
      allocate(M.RunSys().Groups[i],SGN);
      refer(M.MemSys().Groups[i].MerIDRange,M.Sys().Groups[i].MerIDRange);
      refer(M.RunSys().Groups[i].MerIDRange,M.Sys().Groups[i].MerIDRange);
      unsigned int n=M.Sys().Groups[i].MerIDRange.size;
      allocate(M.MemSys().Groups[i].grpContent,n);
      allocate(M.RunSys().Groups[i].grpContent,n);
      M.MemSys().Groups[i].buildGrpContent(M.MemSys().Content());
      M.RunSys().Groups[i].buildGrpContent(M.RunSys().Content());
      void* pStep=reinterpret_cast<void*>(&(M.Step));
      switch(SGN) {
        case SystemFixPosition:
          break;
        case SystemMinimizerLineRegular:
          M.MemSys().Groups[i].Param[MinLineRegularStep].ptr[0]=pStep;
          M.RunSys().Groups[i].Param[MinLineRegularStep].ptr[0]=pStep;
          break;
        default:
          Error("This Grouping Method Cannot be processed!");
      }
    }
    M.MemSys().Build();
    M.RunSys().Build();
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

