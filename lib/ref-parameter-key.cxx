
#include "ref-parameter-key.h"

namespace std {

  void refParameterKey::refer(refParameterKey::ParentType& P) {
    this->index().refer(P.index());
    this->hash().refer(P.hash());
    P.RefInfo().add_before(this->RefInfo());
  }

  void refParameterKey::refer(ObjectWStorage<ParameterKeyBase<varVector> >& P){
    this->index().refer(P.index());
    this->hash().refer(P.hash());
    P.RefList().append(this->RefInfo());
  }

}

