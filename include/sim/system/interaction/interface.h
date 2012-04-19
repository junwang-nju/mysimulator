
#ifndef _System_Interaction_Interface_H_
#define _System_Interaction_Interface_H_

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            typename BufferType,typename DataType,
            template<typename> class ContentType>
  struct SystemInteraction {

    public:

      typedef
        SystemInteraction<T,IDType,ParamType,GeomType,BufferType,DataType,
                          ContentType>
        Type;

  };

}

#endif

