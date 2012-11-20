
#ifndef _System_Interaction_Function_Data_State_H_
#define _System_Interaction_Function_Data_State_H_

namespace mysimulator {

  enum class InteractionFuncDataState {
    NotReady    = 0,
    EDataOK     = 1,
    GDataOK     = 2,
    HDataOK     = 4,
    EGDataOK    = EDataOK + GDataOK,
    EHDataOK    = EDataOK + HDataOK,
    GHDataOK    = GDataOK + HDataOK,
    EGHDataOK   = EDataOK + GDataOK + HDataOK
  };

}

#endif

