
#ifndef _Boundary_PeriodBox_Interface_H_
#define _Boundary_PeriodBox_Interface_H_

#include "array/1d/interface.h"
#include "array/1d/scale.h"

namespace mysimulator {

  template <typename T>
  struct PeriodBox {

    public:

      typedef PeriodBox<T>  Type;

      Array1D<T>    box;
      Array1D<T>    hbox;
      Array1D<bool> pdflag;

      PeriodBox() : box(), hbox(), pdflag() {}
      ~PeriodBox() { clearData(); }

      void clearData() { release(box); release(hbox); release(pdflag); }
      bool isvalid() const {
        return IsValid(box)&&IsValid(hbox)&&IsValid(pdflag);
      }

      const unsigned int& dimension() const { return box.size; }
      void sync() {
        assert(isvalid());
        copy(hbox,box); scale(hbox,ValueHalf<T>());
      }

    private:

      PeriodBox(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  bool IsValid(const PeriodBox<T>& B) { return B.isvalid(); }

  template <typename T>
  void release(PeriodBox<T>& B) { B.clearData(); }

}

#ifdef _Distance_Calc_H_
#include "displacement/period-box/calc.h"
#endif

#endif

