
#ifndef _Array_Common_Shape_Parameter_H_
#define _Array_Common_Shape_Parameter_H_

namespace mysimulator {

  enum ArrayShapeParameter {
    ArrayShapeShift=8,
    ArrayShapeSizeShift=4,
    ArrayShapeBackSizeShift=ArrayShapeShift-ArrayShapeSizeShift
  };

}

#endif

