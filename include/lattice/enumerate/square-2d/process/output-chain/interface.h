
#ifndef _Lattice_Enumerate_Square2D_Process_OutputChain_Interface_H_
#define _Lattice_Enumerate_Square2D_Process_OutputChain_Interface_H_

#include "lattice/enumerate/square-2d/process/interface.h"

namespace mysimulator {

  template <unsigned int L, typename OutputStream>
  struct LatticeEnumSquare2DProcessOutputChain
      : public LatticeEnumSquare2DProcessBase<L> {

    typedef LatticeEnumSquare2DProcessOutputChain<L,OutputStream> Type;
    typedef LatticeEnumSquare2DProcessBase<L> ParentType;

    OutputStream os;

    LatticeEnumSquare2DProcessOutputChain() : os(stdout) {}

    virtual void operator()(const LatticeEnumSquare2DRunData<L>& Data) {
      assert(IsValid(os));
      os<<Data.C<<Endl;
    }

  };

}

#endif

