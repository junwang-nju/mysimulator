
#ifndef _Interaction_Func_Update_Name_H_
#define _Interaction_Func_Update_Name_H_

namespace mysimulator {

  enum InteractionFuncUpdateName {
    NoUpdateOK = 0,
    EFuncUpdateOK = 1,
    GFuncUpdateOK = 2,
    HFuncUpdateOK = 4,
    EGFuncUpdateOK = EFuncUpdateOK + GFuncUpdateOK,
    EHFuncUpdateOK = EFuncUpdateOK + HFuncUpdateOK,
    GHFuncUpdateOK = GFuncUpdateOK + HFuncUpdateOK,
    EGHFuncUpdateOK = EFuncUpdateOK + GFuncUpdateOK + HFuncUpdateOK
  };

}

#endif

