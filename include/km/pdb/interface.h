
#ifndef _PDB_Interface_H_
#define _PDB_Interface_H_

#include "array2d/interface.h"
#include <cstring>

namespace mysimulator {

  class PDBObject {

    public:

      typedef PDBObject   Type;
      friend void Clear(PDBObject&);

      PDBObject() : _code(), _nres(0), _model(), _seqIdx() {
        strncpy(_code,"    ",5);
      }
      ~PDBObject() { Clear(*this); }

      bool IsValid() const {
        return (strncpy(_code,"    ",4)!=0)&&(_nres>0)&&
               _model.IsValid()&&_seqIdx.IsValid();
      }
      const char* Code() const { return _code; }
      const unsigned int NumberResidue() const { return _nres; }
      const PDBModel& Model(unsigned int i) { return _model[i]; }
      const unsigned int Index(unsigned int i,unsigned int j) const {
        assert(_seqIdx.IsValid());
        return _seqIdx[i][j];
      }

    protected:

      char _code[5];
      unsigned int _nres;
      Array<PDBModel> _model;
      Array2D<unsigned int> _seqIdx;

    private:

      PDBObject(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBObject& O) {
    strncpy(O._code,"    ",5);
    O._nres=0;
    Clear(O._model);
    Clear(O._seqIdx);
  }

}

#endif

