
#ifndef _Meta_Interaction_H_
#define _Meta_interaction_H_

namespace std {

  template <typename T, template<typename> class DistBuffer, typename GeomType,
            template <typename,template<typename>class,typename> class IType,
            typename PType>
  struct MetaInteraction {
    typedef IType<T,DistBuffer,GeomType>  RunIType;
    typedef PType RunPType;
    typedef MetaInteraction<T,DistBuffer,GeomType,IType,PType>  Type;

    RunIType inInteraction;
    Vector<unsigned int> tag;
    PropertyList<T> tmvec;
    void (*EFunc)(const Vector<T>*,RunIType&,RunPType&,const UniqueParameter*,
                  T&,Vector<T>*);
    void (*GFunc)(const Vector<T>*,RunIType&,RunPType&,const UniqueParameter*,
                  Vector<T>*,Vector<T>*);
    void (*BFunc)(const Vector<T>*,RunIType&,RunPType&,const UniqueParameter*,
                  T&,Vector<T>*,Vector<T>*);

    MetaInteraction()
      : inInteraction(),tag(),tmvec(),EFunc(NULL),GFunc(NULL),BFunc(NULL) {}
    MetaInteraction(const Type&) {
      myError("Cannot create Meta Interaction");
    }
    Type& operator=(const Type& I) {
      myError("Cannot copy Meta Interaction");
      return *this;
    }
    ~MetaInteraction() { release(*this); }

    unsigned int& iTag() { return tag[0]; }
    const unsigned int& iTag() const { return tag[0]; }
  };

  template <typename T,template<typename> class DBuff,typename GType,
            template <typename,template<typename>class,typename> class IType>
  bool IsAvailable(const MetaInteraction<T,DBuff,GType,IType>& MI) {
    return IsAvailable(MI.inInteraction)&&IsAvailable(MI.tag)&&
           IsAvailable(MI.EFunc)&&IsAvailable(MI.GFunc)&&IsAvailable(MI.BFunc);
  }

  template <typename T,template<typename> class DBuff,typename GType,
            template <typename,template<typename>class,typename> class IType>
  void release(MetaInteraction<T,DBuff,GType,IType>& MI) {
    release(MI.inInteraction);
    release(MI.tmvec);
    release(MI.tag);
    MI.EFunc=NULL;
    MI.GFunc=NULL;
    MI.BFunc=NULL;
  }

  template <typename T,template<typename> class DBuff,typename GType,
            template <typename,template<typename>class,typename> class IType>
  void copy(MetaInteraction<T,DBuff,GType,IType>& MI,
            const MetaInteraction<T,DBuff,GType,IType>& cMI) {
    assert(IsAvailable(MI));
    assert(IsAvailable(cMI));
    assert(MI.iTag()==cMI.iTag());
    copy(MI.inInteraction,cMI.inInteraction);
  }

  template <typename T,template<typename> class DBuff,typename GType,
            template <typename,template<typename>class,typename> class IType>
  void refer(MetaInteraction<T,DBuff,GType,IType>& MI,
             const MetaInteraction<T,DBuff,GType,IType>& rMI) {
    assert(IsAvailable(rMI));
    release(MI);
    refer(MI.tag,rMI.tag);
    refer(MI.inInteraction,rMI.inInteraction);
    if(IsAvailable(rMI.tmvec))  refer(MI.tmvec,rMI.tmvec);
  }
}

#include "data/name/all-interaction.h"

namespace std {

  template <typename T,template<typename> class DBuff,typename GType,
            template <typename,template<typename>class,typename> class IType>
  void allocate(MetaInteraction<T,DBuff,GType,IType>& MI,
                const unsigned int& tag, const unsigned int& dim) {
  }

}

#endif

