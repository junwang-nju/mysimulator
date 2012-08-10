
#ifndef _Interaction_Func_Update_Name_H_
#define _Interaction_Func_Update_Name_H_

namespace mysimulator {

  enum InteractionFuncUpdateName {
    NoUpdateOK = 0U,
    EFuncUpdateOK = 1U,
    GFuncUpdateOK = 2U,
    HFuncUpdateOK = 4U,
    EGFuncUpdateOK = EFuncUpdateOK + GFuncUpdateOK,
    EHFuncUpdateOK = EFuncUpdateOK + HFuncUpdateOK,
    GHFuncUpdateOK = GFuncUpdateOK + HFuncUpdateOK,
    EGHFuncUpdateOK = EFuncUpdateOK + GFuncUpdateOK + HFuncUpdateOK
  };

}

#endif

