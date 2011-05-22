
#ifndef _Binary_Tree_Branch_Name_H_
#define _Binary_Tree_Branch_Name_H_

namespace mysimulator {

  enum BranchName {
    Unassigned,
    LeftBranch,
    RightBranch
  };

}

#include "intrinsic-type/single-operation-type.h"

namespace mysimulator {

  template <>
  struct _SingleOp<BranchName> { typedef BranchName Type; };

}

#endif

