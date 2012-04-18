
#ifndef _Interaction_Buffer_Interface_H_
#define _Interaction_Buffer_Interface_H_

#include "unique/64bit/interface.h"
#include "array/2d/release.h"

namespace mysimulator {

  template <typename T>
  struct InteractionBuffer {

    public:

      typedef InteractionBuffer<T>  Type;
      typedef void (*P2PFuncType)(const T*,const Unique64Bit*,T*,bool&);
      typedef void (*GetPreFuncType)(Type&);

      unsigned int    dim;
      T*              pre;
      T*              post;
      T**             tmvec;
      Type**          inf;
      bool            postUpdate;
      P2PFuncType     P2PFunc,  P2PDiff,  P2PBoth;
      GetPreFuncType  GPreFunc, GPreDiff, GPreBoth;

      InteractionBuffer()
        : dim(0), pre(NULL), post(NULL), tmvec(NULL), inf(NULL),
          postUpdate(true),
          P2PFunc(NULL),  P2PDiff(NULL),  P2PBoth(NULL),
          GPreFunc(NULL), GPreDiff(NULL), GPreBoth(NULL) {}
      ~InteractionBuffer() { clearData(); }

      bool isvalid() const {
        return (dim>0)&&(pre!=NULL)&&(post!=NULL)&&(tmvec!=NULL)&&
               (P2PFunc!=NULL)&&(P2PDiff!=NULL)&&(P2PBoth!=NULL);
      }
      void clearData() {
        GPreBoth=NULL;    GPreDiff=NULL;    GPreFunc=NULL;
        P2PBoth=NULL;     P2PDiff=NULL;     P2PFunc=NULL;
        postUpdate=true;  release(inf);     release2d(tmvec);
        release(post);    release(pre);     dim=0;
      }

      void clearFlag() { postUpdate=true; }
      void GetPreFunc() { GPreFunc(*this); }
      void GetPreDiff() { GPreDiff(*this); }
      void GetPreBoth() { GPreBoth(*this); }
      void Pre2PostFunc(const Unique64Bit* P){ P2PFunc(pre,P,post,postUpdate); }
      void Pre2PostDiff(const Unique64Bit* P){ P2PDiff(pre,P,post,postUpdate); }
      void Pre2PostBoth(const Unique64Bit* P){ P2PBoth(pre,P,post,postUpdate); }

  };

  template <typename T>
  bool IsValid(const InteractionBuffer<T>& B) { return B.isvalid(); }

  template <typename T>
  void release(InteractionBuffer<T>& B) { B.clearData(); }

}

#endif

