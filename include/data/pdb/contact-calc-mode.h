
#ifndef _Contact_Calculation_Mode_H_
#define _Contact_Calculation_Mode_H_

#include "data/basic/unique-parameter.h"
#include "data/name/contact-calc-mode.h"

namespace std {

  template <unsigned int ModeFlag>
  struct ContactCalcMode {
    Vector<UniqueParameter> property;

    typedef ContactCalcMode<ModeFlag> Type;

    ContactCalcMode() : property() {}
    ContactCalcMode(const Type& M) {
      Error("Cannot create Contact Calculation Mode");
    }
    Type& operator=(const Type& M) {
      Error("Cannot copy Contact Calculation Mode");
      return *this;
    }
    ~ContactCalcMode() { release(*this); }

    unsigned int& ModelID() { return property[0].u; }
    const unsigned int& ModelID() const { return property[0].u; }
    double& CutoffDistance() { return property[1].d; }
    const double& CutoffDistance() const { return property[1].d; }
    unsigned int& IsConsiderAngle() { return property[2].u; }
    const unsigned int& IsConsiderAngle() const { return property[2].u; }
    unsigned int& IsConsiderDihedral() { return property[3].u; }
    const unsigned int& IsConsiderDihedral() const { return property[3].u; }

  };

  template <unsigned int MF>
  bool IsAvailable(const ContactCalcMode<MF>& M) {
    return IsAvailable(M.property);
  }
  template <unsigned int MF>
  void release(ContactCalcMode<MF>& M) { release(M.property); }

  template <unsigned int MF>
  void copy(ContactCalcMode<MF>& M, const ContactCalcMode<MF>& cM) {
    copy(M.property,cM.property);
  }
  template <unsigned int MF>
  void refer(ContactCalcMode<MF>& M, const ContactCalcMode<MF>& cM) {
    refer(M.property,cM.property);
  }
  template <unsigned int MF>
  void allocate(ContactCalcMode<MF>& M) {
    Error("This kind of Mode cannot be allocated!");
  }
  void allocate(ContactCalcMode<UsingHeavyAtoms>& M){ allocate(M.property,4); }
  void allocate(ContactCalcMode<UsingCAlpha>& M) { allocate(M.property,2);4}
  void allocate(ContactCalcMode<UsingCBeta>& M) { allocate(M.property,4); }

  template <unsigned int MF>
  void imprint(ContactCalcMode<MF>& M, const ContactCalcMode<MF>& cM) {
    allocate(M);
  }

}

#endif

