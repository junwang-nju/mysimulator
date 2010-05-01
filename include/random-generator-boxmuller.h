
#ifndef _Random_Generator_BoxMuller_H_
#define _Random_Generator_BoxMuller_H_

namespace std {

  template <typename UniformRNG>
  struct BoxMuller {

    typedef BoxMuller<UniformRNG>   Type;

    UniformRNG *urng;
    double *DbFac;
    bool *isSecond;
    double *output;
    unsigned int state;

    BoxMuller()
      : urng(NULL), DbFac(NULL), isSecond(NULL), output(NULL), state(Unused) {}
    BoxMuller(const Type&) { myError("Cannot create from BoxMuller"); }
    Type& operator=(const Type& BM) { assign(*this,BM); return *this; }
    ~BoxMuller() { release(*this); }

  };

  template <typename UniformRNG>
  void release(BoxMuller<UniformRNG>& BM) {
    if(BM.state==Allocated) {
      safe_delete(BM.urng);
      safe_delete_array(BM.DbFac);
      safe_delete(BM.isSecond);
      safe_delete(BM.output);
    } else {
      BM.urng=NULL;
      BM.DbFac=NULL;
      BM.isSecond=NULL;
      BM.output=NULL;
    }
    BM.state=Unused;
  }

  template <typename UniformRNG>
  void refer(BoxMuller<UniformRNG>& dest, const BoxMuller<UniformRNG>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.urng=src.urng;
    dest.DbFac=src.DbFac;
    dest.isSecond=src.isSecond;
    dest.output=src.output;
    dest.state=Reference;
  }

}

#endif

