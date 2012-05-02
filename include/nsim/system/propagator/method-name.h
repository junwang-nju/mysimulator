
#ifndef _System_Propagator_Method_Name_H_
#define _System_Propagator_Method_Name_H_

namespace mysimulator {

  enum SystemPropagatorMethodName {
    SystemToBeDetermined=0,
    SystemFixPosition,
    SystemMinimizerLineRegular,
    SystemConstEVelVerlet,
    SystemLangevinVelVerlet,
    SystemBerendsenVelVerlet,
    SystemPropagatorNumberMethods,
    SystemPropagatorUnassigned
  };

}

#endif

