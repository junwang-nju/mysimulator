
#ifndef _System_Propagator_Interface_H_
#define _System_Propagator_Interface_H_

namespace mysimulator {

  template <typename T,typename DataType,template<typename> class ContentType>
  struct SystemPropagator {

    public:

      typedef SystemPropagator<T,DataType,ContentType>  Type;

  };

}

#endif

